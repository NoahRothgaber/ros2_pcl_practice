#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"

#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/filters/voxel_grid.h>

class VoxelGridFilterNode : public rclcpp::Node
{
public:
    VoxelGridFilterNode() : Node("voxel_grid_filter_node")
    {
        this->declare_parameter<std::string>("input_topic", "/sor_cloud");
        this->declare_parameter<double>("leaf_size", 0.005);

        input_topic_ = this->get_parameter("input_topic").as_string();
        leaf_size_ = this->get_parameter("leaf_size").as_double();

        sub_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
            input_topic_,
            10,
            std::bind(&VoxelGridFilterNode::cloud_callback, this, std::placeholders::_1));

        pub_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("/voxel_cloud", 10);

        RCLCPP_INFO(this->get_logger(), "VoxelGrid subscribed to: %s", input_topic_.c_str());
        RCLCPP_INFO(this->get_logger(), "VoxelGrid leaf_size=%.4f", leaf_size_);
    }

private:
    void cloud_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
    {
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr filtered(new pcl::PointCloud<pcl::PointXYZRGB>);

        pcl::fromROSMsg(*msg, *cloud);

        if (cloud->empty()) {
            RCLCPP_WARN(this->get_logger(), "Received empty cloud");
            return;
        }

        pcl::VoxelGrid<pcl::PointXYZRGB> vg;
        vg.setInputCloud(cloud);
        vg.setLeafSize(
            static_cast<float>(leaf_size_),
            static_cast<float>(leaf_size_),
            static_cast<float>(leaf_size_));
        vg.filter(*filtered);

        sensor_msgs::msg::PointCloud2 output_msg;
        pcl::toROSMsg(*filtered, output_msg);
        output_msg.header = msg->header;

        pub_->publish(output_msg);

        RCLCPP_INFO(this->get_logger(),
            "VoxelGrid: input=%zu output=%zu",
            cloud->size(), filtered->size());
    }

    std::string input_topic_;
    double leaf_size_;

    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr sub_;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pub_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<VoxelGridFilterNode>());
    rclcpp::shutdown();
    return 0;
}