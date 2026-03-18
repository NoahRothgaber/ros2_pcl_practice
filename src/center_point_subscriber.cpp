#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/point.hpp"
#include <pcl/io/pcd_io.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/point_types.h>

class CenterPointSubscriber : public rclcpp::Node
{
public:
    CenterPointSubscriber()
        : Node("center_point_subscriber")
    {
        subscription_ = this->create_subscription<geometry_msgs::msg::Point>(
            "/center_point",
            10,
            std::bind(&CenterPointSubscriber::topic_callback, this, std::placeholders::_1));

        this->declare_parameter<std::string>("pcd_file", "pointcloud.pcd");
        std::string pcd_file = this->get_parameter("pcd_file").as_string();

        cloud_ = pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud<pcl::PointXYZ>);
        if (pcl::io::loadPCDFile<pcl::PointXYZ>(pcd_file, *cloud_) == -1) {
            RCLCPP_ERROR(this->get_logger(), "Couldn't read PCD file: %s", pcd_file.c_str());
            return;
        }
        kdtree_.setInputCloud(cloud_);
        RCLCPP_INFO(this->get_logger(), "Loaded PCD file with %zu points", cloud_->size());
    }

private:
    void topic_callback(const geometry_msgs::msg::Point::SharedPtr msg) const
    {
        RCLCPP_INFO(this->get_logger(),
            "Received center point - X: %.2f, Y: %.2f, Z: %.2f",
            msg->x, msg->y, msg->z);

        pcl::PointXYZ searchPoint(msg->x, msg->y, msg->z);
        std::vector<int> pointIdxNKNSearch(1);
        std::vector<float> pointNKNSquaredDistance(1);

        if (kdtree_.nearestKSearch(searchPoint, 1, pointIdxNKNSearch, pointNKNSquaredDistance) > 0) {
            pcl::PointXYZ closest = cloud_->points[pointIdxNKNSearch[0]];
            RCLCPP_INFO(this->get_logger(), "Closest point depth: %.2f", closest.z);
        } else {
            RCLCPP_WARN(this->get_logger(), "No nearest neighbor found in PCD");
        }
    }

    rclcpp::Subscription<geometry_msgs::msg::Point>::SharedPtr subscription_;
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_;
    pcl::KdTreeFLANN<pcl::PointXYZ> kdtree_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CenterPointSubscriber>());
    rclcpp::shutdown();
    return 0;
}