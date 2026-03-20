cmake_minimum_required(VERSION 3.10)
project(pcd_to_image)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PCL REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(
    ${PCL_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
)

link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable(pcd_to_image derive_rgb_image_from_pcd.cpp)

target_link_libraries(pcd_to_image
    ${PCL_LIBRARIES}
    ${OpenCV_LIBS}
)