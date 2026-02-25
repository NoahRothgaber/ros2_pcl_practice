#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl/filters/radius_outlier_removal.h>
#include <pcl/filters/conditional_removal.h>

#include <pcl_conversions/pcl_conversions.h>

#include <chrono>
#include <cstdlib>
#include <memory>
#include <mutex>
#include <string>

using namespace std::chrono_literals;

class PointCloudPublisher : public rclcpp::Node
{
public:
  PointCloudPublisher()
  : Node("pointcloud_publisher")
  {
    // ---------- Parameters ----------
    // Keep voxel around if you still want it, but it won't feed outlier filters.
    this->declare_parameter("voxel_leaf", 0.02);

    // Choose which outlier filter publishes to /outlier_point
    // Options: "sor", "radius", "conditional"
    this->declare_parameter("outlier_mode", "sor");

    // SOR params
    this->declare_parameter("sor_mean_k", 50);
    this->declare_parameter("sor_stddev", 1.0);

    // RadiusOutlierRemoval params
    this->declare_parameter("ror_radius", 0.8);
    this->declare_parameter("ror_min_neighbors", 2);

    // ConditionalRemoval params (example: z in (min,max))
    this->declare_parameter("cond_z_min", 0.0);
    this->declare_parameter("cond_z_max", 0.8);

    // Keep organized (keeps width/height but may insert NaNs)
    this->declare_parameter("keep_organized", true);

    // Read initial values
    voxel_leaf_      = this->get_parameter("voxel_leaf").as_double();
    outlier_mode_    = this->get_parameter("outlier_mode").as_string();

    sor_mean_k_      = this->get_parameter("sor_mean_k").as_int();
    sor_stddev_      = this->get_parameter("sor_stddev").as_double();

    ror_radius_      = this->get_parameter("ror_radius").as_double();
    ror_min_neighbors_= this->get_parameter("ror_min_neighbors").as_int();

    cond_z_min_      = this->get_parameter("cond_z_min").as_double();
    cond_z_max_      = this->get_parameter("cond_z_max").as_double();

    keep_organized_  = this->get_parameter("keep_organized").as_bool();

    // ---------- Clouds ----------
    cloud_raw_    = std::make_shared<pcl::PointCloud<pcl::PointXYZRGB>>();
    cloud_voxel_  = std::make_shared<pcl::PointCloud<pcl::PointXYZRGB>>();
    cloud_sor_    = std::make_shared<pcl::PointCloud<pcl::PointXYZRGB>>();
    cloud_ror_    = std::make_shared<pcl::PointCloud<pcl::PointXYZRGB>>();
    cloud_cond_   = std::make_shared<pcl::PointCloud<pcl::PointXYZRGB>>();
    cloud_outlier_selected_ = std::make_shared<pcl::PointCloud<pcl::PointXYZRGB>>();

    std::string path = std::string(std::getenv("HOME")) + "/Desktop/02_18_2026_13_19_16.pcd";
    if (pcl::io::loadPCDFile<pcl::PointXYZRGB>(path, *cloud_raw_) == -1) {
      RCLCPP_ERROR(this->get_logger(), "Couldn't read file %s", path.c_str());
      rclcpp::shutdown();
      return;
    }
    RCLCPP_INFO(this->get_logger(), "Loaded %zu points", cloud_raw_->size());

    // Compute once with initial params
    apply_voxel();        // independent
    apply_all_outliers(); // independent, based on raw

    // ---------- Publishers ----------
    auto qos = rclcpp::QoS(10).reliable();
    pub_raw_     = this->create_publisher<sensor_msgs::msg::PointCloud2>("point", qos);
    pub_voxel_   = this->create_publisher<sensor_msgs::msg::PointCloud2>("voxel_point", qos);

    // Publish whichever outlier is selected here:
    pub_outlier_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("outlier_point", qos);

    // Optional: publish each independently (nice for RViz comparisons)
    pub_sor_   = this->create_publisher<sensor_msgs::msg::PointCloud2>("sor_point", qos);
    pub_ror_   = this->create_publisher<sensor_msgs::msg::PointCloud2>("radius_point", qos);
    pub_cond_  = this->create_publisher<sensor_msgs::msg::PointCloud2>("conditional_point", qos);

    // ---------- Parameter callback ----------
    param_callback_handle_ =
      this->add_on_set_parameters_callback(
        std::bind(&PointCloudPublisher::param_callback, this, std::placeholders::_1)
      );

    // ---------- Timer ----------
    timer_ = this->create_wall_timer(500ms, std::bind(&PointCloudPublisher::publish_clouds, this));
  }

private:
  // ---------- Filters ----------
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
    sor.setInputCloud(cloud_raw_); // independent
    sor.setMeanK(sor_mean_k_);
    sor.setStddevMulThresh(sor_stddev_);
    sor.setKeepOrganized(keep_organized_);
    sor.filter(*cloud_sor_);
    RCLCPP_INFO(this->get_logger(), "SOR: %zu points", cloud_sor_->size());
  }

  void apply_ror()
  {
    pcl::RadiusOutlierRemoval<pcl::PointXYZRGB> ror;
    ror.setInputCloud(cloud_raw_); // independent
    ror.setRadiusSearch(ror_radius_);
    ror.setMinNeighborsInRadius(ror_min_neighbors_);
    ror.setKeepOrganized(keep_organized_);
    ror.filter(*cloud_ror_);
    RCLCPP_INFO(this->get_logger(), "RadiusOutlier: %zu points", cloud_ror_->size());
  }

  void apply_conditional()
  {
    // Keep XYZRGB, but compare "z" field
    auto range_cond = pcl::ConditionAnd<pcl::PointXYZRGB>::Ptr(
      new pcl::ConditionAnd<pcl::PointXYZRGB>()
    );

    range_cond->addComparison(
      pcl::FieldComparison<pcl::PointXYZRGB>::ConstPtr(
        new pcl::FieldComparison<pcl::PointXYZRGB>("z", pcl::ComparisonOps::GT, cond_z_min_)
      )
    );

    range_cond->addComparison(
      pcl::FieldComparison<pcl::PointXYZRGB>::ConstPtr(
        new pcl::FieldComparison<pcl::PointXYZRGB>("z", pcl::ComparisonOps::LT, cond_z_max_)
      )
    );

    pcl::ConditionalRemoval<pcl::PointXYZRGB> condrem;
    condrem.setCondition(range_cond);
    condrem.setInputCloud(cloud_raw_); // independent
    condrem.setKeepOrganized(keep_organized_);
    condrem.filter(*cloud_cond_);

    RCLCPP_INFO(this->get_logger(), "Conditional(z): %zu points", cloud_cond_->size());
  }

  void apply_all_outliers()
  {
    apply_sor();
    apply_ror();
    apply_conditional();
    select_outlier_output();
  }

  void select_outlier_output()
  {
    // Choose which cloud drives /outlier_point
    if (outlier_mode_ == "sor") {
      *cloud_outlier_selected_ = *cloud_sor_;
    } else if (outlier_mode_ == "radius") {
      *cloud_outlier_selected_ = *cloud_ror_;
    } else if (outlier_mode_ == "conditional") {
      *cloud_outlier_selected_ = *cloud_cond_;
    } else {
      RCLCPP_WARN(this->get_logger(),
                  "Unknown outlier_mode '%s' (expected sor|radius|conditional). Defaulting to sor.",
                  outlier_mode_.c_str());
      outlier_mode_ = "sor";
      *cloud_outlier_selected_ = *cloud_sor_;
    }
  }

  // ---------- Param callback ----------
  rcl_interfaces::msg::SetParametersResult
  param_callback(const std::vector<rclcpp::Parameter> & params)
  {
    std::lock_guard<std::mutex> lock(mutex_);

    bool voxel_changed = false;
    bool outlier_changed = false;
    bool mode_changed = false;

    // Basic validation + update
    for (const auto & p : params)
    {
      const auto & name = p.get_name();

      if (name == "voxel_leaf") {
        const double v = p.as_double();
        if (v <= 0.0) return fail("voxel_leaf must be > 0");
        voxel_leaf_ = v;
        voxel_changed = true;
      }
      else if (name == "outlier_mode") {
        outlier_mode_ = p.as_string();
        mode_changed = true;
      }
      else if (name == "sor_mean_k") {
        const int v = p.as_int();
        if (v < 1) return fail("sor_mean_k must be >= 1");
        sor_mean_k_ = v;
        outlier_changed = true;
      }
      else if (name == "sor_stddev") {
        const double v = p.as_double();
        if (v <= 0.0) return fail("sor_stddev must be > 0");
        sor_stddev_ = v;
        outlier_changed = true;
      }
      else if (name == "ror_radius") {
        const double v = p.as_double();
        if (v <= 0.0) return fail("ror_radius must be > 0");
        ror_radius_ = v;
        outlier_changed = true;
      }
      else if (name == "ror_min_neighbors") {
        const int v = p.as_int();
        if (v < 0) return fail("ror_min_neighbors must be >= 0");
        ror_min_neighbors_ = v;
        outlier_changed = true;
      }
      else if (name == "cond_z_min") {
        cond_z_min_ = p.as_double();
        outlier_changed = true;
      }
      else if (name == "cond_z_max") {
        cond_z_max_ = p.as_double();
        outlier_changed = true;
      }
      else if (name == "keep_organized") {
        keep_organized_ = p.as_bool();
        outlier_changed = true;
      }
    }

    // Additional validation that depends on multiple params
    if (cond_z_max_ <= cond_z_min_) {
      return fail("cond_z_max must be > cond_z_min");
    }

    // Recompute what needs recomputing
    if (voxel_changed) {
      apply_voxel();
    }
    if (outlier_changed) {
      apply_all_outliers();
    } else if (mode_changed) {
      select_outlier_output();
    }

    rcl_interfaces::msg::SetParametersResult ok;
    ok.successful = true;
    return ok;
  }

  rcl_interfaces::msg::SetParametersResult fail(const std::string & msg)
  {
    rcl_interfaces::msg::SetParametersResult r;
    r.successful = false;
    r.reason = msg;
    return r;
  }

  // ---------- Publish ----------
  void publish_clouds()
  {
    std::lock_guard<std::mutex> lock(mutex_);
    const auto stamp = this->now();

    auto pub_cloud = [&](const auto & cloud,
                         const rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr & pub)
    {
      sensor_msgs::msg::PointCloud2 msg;
      pcl::toROSMsg(*cloud, msg);
      msg.header.frame_id = "map";
      msg.header.stamp = stamp;
      pub->publish(msg);
    };

    pub_cloud(cloud_raw_, pub_raw_);
    pub_cloud(cloud_voxel_, pub_voxel_);

    pub_cloud(cloud_sor_, pub_sor_);
    pub_cloud(cloud_ror_, pub_ror_);
    pub_cloud(cloud_cond_, pub_cond_);

    pub_cloud(cloud_outlier_selected_, pub_outlier_);
  }

  // ---------- Data ----------
  std::shared_ptr<pcl::PointCloud<pcl::PointXYZRGB>> cloud_raw_;
  std::shared_ptr<pcl::PointCloud<pcl::PointXYZRGB>> cloud_voxel_;

  std::shared_ptr<pcl::PointCloud<pcl::PointXYZRGB>> cloud_sor_;
  std::shared_ptr<pcl::PointCloud<pcl::PointXYZRGB>> cloud_ror_;
  std::shared_ptr<pcl::PointCloud<pcl::PointXYZRGB>> cloud_cond_;
  std::shared_ptr<pcl::PointCloud<pcl::PointXYZRGB>> cloud_outlier_selected_;

  double voxel_leaf_;
  std::string outlier_mode_;

  int sor_mean_k_;
  double sor_stddev_;

  double ror_radius_;
  int ror_min_neighbors_;

  double cond_z_min_;
  double cond_z_max_;

  bool keep_organized_;
  std::mutex mutex_;

  // ---------- ROS ----------
  rclcpp::TimerBase::SharedPtr timer_;

  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pub_raw_;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pub_voxel_;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pub_outlier_;

  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pub_sor_;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pub_ror_;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pub_cond_;

  rclcpp::node_interfaces::OnSetParametersCallbackHandle::SharedPtr param_callback_handle_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<PointCloudPublisher>());
  rclcpp::shutdown();
  return 0;
}