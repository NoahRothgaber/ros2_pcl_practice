#include <memory>
#include <inttypes.h>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"

#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>
#include <pcl_conversions/pcl_conversions.h>

class PointCloudOnceSubscriber : public rclcpp::Node
{
public:
  PointCloudOnceSubscriber()
  : Node("pointcloud2_subscriber")
  {
    capture_once_ = this->declare_parameter<bool>("capture_once", true);
    pub_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("filtered_pointcloud", 10);
    sub_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
      "/camera/camera/depth/color/points",
      rclcpp::SensorDataQoS(),
      std::bind(&PointCloudOnceSubscriber::on_cloud, this, std::placeholders::_1)
    );
  }

private:
  void on_cloud(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
  {
    RCLCPP_INFO(this->get_logger(),
      "Got cloud: height=%" PRIu32 " width=%" PRIu32 " fields=%zu data=%zu",
      msg->height, msg->width, msg->fields.size(), msg->data.size());

    // ROS -> PCL because the msg is in a different format than what PCL expects
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::fromROSMsg(*msg, *cloud);
    // Filter into a new cloud, have to use RGB with the realsense camera 
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr filtered(new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::PassThrough<pcl::PointXYZRGB> pass;
    pass.setInputCloud(cloud);
    pass.setFilterFieldName("z");
    pass.setFilterLimits(0.0, 1.0);
    pass.filter(*filtered);
    // PCL -> ROS
    sensor_msgs::msg::PointCloud2 filtered_msg;
    pcl::toROSMsg(*filtered, filtered_msg);
    filtered_msg.header = msg->header;

    pub_->publish(filtered_msg);
    RCLCPP_INFO(this->get_logger(), "Published filtered cloud (%zu points).", filtered->size());

    if (capture_once_) {
      // Unsubscribe so we don't re-enter callback while shutting down
      sub_.reset();
      // Giving ROS a moment to actually send the message
      rclcpp::sleep_for(std::chrono::milliseconds(200));
      rclcpp::shutdown();
    }
  }

  rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr sub_;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pub_;
  bool capture_once_{true};
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<PointCloudOnceSubscriber>());
  rclcpp::shutdown();
  return 0;
}
