from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os


pkg_share = get_package_share_directory("save_pointcloud")
rviz_config = os.path.join(pkg_share, "rviz", "pointclouds.rviz")


def generate_launch_description():
    cropped_and_original_tf = Node(
        package="tf2_ros",
        executable="static_transform_publisher",
        arguments=[
            "0", "0", "0",
            "0", "0", "0",
            "map", "camera_depth_optical_frame"
        ],
        output="screen",
    )

    base_link_tf = Node(
        package="tf2_ros",
        executable="static_transform_publisher",
        arguments=[
            "0", "0", "0",
            "0", "0", "0",
            "map", "base_link"
        ],
        output="screen",
    )

    center_point_subscriber = Node(
        package="save_pointcloud",
        executable="center_point_subscriber",
        output="screen",
    )

    center_point_publisher = Node(
        package="save_pointcloud",
        executable="center_point_publisher.py",
        output="screen",
    )

    passthrough_filter_node = Node(
        package="save_pointcloud",
        executable="passthrough_filter_node",
        name="passthrough_filter_node",
        parameters=[{
            "input_topic": "/cropped_pointcloud",
            "filter_field_name": "z",
            "limit_min": 0.35,
            "limit_max": 0.65
        }],
        output="screen",
    )

    filtered_cloud_node = Node(
        package="save_pointcloud",
        executable="filtered_cloud_node",
        name="filtered_cloud_node",
        parameters=[{
            "input_topic": "/passthrough_cloud",
            "distance_threshold": 0.005,
            "optimize_coefficients": True
        }],
        output="screen",
    )

    statistical_outlier_removal_node = Node(
        package="save_pointcloud",
        executable="statistical_outlier_removal_node",
        name="statistical_outlier_removal_node",
        parameters=[{
            "input_topic": "/filtered_cloud",
            "mean_k": 20,
            "stddev_mul_thresh": 1.0
        }],
        output="screen",
    )

    voxel_grid_filter_node = Node(
        package="save_pointcloud",
        executable="voxel_grid_filter_node",
        name="voxel_grid_filter_node",
        parameters=[{
            "input_topic": "/sor_cloud",
            "leaf_size": 0.005
        }],
        output="screen",
    )

    rviz = Node(
        package="rviz2",
        executable="rviz2",
        arguments=["-d", rviz_config],
        output="screen",
    )

    return LaunchDescription([
        cropped_and_original_tf,
        base_link_tf,
        center_point_subscriber,
        center_point_publisher,
        passthrough_filter_node,
        filtered_cloud_node,
        statistical_outlier_removal_node,
        voxel_grid_filter_node,
        rviz,
    ])