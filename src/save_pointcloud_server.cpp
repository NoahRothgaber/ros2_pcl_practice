#include "rclcpp/wait_for_message.hpp"
#include "std_srvs/srv/trigger.hpp"
#include "std_srvs/srv/empty.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <memory>
#include <pcl_conversions/pcl_conversions.h>
#include <chrono>
#include <iostream>
#include "sensor_msgs/msg/image.hpp"
#include <opencv2/opencv.hpp>

class SavePointCloudServer : public rclcpp::Node
{
public:
  SavePointCloudServer() : Node("save_pointcloud_server")
  {
     service_ = this->create_service<std_srvs::srv::Empty>(
      "save_pointcloud",
      std::bind(&SavePointCloudServer::save_pointcloud, this,
                std::placeholders::_1, std::placeholders::_2)
    );
  }
private:
    rclcpp::Service<std_srvs::srv::Empty>::SharedPtr service_;
    void save_pointcloud(const std::shared_ptr<std_srvs::srv::Empty::Request> request,
        std::shared_ptr<std_srvs::srv::Empty::Response> response)
        {
        sensor_msgs::msg::PointCloud2 cloud;
        auto qos = rclcpp::SensorDataQoS(); // This is what is recommended per realsense github
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Saving pointcloud...");
        auto sub = this->create_subscription<sensor_msgs::msg::PointCloud2>(
        "/camera/camera/depth/color/points", qos, 
        [](sensor_msgs::msg::PointCloud2::SharedPtr) { /* no-op */ }); // Have to use NO OP because we dont want it to spin and call a callback? 
        auto context = this->get_node_base_interface()->get_context();
        auto timeout = std::chrono::duration<float>(std::max(0.0f, 1.0f - 0.2f)); // 1 second minus a little buffer for shutdown
        const bool ok = rclcpp::wait_for_message<sensor_msgs::msg::PointCloud2>(cloud, sub, context, timeout);
        if (!ok) {
            RCLCPP_INFO(this->get_logger(), "Failed to capture pointcloud within timeout.");
        }
        else {
            RCLCPP_INFO(this->get_logger(),
            "ROS cloud: width=%u height=%u row_step=%u point_step=%u is_dense=%s",
            cloud.width, cloud.height, cloud.row_step, cloud.point_step,
            cloud.is_dense ? "true" : "false");
            pcl::PointCloud<pcl::PointXYZRGB> pcl_cloud;
            pcl::fromROSMsg(cloud, pcl_cloud);
            RCLCPP_INFO(this->get_logger(),
            "PCL cloud: width=%u height=%u size=%zu is_dense=%s",
            pcl_cloud.width, pcl_cloud.height, pcl_cloud.size(),
            pcl_cloud.is_dense ? "true" : "false");
            auto now = std::chrono::system_clock::now();
            std::time_t now_c = std::chrono::system_clock::to_time_t(now);
            std::tm local_tm = *std::localtime(&now_c);
            std::ostringstream oss;
            oss << std::put_time(&local_tm, "%m_%d_%Y_%H_%M_%S");
            std::string filename = oss.str() + ".pcd";
            std::string path = std::string(std::getenv("HOME")) + "/Desktop/" + filename;
            pcl::io::savePCDFileASCII(path, pcl_cloud);
            sensor_msgs::msg::Image rgb_msg;
            auto sub_rgb = this->create_subscription<sensor_msgs::msg::Image>(
            "/camera/camera/color/image_raw", qos,
            [](sensor_msgs::msg::Image::SharedPtr) { /* no-op */ });

            const bool ok_rgb = rclcpp::wait_for_message<sensor_msgs::msg::Image>(
                rgb_msg, sub_rgb, context, timeout);

            if (!ok_rgb) {
                RCLCPP_WARN(this->get_logger(), "Failed to capture RGB image within timeout.");
            }
            else {
                RCLCPP_INFO(this->get_logger(),
                "RGB image: width=%u height=%u encoding=%s step=%u",
                rgb_msg.width, rgb_msg.height, rgb_msg.encoding.c_str(), rgb_msg.step);

                cv::Mat image;

                if (rgb_msg.encoding == "bgr8") {
                    image = cv::Mat(rgb_msg.height, rgb_msg.width, CV_8UC3,
                                    rgb_msg.data.data(), rgb_msg.step).clone();
                }
                else if (rgb_msg.encoding == "rgb8") {
                    cv::Mat rgb(rgb_msg.height, rgb_msg.width, CV_8UC3,
                                rgb_msg.data.data(), rgb_msg.step);
                    cv::cvtColor(rgb, image, cv::COLOR_RGB2BGR);
                }
                else {
                    RCLCPP_ERROR(this->get_logger(),
                    "Unsupported image encoding: %s", rgb_msg.encoding.c_str());
                    return;
                }

                std::string img_filename = oss.str() + ".png";
                std::string img_path = std::string(std::getenv("HOME")) + "/Desktop/" + img_filename;

                if (cv::imwrite(img_path, image)) {
                    RCLCPP_INFO(this->get_logger(), "Saved RGB image to %s", img_path.c_str());
                } else {
                    RCLCPP_ERROR(this->get_logger(), "Failed to save RGB image to %s", img_path.c_str());
                }
            }
        }
        
        }
        
};
int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SavePointCloudServer>());
  rclcpp::shutdown();
}