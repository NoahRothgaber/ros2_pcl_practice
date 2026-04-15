cmake_minimum_required(VERSION 3.8)
project(save_pointcloud)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_srvs REQUIRED)
find_package(OpenCV REQUIRED)
find_package(PCL REQUIRED COMPONENTS common filters io segmentation sample_consensus)
find_package(pcl_conversions REQUIRED)
find_package(pcl_msgs REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/BoundingBoxCenter.msg"
  "srv/ClusterClosestToPoint.srv"
  DEPENDENCIES geometry_msgs sensor_msgs pcl_msgs
)

rosidl_get_typesupport_target(cpp_typesupport_target ${PROJECT_NAME} "rosidl_typesupport_cpp")

add_executable(pointcloud_subscriber src/save_pointcloud_subscriber.cpp)
add_executable(pointcloud_server src/save_pointcloud_server.cpp)
add_executable(pointcloud_client src/save_pointcloud_client.cpp)
add_executable(pointcloud_publisher src/point_cloud_publisher.cpp)
add_executable(center_point_subscriber src/center_point_subscriber.cpp)
add_executable(planar_segmentation_node src/planar_segmentation_node.cpp)
add_executable(passthrough_filter_node src/passthrough_filter_node.cpp)
add_executable(filtered_cloud_node src/filtered_cloud_node.cpp)
add_executable(statistical_outlier_removal_node src/statistical_outlier_removal_node.cpp)
add_executable(voxel_grid_filter_node src/voxel_grid_filter_node.cpp)
add_executable(euclidean_clustering_service src/euclidean_clustering_service.cpp)
add_executable(cluster_closest_to_point_client src/cluster_closest_to_point_client.cpp)

ament_target_dependencies(cluster_closest_to_point_client
  rclcpp
  sensor_msgs
  geometry_msgs
  pcl_msgs
  pcl_conversions
)

target_include_directories(cluster_closest_to_point_client PRIVATE ${PCL_INCLUDE_DIRS})

target_link_libraries(cluster_closest_to_point_client
  ${PCL_LIBRARIES}
  ${cpp_typesupport_target}
)

target_compile_definitions(cluster_closest_to_point_client PRIVATE ${PCL_DEFINITIONS})

ament_target_dependencies(euclidean_clustering_service
  rclcpp
  sensor_msgs
  geometry_msgs
  pcl_msgs
  pcl_conversions
)

target_include_directories(euclidean_clustering_service PRIVATE ${PCL_INCLUDE_DIRS})

target_link_libraries(euclidean_clustering_service
  ${PCL_LIBRARIES}
  ${cpp_typesupport_target}
)

target_compile_definitions(euclidean_clustering_service PRIVATE ${PCL_DEFINITIONS})
# pointcloud_subscriber
ament_target_dependencies(pointcloud_subscriber
  rclcpp
  sensor_msgs
  pcl_conversions
)
target_include_directories(pointcloud_subscriber PRIVATE ${PCL_INCLUDE_DIRS})
target_link_libraries(pointcloud_subscriber ${PCL_LIBRARIES})
target_compile_definitions(pointcloud_subscriber PRIVATE ${PCL_DEFINITIONS})

# pointcloud_server
ament_target_dependencies(pointcloud_server
  rclcpp
  sensor_msgs
  std_srvs
  pcl_conversions
)
target_include_directories(pointcloud_server PRIVATE ${PCL_INCLUDE_DIRS})
target_link_libraries(pointcloud_server ${PCL_LIBRARIES} ${OpenCV_LIBS})
target_compile_definitions(pointcloud_server PRIVATE ${PCL_DEFINITIONS})

# pointcloud_client
ament_target_dependencies(pointcloud_client
  rclcpp
  std_srvs
)

# pointcloud_publisher
ament_target_dependencies(pointcloud_publisher
  rclcpp
  sensor_msgs
  pcl_conversions
)
target_include_directories(pointcloud_publisher PRIVATE ${PCL_INCLUDE_DIRS})
target_link_libraries(pointcloud_publisher ${PCL_LIBRARIES})
target_compile_definitions(pointcloud_publisher PRIVATE ${PCL_DEFINITIONS})

# center_point_subscriber
ament_target_dependencies(center_point_subscriber
  rclcpp
  geometry_msgs
  sensor_msgs
  pcl_conversions
)
target_include_directories(center_point_subscriber PRIVATE ${PCL_INCLUDE_DIRS})
target_link_libraries(center_point_subscriber
  ${PCL_LIBRARIES}
  ${cpp_typesupport_target}
)
target_compile_definitions(center_point_subscriber PRIVATE ${PCL_DEFINITIONS})

# planar_segmentation_node
ament_target_dependencies(planar_segmentation_node
  rclcpp
  sensor_msgs
  pcl_conversions
)
target_include_directories(planar_segmentation_node PRIVATE ${PCL_INCLUDE_DIRS})
target_link_libraries(planar_segmentation_node ${PCL_LIBRARIES})
target_compile_definitions(planar_segmentation_node PRIVATE ${PCL_DEFINITIONS})

# passthrough_filter_node
ament_target_dependencies(passthrough_filter_node
  rclcpp
  sensor_msgs
  pcl_conversions
)
target_include_directories(passthrough_filter_node PRIVATE ${PCL_INCLUDE_DIRS})
target_link_libraries(passthrough_filter_node ${PCL_LIBRARIES})
target_compile_definitions(passthrough_filter_node PRIVATE ${PCL_DEFINITIONS})

# filtered_cloud_node
ament_target_dependencies(filtered_cloud_node
  rclcpp
  sensor_msgs
  pcl_conversions
)
target_include_directories(filtered_cloud_node PRIVATE ${PCL_INCLUDE_DIRS})
target_link_libraries(filtered_cloud_node ${PCL_LIBRARIES})
target_compile_definitions(filtered_cloud_node PRIVATE ${PCL_DEFINITIONS})

# statistical_outlier_removal_node
ament_target_dependencies(statistical_outlier_removal_node
  rclcpp
  sensor_msgs
  pcl_conversions
)
target_include_directories(statistical_outlier_removal_node PRIVATE ${PCL_INCLUDE_DIRS})
target_link_libraries(statistical_outlier_removal_node ${PCL_LIBRARIES})
target_compile_definitions(statistical_outlier_removal_node PRIVATE ${PCL_DEFINITIONS})

# voxel_grid_filter_node
ament_target_dependencies(voxel_grid_filter_node
  rclcpp
  sensor_msgs
  pcl_conversions
)
target_include_directories(voxel_grid_filter_node PRIVATE ${PCL_INCLUDE_DIRS})
target_link_libraries(voxel_grid_filter_node ${PCL_LIBRARIES})
target_compile_definitions(voxel_grid_filter_node PRIVATE ${PCL_DEFINITIONS})

install(TARGETS
  pointcloud_subscriber
  pointcloud_server
  pointcloud_client
  pointcloud_publisher
  center_point_subscriber
  planar_segmentation_node
  passthrough_filter_node
  filtered_cloud_node
  statistical_outlier_removal_node
  voxel_grid_filter_node
  euclidean_clustering_service
  cluster_closest_to_point_client
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  launch
  rviz
  DESTINATION share/${PROJECT_NAME}
)

install(PROGRAMS
  scripts/center_point_publisher.py
  DESTINATION lib/${PROJECT_NAME}
)

ament_export_dependencies(rosidl_default_runtime)

ament_package()