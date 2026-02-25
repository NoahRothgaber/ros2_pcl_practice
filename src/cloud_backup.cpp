#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl_conversions/pcl_conversions.h>

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <memory>

using namespace std::chrono_literals;

class PointCloudPublisher : public rclcpp::Node
{
public:
  PointCloudPublisher()
  : Node("pointcloud_publisher")
  {
    auto cloud = std::make_shared<pcl::PointCloud<pcl::PointXYZRGB>>();
    auto cloud_voxel = std::make_shared<pcl::PointCloud<pcl::PointXYZRGB>>();
    auto cloud_outlier = std::make_shared<pcl::PointCloud<pcl::PointXYZRGB>>();

    std::string path = std::string(std::getenv("HOME")) + "/Desktop/02_18_2026_13_19_16.pcd";
    if (pcl::io::loadPCDFile<pcl::PointXYZRGB>(path, *cloud) == -1) {
      RCLCPP_ERROR(this->get_logger(), "Couldn't read file %s", path.c_str());
      rclcpp::shutdown();
      return;
    }

    RCLCPP_INFO(this->get_logger(), "Loaded %zu points from %s", cloud->size(), path.c_str());

    // --- VoxelGrid (compute once) ---
    pcl::VoxelGrid<pcl::PointXYZRGB> vg;
    vg.setInputCloud(cloud);
    vg.setLeafSize(0.02f, 0.02f, 0.02f);
    vg.filter(*cloud_voxel);

    RCLCPP_INFO(this->get_logger(), "VoxelGrid output: %zu points", cloud_voxel->size());

    auto qos = rclcpp::QoS(rclcpp::KeepLast(10)).reliable().durability_volatile();

    // Statistical Outlier Removal
    pcl::StatisticalOutlierRemoval<pcl::PointXYZRGB> outlier_removal;
    outlier_removal.setInputCloud(cloud);
    outlier_removal.setMeanK(50);
    outlier_removal.setStddevMulThresh(1.0);
    outlier_removal.filter(*cloud_outlier);
    RCLCPP_INFO(this->get_logger(), "Outlier output: %zu points", cloud_outlier->size());

    pub_raw_   = this->create_publisher<sensor_msgs::msg::PointCloud2>("point", qos);
    pub_voxel_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("voxel_point", qos);
    pub_outlier_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("outlier_point", qos);
    // Timer publishes both
    timer_ = this->create_wall_timer(
      500ms,
      [this, cloud, cloud_voxel, cloud_outlier]() {
        const auto stamp = this->get_clock()->now();

        sensor_msgs::msg::PointCloud2 msg_raw;
        pcl::toROSMsg(*cloud, msg_raw);
        msg_raw.header.frame_id = "map";
        msg_raw.header.stamp = stamp;
        pub_raw_->publish(msg_raw);

        sensor_msgs::msg::PointCloud2 msg_voxel;
        pcl::toROSMsg(*cloud_voxel, msg_voxel);
        msg_voxel.header.frame_id = "map";
        msg_voxel.header.stamp = stamp;
        pub_voxel_->publish(msg_voxel);

        sensor_msgs::msg::PointCloud2 msg_outlier;
        pcl::toROSMsg(*cloud_outlier, msg_outlier);
        msg_outlier.header.frame_id = "map";
        msg_outlier.header.stamp = stamp;
        pub_outlier_->publish(msg_outlier);
      }
    );
  }

private:
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pub_raw_;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pub_voxel_;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pub_outlier_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<PointCloudPublisher>());
  rclcpp::shutdown();
  return 0;
}


#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl_conversions/pcl_conversions.h>

#include <chrono>
#include <cstdlib>
#include <memory>
#include <mutex>

using namespace std::chrono_literals;

class PointCloudPublisher : public rclcpp::Node
{
public:
  PointCloudPublisher()
  : Node("pointcloud_publisher")
  {
    // --- Declare parameters ---
    this->declare_parameter("voxel_leaf", 0.02);
    this->declare_parameter("sor_mean_k", 50);
    this->declare_parameter("sor_stddev", 1.0);

    voxel_leaf_ = this->get_parameter("voxel_leaf").as_double();
    sor_mean_k_ = this->get_parameter("sor_mean_k").as_int();
    sor_stddev_ = this->get_parameter("sor_stddev").as_double();

    // --- Load raw cloud ---
    cloud_raw_ = std::make_shared<pcl::PointCloud<pcl::PointXYZRGB>>();
    cloud_voxel_ = std::make_shared<pcl::PointCloud<pcl::PointXYZRGB>>();
    cloud_outlier_ = std::make_shared<pcl::PointCloud<pcl::PointXYZRGB>>();

    std::string path = std::string(std::getenv("HOME")) + "/Desktop/02_18_2026_13_19_16.pcd";
    if (pcl::io::loadPCDFile<pcl::PointXYZRGB>(path, *cloud_raw_) == -1) {
      RCLCPP_ERROR(this->get_logger(), "Couldn't read file %s", path.c_str());
      rclcpp::shutdown();
      return;
    }

    RCLCPP_INFO(this->get_logger(), "Loaded %zu points", cloud_raw_->size());

    apply_voxel();
    apply_sor();

    auto qos = rclcpp::QoS(10).reliable();

    pub_raw_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("point", qos);
    pub_voxel_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("voxel_point", qos);
    pub_outlier_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("outlier_point", qos);

    // --- Parameter callback ---
    param_callback_handle_ =
      this->add_on_set_parameters_callback(
        std::bind(&PointCloudPublisher::param_callback, this, std::placeholders::_1)
      );

    // --- Publish timer ---
    timer_ = this->create_wall_timer(
      500ms,
      std::bind(&PointCloudPublisher::publish_clouds, this)
    );
  }

private:

  void apply_voxel()
  {
    pcl::VoxelGrid<pcl::PointXYZRGB> vg;
    vg.setInputCloud(cloud_raw_);
    vg.setLeafSize(voxel_leaf_, voxel_leaf_, voxel_leaf_);
    vg.filter(*cloud_voxel_);

    RCLCPP_INFO(this->get_logger(), "Voxel: %zu points", cloud_voxel_->size());
  }

  void apply_sor()
  {
    pcl::StatisticalOutlierRemoval<pcl::PointXYZRGB> sor;
    sor.setInputCloud(cloud_raw_);  // chained after voxel
    sor.setMeanK(sor_mean_k_);
    sor.setStddevMulThresh(sor_stddev_);
    sor.filter(*cloud_outlier_);

    RCLCPP_INFO(this->get_logger(), "Outlier: %zu points", cloud_outlier_->size());
  }

  rcl_interfaces::msg::SetParametersResult
  param_callback(const std::vector<rclcpp::Parameter> & params)
  {
    std::lock_guard<std::mutex> lock(mutex_);

    for (const auto & param : params)
    {
      if (param.get_name() == "voxel_leaf") {
        voxel_leaf_ = param.as_double();
        apply_voxel();
        apply_sor();
      }
      else if (param.get_name() == "sor_mean_k") {
        sor_mean_k_ = param.as_int();
        apply_sor();
      }
      else if (param.get_name() == "sor_stddev") {
        sor_stddev_ = param.as_double();
        apply_sor();
      }
    }

    rcl_interfaces::msg::SetParametersResult result;
    result.successful = true;
    return result;
  }

  void publish_clouds()
  {
    std::lock_guard<std::mutex> lock(mutex_);

    auto stamp = this->now();

    auto publish = [&](auto cloud, auto publisher) {
      sensor_msgs::msg::PointCloud2 msg;
      pcl::toROSMsg(*cloud, msg);
      msg.header.frame_id = "map";
      msg.header.stamp = stamp;
      publisher->publish(msg);
    };

    publish(cloud_raw_, pub_raw_);
    publish(cloud_voxel_, pub_voxel_);
    publish(cloud_outlier_, pub_outlier_);
  }

  std::shared_ptr<pcl::PointCloud<pcl::PointXYZRGB>> cloud_raw_;
  std::shared_ptr<pcl::PointCloud<pcl::PointXYZRGB>> cloud_voxel_;
  std::shared_ptr<pcl::PointCloud<pcl::PointXYZRGB>> cloud_outlier_;

  double voxel_leaf_;
  int sor_mean_k_;
  double sor_stddev_;

  std::mutex mutex_;

  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pub_raw_;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pub_voxel_;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pub_outlier_;
  rclcpp::node_interfaces::OnSetParametersCallbackHandle::SharedPtr param_callback_handle_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<PointCloudPublisher>());
  rclcpp::shutdown();
  return 0;
}