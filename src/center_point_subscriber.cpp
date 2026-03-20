#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/point.hpp"
#include <pcl/io/pcd_io.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/point_types.h>
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
    // It uses a KdTree for efficient lookup. https://pcl.readthedocs.io/projects/tutorials/en/master/kdtree_search.html
    // The PCD file is expected to be organized (i.e., width and height are set) so that we can directly index into it using pixel coordinates.
    CenterPointSubscriber()
        : Node("center_point_subscriber")
    {
        subscription_ = this->create_subscription<save_pointcloud::msg::BoundingBoxCenter>(
        "/bbox_center",
        10,
        std::bind(&CenterPointSubscriber::topic_callback, this, std::placeholders::_1));

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
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_;
    pcl::KdTreeFLANN<pcl::PointXYZRGB> kdtree_;
    void topic_callback(const save_pointcloud::msg::BoundingBoxCenter::SharedPtr msg) const
    {
        int u = static_cast<int>(msg->center.x);
        int v = static_cast<int>(msg->center.y);

        RCLCPP_INFO(this->get_logger(),
            "Received pixel center - u: %d, v: %d", u, v);

        RCLCPP_INFO(this->get_logger(),
            "Bounding box - x_min: %d y_min: %d x_max: %d y_max: %d",
            msg->x_min, msg->y_min, msg->x_max, msg->y_max);

        if (u < 0 || v < 0 ||
            u >= static_cast<int>(cloud_->width) ||
            v >= static_cast<int>(cloud_->height))
        {
            RCLCPP_WARN(this->get_logger(), "Pixel is out of bounds");
            return;
        }

        const auto & pt = cloud_->at(u, v);

        if (!pcl::isFinite(pt))
        {
            RCLCPP_WARN(this->get_logger(), "Point at pixel (%d, %d) is invalid", u, v);
            return;
        }

        RCLCPP_INFO(this->get_logger(),
            "3D point → X=" CYAN "%.4f" RESET
            " Y=" CYAN "%.4f" RESET
            " Z=" CYAN "%.4f" RESET,
            pt.x, pt.y, pt.z);
    }
};
int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CenterPointSubscriber>());
    rclcpp::shutdown();
    return 0;
}