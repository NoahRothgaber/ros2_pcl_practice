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
            pcl::PointCloud<pcl::PointXYZRGB> pcl_cloud;
            pcl::fromROSMsg(cloud, pcl_cloud);
            auto now = std::chrono::system_clock::now();
            std::time_t now_c = std::chrono::system_clock::to_time_t(now);
            std::tm local_tm = *std::localtime(&now_c);
            std::ostringstream oss;
            oss << std::put_time(&local_tm, "%m_%d_%Y_%H_%M_%S");
            std::string filename = oss.str() + ".pcd";
            std::string path = std::string(std::getenv("HOME")) + "/Desktop/" + filename;
            pcl::io::savePCDFileASCII(path, pcl_cloud);
        }
        
        }
        
};
int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SavePointCloudServer>());
  rclcpp::shutdown();
}