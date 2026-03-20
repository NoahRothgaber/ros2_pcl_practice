#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/point.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include <pcl/io/pcd_io.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>
#include <cstdlib>
#include "save_pointcloud/msg/bounding_box_center.hpp"
#include <pcl/common/common.h>
#include <pcl/common/point_tests.h>

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define RESET   "\033[0m"

class CenterPointSubscriber : public rclcpp::Node
{
public:
    std::string pcd_name = "02_mustard.pcd";
    // This node subscribes to the center pixel coordinates of the image and looks up the corresponding 3D point in the PCD file.
    // It also crops the organized point cloud using the bounding box and publishes the cropped cloud.
    CenterPointSubscriber()
        : Node("center_point_subscriber")
    {
        subscription_ = this->create_subscription<save_pointcloud::msg::BoundingBoxCenter>(
            "/bbox_center",
            10,
            std::bind(&CenterPointSubscriber::topic_callback, this, std::placeholders::_1));

        cropped_cloud_publisher_ = this->create_publisher<sensor_msgs::msg::PointCloud2>(
            "/cropped_pointcloud",
            10);

        std::string default_pcd_path = std::string(std::getenv("HOME")) + "/Desktop/" + pcd_name;

        this->declare_parameter<std::string>("pcd_file", default_pcd_path);
        std::string pcd_file = this->get_parameter("pcd_file").as_string();

        cloud_ = pcl::PointCloud<pcl::PointXYZRGB>::Ptr(new pcl::PointCloud<pcl::PointXYZRGB>);

        if (pcl::io::loadPCDFile<pcl::PointXYZRGB>(pcd_file, *cloud_) == -1) {
            RCLCPP_ERROR(this->get_logger(), "Couldn't read PCD file: %s", pcd_file.c_str());
            return;
        }

        kdtree_.setInputCloud(cloud_);
        RCLCPP_INFO(this->get_logger(), "Loaded PCD file: %s", pcd_file.c_str());
        RCLCPP_INFO(this->get_logger(), "Loaded PCD file with %zu points", cloud_->size());
        RCLCPP_INFO(this->get_logger(), "Cloud width=%u height=%u", cloud_->width, cloud_->height);
    }

private:
    rclcpp::Subscription<save_pointcloud::msg::BoundingBoxCenter>::SharedPtr subscription_;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr cropped_cloud_publisher_;
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_;
    pcl::KdTreeFLANN<pcl::PointXYZRGB> kdtree_;

    void topic_callback(const save_pointcloud::msg::BoundingBoxCenter::SharedPtr msg)
    {
        int u = static_cast<int>(msg->center.x);
        int v = static_cast<int>(msg->center.y);

        RCLCPP_INFO(this->get_logger(),
            "Received pixel center - u: %d, v: %d", u, v);

        RCLCPP_INFO(this->get_logger(),
            "Bounding box - x_min: %d y_min: %d x_max: %d y_max: %d",
            msg->x_min, msg->y_min, msg->x_max, msg->y_max);
        // Checking for valid pixel bounds before accessing the point cloud
        if (u < 0 || v < 0 ||
            u >= static_cast<int>(cloud_->width) ||
            v >= static_cast<int>(cloud_->height))
        {
            RCLCPP_WARN(this->get_logger(), "Pixel is out of bounds");
            return;
        }

        const auto & pt = cloud_->at(u, v);

        if (!pcl::isFinite(pt) || pt.z <= 0.001f)
        {
            RCLCPP_WARN(this->get_logger(), "Point at pixel (%d, %d) is invalid", u, v);
            return;
        }

        RCLCPP_INFO(this->get_logger(),
            "3D point → X=" CYAN "%.4f" RESET
            " Y=" CYAN "%.4f" RESET
            " Z=" CYAN "%.4f" RESET,
            pt.x, pt.y, pt.z);

        int x_min = msg->x_min;
        int y_min = msg->y_min;
        int x_max = msg->x_max;
        int y_max = msg->y_max;

        if (x_min < 0) x_min = 0;
        if (y_min < 0) y_min = 0;
        if (x_max >= static_cast<int>(cloud_->width))  x_max = static_cast<int>(cloud_->width) - 1;
        if (y_max >= static_cast<int>(cloud_->height)) y_max = static_cast<int>(cloud_->height) - 1;

        if (x_min > x_max || y_min > y_max)
        {
            RCLCPP_WARN(this->get_logger(), "Bounding box is invalid after clamping");
            return;
        }

        pcl::PointCloud<pcl::PointXYZRGB>::Ptr cropped_cloud(
            new pcl::PointCloud<pcl::PointXYZRGB>);

        cropped_cloud->width = static_cast<uint32_t>(x_max - x_min + 1);
        cropped_cloud->height = static_cast<uint32_t>(y_max - y_min + 1);
        cropped_cloud->is_dense = false;
        cropped_cloud->points.resize(cropped_cloud->width * cropped_cloud->height);

        for (int y = y_min; y <= y_max; ++y)
        {
            for (int x = x_min; x <= x_max; ++x)
            {
                int cropped_x = x - x_min;
                int cropped_y = y - y_min;
                cropped_cloud->at(cropped_x, cropped_y) = cloud_->at(x, y);
            }
        }

        sensor_msgs::msg::PointCloud2 cropped_msg;
        pcl::toROSMsg(*cropped_cloud, cropped_msg);
        cropped_msg.header.stamp = this->now();
        cropped_msg.header.frame_id = "camera_depth_optical_frame";
        cropped_cloud_publisher_->publish(cropped_msg);
        RCLCPP_INFO(this->get_logger(),
            GREEN "Published cropped point cloud" RESET
            " width=%u height=%u topic=/cropped_pointcloud",
            cropped_cloud->width, cropped_cloud->height);
    }
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CenterPointSubscriber>());
    rclcpp::shutdown();
    return 0;
}