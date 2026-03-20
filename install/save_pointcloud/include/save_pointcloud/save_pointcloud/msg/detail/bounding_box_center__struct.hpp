// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from save_pointcloud:msg/BoundingBoxCenter.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "save_pointcloud/msg/bounding_box_center.hpp"


#ifndef SAVE_POINTCLOUD__MSG__DETAIL__BOUNDING_BOX_CENTER__STRUCT_HPP_
#define SAVE_POINTCLOUD__MSG__DETAIL__BOUNDING_BOX_CENTER__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'center'
#include "geometry_msgs/msg/detail/point__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__save_pointcloud__msg__BoundingBoxCenter __attribute__((deprecated))
#else
# define DEPRECATED__save_pointcloud__msg__BoundingBoxCenter __declspec(deprecated)
#endif

namespace save_pointcloud
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct BoundingBoxCenter_
{
  using Type = BoundingBoxCenter_<ContainerAllocator>;

  explicit BoundingBoxCenter_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : center(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->x_min = 0l;
      this->y_min = 0l;
      this->x_max = 0l;
      this->y_max = 0l;
    }
  }

  explicit BoundingBoxCenter_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : center(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->x_min = 0l;
      this->y_min = 0l;
      this->x_max = 0l;
      this->y_max = 0l;
    }
  }

  // field types and members
  using _center_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _center_type center;
  using _x_min_type =
    int32_t;
  _x_min_type x_min;
  using _y_min_type =
    int32_t;
  _y_min_type y_min;
  using _x_max_type =
    int32_t;
  _x_max_type x_max;
  using _y_max_type =
    int32_t;
  _y_max_type y_max;

  // setters for named parameter idiom
  Type & set__center(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->center = _arg;
    return *this;
  }
  Type & set__x_min(
    const int32_t & _arg)
  {
    this->x_min = _arg;
    return *this;
  }
  Type & set__y_min(
    const int32_t & _arg)
  {
    this->y_min = _arg;
    return *this;
  }
  Type & set__x_max(
    const int32_t & _arg)
  {
    this->x_max = _arg;
    return *this;
  }
  Type & set__y_max(
    const int32_t & _arg)
  {
    this->y_max = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    save_pointcloud::msg::BoundingBoxCenter_<ContainerAllocator> *;
  using ConstRawPtr =
    const save_pointcloud::msg::BoundingBoxCenter_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<save_pointcloud::msg::BoundingBoxCenter_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<save_pointcloud::msg::BoundingBoxCenter_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      save_pointcloud::msg::BoundingBoxCenter_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<save_pointcloud::msg::BoundingBoxCenter_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      save_pointcloud::msg::BoundingBoxCenter_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<save_pointcloud::msg::BoundingBoxCenter_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<save_pointcloud::msg::BoundingBoxCenter_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<save_pointcloud::msg::BoundingBoxCenter_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__save_pointcloud__msg__BoundingBoxCenter
    std::shared_ptr<save_pointcloud::msg::BoundingBoxCenter_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__save_pointcloud__msg__BoundingBoxCenter
    std::shared_ptr<save_pointcloud::msg::BoundingBoxCenter_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const BoundingBoxCenter_ & other) const
  {
    if (this->center != other.center) {
      return false;
    }
    if (this->x_min != other.x_min) {
      return false;
    }
    if (this->y_min != other.y_min) {
      return false;
    }
    if (this->x_max != other.x_max) {
      return false;
    }
    if (this->y_max != other.y_max) {
      return false;
    }
    return true;
  }
  bool operator!=(const BoundingBoxCenter_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct BoundingBoxCenter_

// alias to use template instance with default allocator
using BoundingBoxCenter =
  save_pointcloud::msg::BoundingBoxCenter_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace save_pointcloud

#endif  // SAVE_POINTCLOUD__MSG__DETAIL__BOUNDING_BOX_CENTER__STRUCT_HPP_
