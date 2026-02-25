cmake_minimum_required(VERSION 3.8)
project(save_pointcloud)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_srvs REQUIRED)

find_package(PCL REQUIRED COMPONENTS common filters io)
find_package(pcl_conversions REQUIRED)

add_executable(pointcloud_subscriber src/save_pointcloud_subscriber.cpp)
add_executable(pointcloud_server     src/save_pointcloud_server.cpp)
add_executable(pointcloud_client     src/save_pointcloud_client.cpp)
add_executable(pointcloud_publisher  src/point_cloud_publisher.cpp)

# -------- pointcloud_subscriber --------
ament_target_dependencies(pointcloud_subscriber
  rclcpp
  sensor_msgs
  pcl_conversions
)
target_include_directories(pointcloud_subscriber PRIVATE ${PCL_INCLUDE_DIRS})
target_link_libraries(pointcloud_subscriber ${PCL_LIBRARIES})
target_compile_definitions(pointcloud_subscriber PRIVATE ${PCL_DEFINITIONS})

# -------- pointcloud_server --------
ament_target_dependencies(pointcloud_server
  rclcpp
  sensor_msgs
  std_srvs
  pcl_conversions
)
target_include_directories(pointcloud_server PRIVATE ${PCL_INCLUDE_DIRS})
target_link_libraries(pointcloud_server ${PCL_LIBRARIES})
target_compile_definitions(pointcloud_server PRIVATE ${PCL_DEFINITIONS})

# -------- pointcloud_client --------
ament_target_dependencies(pointcloud_client
  rclcpp
  std_srvs
)

# -------- pointcloud_publisher --------
ament_target_dependencies(pointcloud_publisher
  rclcpp
  sensor_msgs
  pcl_conversions
)
target_include_directories(pointcloud_publisher PRIVATE ${PCL_INCLUDE_DIRS})
target_link_libraries(pointcloud_publisher ${PCL_LIBRARIES})
target_compile_definitions(pointcloud_publisher PRIVATE ${PCL_DEFINITIONS})

install(TARGETS
  pointcloud_subscriber
  pointcloud_server
  pointcloud_client
  pointcloud_publisher
  DESTINATION lib/${PROJECT_NAME}
)

ament_package() 