#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include <inttypes.h>
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>

class PointCloudFilterNode : public rclcpp::Node{
public:
PointCloudFilterNode() : Node("pointcloud_filter_node")
{
    
    publish_filtered_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("filtered_pointcloud", 10);

}
private:
rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr publish_filtered_;
};
