#include "rclcpp/rclcpp.hpp"
#include "save_pointcloud/srv/cluster_closest_to_point.hpp"

#include <sensor_msgs/msg/point_cloud2.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <pcl_msgs/msg/point_indices.hpp>

#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/filters/extract_indices.h>

#include <chrono>
#include <memory>
#include <string>
#include <vector>

using namespace std::chrono_literals;

class ClusterClosestToPointClient : public rclcpp::Node
{
public:
    ClusterClosestToPointClient()
    : Node("cluster_closest_to_point_client")
    {
        cloud_sub_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
            "/sor_cloud",
            rclcpp::SensorDataQoS(),
            std::bind(&ClusterClosestToPointClient::cloud_callback, this, std::placeholders::_1));
        
        target_pose_sub_ = this->create_subscription<geometry_msgs::msg::PoseStamped>(
            "/bbox_target_pose",
            rclcpp::QoS(1).transient_local().reliable(),
            std::bind(&ClusterClosestToPointClient::target_pose_callback, this, std::placeholders::_1));

        target_cloud_pub_ = this->create_publisher<sensor_msgs::msg::PointCloud2>(
            "/target_cluster_cloud",
            10);

        obstacle_cloud_pub_ = this->create_publisher<sensor_msgs::msg::PointCloud2>(
            "/obstacle_clusters_cloud",
            10);

        client_ = this->create_client<save_pointcloud::srv::ClusterClosestToPoint>(
            "euclidean_clustering");

        timer_ = this->create_wall_timer(
            500ms,
            std::bind(&ClusterClosestToPointClient::try_call_service, this));

        RCLCPP_INFO(this->get_logger(), "ClusterClosestToPoint client ready.");
    }

private:
    void cloud_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
    {
        latest_cloud_ = msg;
    }

    void target_pose_callback(const geometry_msgs::msg::PoseStamped::SharedPtr msg)
    {
        latest_target_pose_ = msg;

        RCLCPP_INFO(this->get_logger(),
            "Received target pose: X=%.4f Y=%.4f Z=%.4f",
            msg->pose.position.x,
            msg->pose.position.y,
            msg->pose.position.z);
    }

    void try_call_service()
    {
        if (request_in_progress_) {
            return;
        }

        if (!latest_cloud_) {
            RCLCPP_WARN_THROTTLE(
                this->get_logger(),
                *this->get_clock(),
                2000,
                "Waiting for /sor_cloud...");
            return;
        }

        if (!latest_target_pose_) {
            RCLCPP_WARN_THROTTLE(
                this->get_logger(),
                *this->get_clock(),
                2000,
                "Waiting for /bbox_target_pose...");
            return;
        }

        if (!client_->wait_for_service(0s)) {
            RCLCPP_WARN_THROTTLE(
                this->get_logger(),
                *this->get_clock(),
                2000,
                "Waiting for euclidean_clustering service...");
            return;
        }

        auto request = std::make_shared<save_pointcloud::srv::ClusterClosestToPoint::Request>();

        request->input = *latest_cloud_;
        request->camera_pose = *latest_target_pose_;

        request->cluster_tolerance = 0.02f;
        request->min_cluster_size = 100;
        request->max_cluster_size = 25000;

        request_in_progress_ = true;

        RCLCPP_INFO(this->get_logger(), "Calling euclidean_clustering service...");

        client_->async_send_request(
            request,
            std::bind(
                &ClusterClosestToPointClient::service_response_callback,
                this,
                std::placeholders::_1));
    }

    void service_response_callback(
        rclcpp::Client<save_pointcloud::srv::ClusterClosestToPoint>::SharedFuture future)
    {
        request_in_progress_ = false;

        auto response = future.get();

        RCLCPP_INFO(this->get_logger(),
            "Got response. Target indices=%zu, obstacle clusters=%zu",
            response->target_cluster_indices.indices.size(),
            response->obstacle_cluster_indices.size());

        publish_cluster_clouds(response);
    }

    void publish_cluster_clouds(
        const std::shared_ptr<save_pointcloud::srv::ClusterClosestToPoint::Response> response)
    {
        if (!latest_cloud_) {
            return;
        }

        pcl::PointCloud<pcl::PointXYZRGB>::Ptr full_cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
        pcl::fromROSMsg(*latest_cloud_, *full_cloud);

        if (full_cloud->empty()) {
            RCLCPP_WARN(this->get_logger(), "Latest cloud is empty.");
            return;
        }

        publish_single_cluster(
            full_cloud,
            response->target_cluster_indices,
            target_cloud_pub_,
            "target");

        publish_obstacle_clusters(
            full_cloud,
            response->obstacle_cluster_indices);
    }

    void publish_single_cluster(
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr full_cloud,
        const pcl_msgs::msg::PointIndices & indices_msg,
        rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr publisher,
        const std::string & label)
    {
        if (indices_msg.indices.empty()) {
            RCLCPP_WARN(this->get_logger(), "%s cluster has no indices.", label.c_str());
            return;
        }

        pcl::PointIndices::Ptr pcl_indices(new pcl::PointIndices);
        pcl_indices->indices = indices_msg.indices;

        pcl::PointCloud<pcl::PointXYZRGB>::Ptr extracted_cloud(new pcl::PointCloud<pcl::PointXYZRGB>);

        pcl::ExtractIndices<pcl::PointXYZRGB> extract;
        extract.setInputCloud(full_cloud);
        extract.setIndices(pcl_indices);
        extract.setNegative(false);
        extract.filter(*extracted_cloud);

        sensor_msgs::msg::PointCloud2 output_msg;
        pcl::toROSMsg(*extracted_cloud, output_msg);
        output_msg.header = latest_cloud_->header;

        publisher->publish(output_msg);

        RCLCPP_INFO(this->get_logger(),
            "Published %s cluster cloud with %zu points.",
            label.c_str(),
            extracted_cloud->size());
    }

    void publish_obstacle_clusters(
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr full_cloud,
        const std::vector<pcl_msgs::msg::PointIndices> & obstacle_indices)
    {
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr combined_obstacles(new pcl::PointCloud<pcl::PointXYZRGB>);

        for (const auto & cluster_indices_msg : obstacle_indices) {
            pcl::PointIndices::Ptr pcl_indices(new pcl::PointIndices);
            pcl_indices->indices = cluster_indices_msg.indices;

            pcl::PointCloud<pcl::PointXYZRGB>::Ptr single_obstacle(new pcl::PointCloud<pcl::PointXYZRGB>);

            pcl::ExtractIndices<pcl::PointXYZRGB> extract;
            extract.setInputCloud(full_cloud);
            extract.setIndices(pcl_indices);
            extract.setNegative(false);
            extract.filter(*single_obstacle);

            *combined_obstacles += *single_obstacle;
        }

        if (combined_obstacles->empty()) {
            RCLCPP_WARN(this->get_logger(), "No obstacle cloud points to publish.");
            return;
        }

        sensor_msgs::msg::PointCloud2 output_msg;
        pcl::toROSMsg(*combined_obstacles, output_msg);
        output_msg.header = latest_cloud_->header;

        obstacle_cloud_pub_->publish(output_msg);

        RCLCPP_INFO(this->get_logger(),
            "Published obstacle cloud with %zu points.",
            combined_obstacles->size());
    }

    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr cloud_sub_;
    rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr target_pose_sub_;

    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr target_cloud_pub_;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr obstacle_cloud_pub_;

    rclcpp::Client<save_pointcloud::srv::ClusterClosestToPoint>::SharedPtr client_;

    rclcpp::TimerBase::SharedPtr timer_;

    sensor_msgs::msg::PointCloud2::SharedPtr latest_cloud_;
    geometry_msgs::msg::PoseStamped::SharedPtr latest_target_pose_;

    bool request_in_progress_ = false;
};

int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ClusterClosestToPointClient>());
    rclcpp::shutdown();
    return 0;
}