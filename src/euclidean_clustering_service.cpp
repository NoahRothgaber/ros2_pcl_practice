#include "rclcpp/rclcpp.hpp"

#include "save_pointcloud/srv/cluster_closest_to_point.hpp"

#include <sensor_msgs/msg/point_cloud2.hpp>
#include <pcl_msgs/msg/point_indices.hpp>

#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/search/kdtree.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/common/centroid.h>
#include <pcl/common/common.h>

#include <limits>
#include <cmath>
#include <vector>

class EuclideanClusteringService : public rclcpp::Node
{
public:
    EuclideanClusteringService()
    : Node("euclidean_clustering_service")
    {
        service_ = this->create_service<save_pointcloud::srv::ClusterClosestToPoint>(
            "euclidean_clustering",
            std::bind(
                &EuclideanClusteringService::cluster_callback,
                this,
                std::placeholders::_1,
                std::placeholders::_2));

        RCLCPP_INFO(this->get_logger(), "Euclidean clustering service ready.");
    }

private:
    void cluster_callback(
        const std::shared_ptr<save_pointcloud::srv::ClusterClosestToPoint::Request> request,
        std::shared_ptr<save_pointcloud::srv::ClusterClosestToPoint::Response> response)
    {
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
        pcl::fromROSMsg(request->input, *cloud);

        if (cloud->empty()) {
            RCLCPP_WARN(this->get_logger(), "Input cloud is empty.");
            return;
        }

        float cluster_tolerance = request->cluster_tolerance > 0.0f
            ? request->cluster_tolerance
            : 0.02f;

        int min_cluster_size = request->min_cluster_size > 0
            ? request->min_cluster_size
            : 100;

        int max_cluster_size = request->max_cluster_size > 0
            ? request->max_cluster_size
            : 25000;

        pcl::search::KdTree<pcl::PointXYZRGB>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZRGB>);
        tree->setInputCloud(cloud);

        std::vector<pcl::PointIndices> cluster_indices;

        pcl::EuclideanClusterExtraction<pcl::PointXYZRGB> ec;
        ec.setClusterTolerance(cluster_tolerance);
        ec.setMinClusterSize(min_cluster_size);
        ec.setMaxClusterSize(max_cluster_size);
        ec.setSearchMethod(tree);
        ec.setInputCloud(cloud);
        ec.extract(cluster_indices);

        if (cluster_indices.empty()) {
            RCLCPP_WARN(this->get_logger(), "No clusters found.");
            return;
        }

        const double target_x = request->camera_pose.pose.position.x;
        const double target_y = request->camera_pose.pose.position.y;
        const double target_z = request->camera_pose.pose.position.z;

        double best_distance = std::numeric_limits<double>::max();
        int best_cluster = -1;

        for (size_t i = 0; i < cluster_indices.size(); ++i) {
            Eigen::Vector4f centroid;
            pcl::compute3DCentroid(*cloud, cluster_indices[i].indices, centroid);

            const double dx = centroid[0] - target_x;
            const double dy = centroid[1] - target_y;
            const double dz = centroid[2] - target_z;
            const double distance = std::sqrt(dx * dx + dy * dy + dz * dz);

            RCLCPP_INFO(this->get_logger(),
                "Cluster %zu centroid: X=%.4f Y=%.4f Z=%.4f distance=%.4f",
                i, centroid[0], centroid[1], centroid[2], distance);

            if (distance < best_distance) {
                best_distance = distance;
                best_cluster = static_cast<int>(i);
            }
        }

        if (best_cluster < 0) {
            RCLCPP_WARN(this->get_logger(), "Could not select a target cluster.");
            return;
        }

        for (size_t i = 0; i < cluster_indices.size(); ++i) {
            pcl_msgs::msg::PointIndices ros_indices;
            ros_indices.header = request->input.header;
            ros_indices.indices = cluster_indices[i].indices;

            if (static_cast<int>(i) == best_cluster) {
                response->target_cluster_indices = ros_indices;
            } else {
                response->obstacle_cluster_indices.push_back(ros_indices);
            }
        }

        RCLCPP_INFO(this->get_logger(),
            "Selected cluster %d as target. Total clusters=%zu obstacles=%zu",
            best_cluster,
            cluster_indices.size(),
            response->obstacle_cluster_indices.size());
    }

    rclcpp::Service<save_pointcloud::srv::ClusterClosestToPoint>::SharedPtr service_;
};

int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<EuclideanClusteringService>());
    rclcpp::shutdown();
    return 0;
}