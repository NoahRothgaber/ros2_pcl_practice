#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"

#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/filters/passthrough.h>

class PassThroughFilterNode : public rclcpp::Node
{
public:
    PassThroughFilterNode() : Node("passthrough_filter_node")
    {
        this->declare_parameter<std::string>("input_topic", "/cropped_pointcloud");
        this->declare_parameter<std::string>("filter_field_name", "z");
        this->declare_parameter<double>("limit_min", 0.35);
        this->declare_parameter<double>("limit_max", 0.65);

        input_topic_ = this->get_parameter("input_topic").as_string();
        filter_field_name_ = this->get_parameter("filter_field_name").as_string();
        limit_min_ = this->get_parameter("limit_min").as_double();
        limit_max_ = this->get_parameter("limit_max").as_double();

        sub_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
            input_topic_,
            10,
            std::bind(&PassThroughFilterNode::cloud_callback, this, std::placeholders::_1));

        pub_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("/passthrough_cloud", 10);

        RCLCPP_INFO(this->get_logger(), "PassThrough subscribed to: %s", input_topic_.c_str());
        RCLCPP_INFO(this->get_logger(), "Filtering field '%s' in range [%.3f, %.3f]",
                    filter_field_name_.c_str(), limit_min_, limit_max_);
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

        pcl::PassThrough<pcl::PointXYZRGB> pass;
        pass.setInputCloud(cloud);
        pass.setFilterFieldName(filter_field_name_);
        pass.setFilterLimits(limit_min_, limit_max_);
        pass.filter(*filtered);

        sensor_msgs::msg::PointCloud2 output_msg;
        pcl::toROSMsg(*filtered, output_msg);
        output_msg.header = msg->header;

        pub_->publish(output_msg);

        RCLCPP_INFO(this->get_logger(),
            "PassThrough: input=%zu output=%zu",
            cloud->size(), filtered->size());
    }

    std::string input_topic_;
    std::string filter_field_name_;
    double limit_min_;
    double limit_max_;

    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr sub_;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pub_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<PassThroughFilterNode>());
    rclcpp::shutdown();
    return 0;
}