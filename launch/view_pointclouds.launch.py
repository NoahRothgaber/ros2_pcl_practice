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
    )

    base_link_tf = Node(
        package="tf2_ros",
        executable="static_transform_publisher",
        arguments=[
            "0", "0", "0",
            "0", "0", "0",
            "map", "base_link"
        ],
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
        rviz,
    ])