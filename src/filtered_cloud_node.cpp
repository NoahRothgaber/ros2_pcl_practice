#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"

#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>

#include <pcl/ModelCoefficients.h>
#include <pcl/PointIndices.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/filters/extract_indices.h>

class FilteredCloudNode : public rclcpp::Node
{
public:
    FilteredCloudNode() : Node("filtered_cloud_node")
    {
        this->declare_parameter<std::string>("input_topic", "/passthrough_cloud");
        this->declare_parameter<double>("distance_threshold", 0.005);
        this->declare_parameter<bool>("optimize_coefficients", true);

        input_topic_ = this->get_parameter("input_topic").as_string();
        distance_threshold_ = this->get_parameter("distance_threshold").as_double();
        optimize_coefficients_ = this->get_parameter("optimize_coefficients").as_bool();

        sub_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
            input_topic_,
            10,
            std::bind(&FilteredCloudNode::cloud_callback, this, std::placeholders::_1));

        plane_pub_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("/segmented_plane", 10);
        filtered_pub_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("/filtered_cloud", 10);

        RCLCPP_INFO(this->get_logger(), "Filtered cloud subscribed to: %s", input_topic_.c_str());
        RCLCPP_INFO(this->get_logger(), "Distance threshold: %.4f", distance_threshold_);
    }

private:
    void cloud_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
    {
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
        pcl::fromROSMsg(*msg, *cloud);

        if (cloud->empty()) {
            RCLCPP_WARN(this->get_logger(), "Received empty cloud");
            return;
        }

        pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients);
        pcl::PointIndices::Ptr inliers(new pcl::PointIndices);

        pcl::SACSegmentation<pcl::PointXYZRGB> seg;
        seg.setOptimizeCoefficients(optimize_coefficients_);
        seg.setModelType(pcl::SACMODEL_PLANE);
        seg.setMethodType(pcl::SAC_RANSAC);
        seg.setDistanceThreshold(distance_threshold_);
        seg.setInputCloud(cloud);
        seg.segment(*inliers, *coefficients);

        if (inliers->indices.empty()) {
            RCLCPP_WARN(this->get_logger(), "No planar model found");
            return;
        }

        pcl::ExtractIndices<pcl::PointXYZRGB> extract;
        extract.setInputCloud(cloud);
        extract.setIndices(inliers);

        pcl::PointCloud<pcl::PointXYZRGB>::Ptr plane_cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr nonplane_cloud(new pcl::PointCloud<pcl::PointXYZRGB>);

        extract.setNegative(false);
        extract.filter(*plane_cloud);

        extract.setNegative(true);
        extract.filter(*nonplane_cloud);

        sensor_msgs::msg::PointCloud2 plane_msg;
        sensor_msgs::msg::PointCloud2 filtered_msg;

        pcl::toROSMsg(*plane_cloud, plane_msg);
        pcl::toROSMsg(*nonplane_cloud, filtered_msg);

        plane_msg.header = msg->header;
        filtered_msg.header = msg->header;

        plane_pub_->publish(plane_msg);
        filtered_pub_->publish(filtered_msg);

        RCLCPP_INFO(this->get_logger(),
            "Filtered pipeline: input=%zu plane=%zu filtered=%zu",
            cloud->size(), plane_cloud->size(), nonplane_cloud->size());
    }

    std::string input_topic_;
    double distance_threshold_;
    bool optimize_coefficients_;

    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr sub_;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr plane_pub_;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr filtered_pub_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<FilteredCloudNode>());
    rclcpp::shutdown();
    return 0;
}