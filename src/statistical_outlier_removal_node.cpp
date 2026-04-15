#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"

#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/filters/statistical_outlier_removal.h>

class StatisticalOutlierRemovalNode : public rclcpp::Node
{
public:
    StatisticalOutlierRemovalNode() : Node("statistical_outlier_removal_node")
    {
        this->declare_parameter<std::string>("input_topic", "/filtered_cloud");
        this->declare_parameter<int>("mean_k", 20);
        this->declare_parameter<double>("stddev_mul_thresh", 1.0);

        input_topic_ = this->get_parameter("input_topic").as_string();
        mean_k_ = this->get_parameter("mean_k").as_int();
        stddev_mul_thresh_ = this->get_parameter("stddev_mul_thresh").as_double();

        sub_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
            input_topic_,
            10,
            std::bind(&StatisticalOutlierRemovalNode::cloud_callback, this, std::placeholders::_1));

        pub_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("/sor_cloud", 10);

        RCLCPP_INFO(this->get_logger(), "SOR subscribed to: %s", input_topic_.c_str());
        RCLCPP_INFO(this->get_logger(), "SOR params: mean_k=%d stddev_mul_thresh=%.3f",
                    mean_k_, stddev_mul_thresh_);
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

        pcl::StatisticalOutlierRemoval<pcl::PointXYZRGB> sor;
        sor.setInputCloud(cloud);
        sor.setMeanK(mean_k_);
        sor.setStddevMulThresh(stddev_mul_thresh_);
        sor.filter(*filtered);

        sensor_msgs::msg::PointCloud2 output_msg;
        pcl::toROSMsg(*filtered, output_msg);
        output_msg.header = msg->header;

        pub_->publish(output_msg);

        RCLCPP_INFO(this->get_logger(),
            "SOR: input=%zu output=%zu",
            cloud->size(), filtered->size());
    }

    std::string input_topic_;
    int mean_k_;
    double stddev_mul_thresh_;

    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr sub_;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pub_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<StatisticalOutlierRemovalNode>());
    rclcpp::shutdown();
    return 0;
}