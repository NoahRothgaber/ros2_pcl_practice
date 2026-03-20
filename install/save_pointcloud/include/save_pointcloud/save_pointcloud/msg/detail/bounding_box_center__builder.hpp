// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from save_pointcloud:msg/BoundingBoxCenter.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "save_pointcloud/msg/bounding_box_center.hpp"


#ifndef SAVE_POINTCLOUD__MSG__DETAIL__BOUNDING_BOX_CENTER__BUILDER_HPP_
#define SAVE_POINTCLOUD__MSG__DETAIL__BOUNDING_BOX_CENTER__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "save_pointcloud/msg/detail/bounding_box_center__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace save_pointcloud
{

namespace msg
{

namespace builder
{

class Init_BoundingBoxCenter_y_max
{
public:
  explicit Init_BoundingBoxCenter_y_max(::save_pointcloud::msg::BoundingBoxCenter & msg)
  : msg_(msg)
  {}
  ::save_pointcloud::msg::BoundingBoxCenter y_max(::save_pointcloud::msg::BoundingBoxCenter::_y_max_type arg)
  {
    msg_.y_max = std::move(arg);
    return std::move(msg_);
  }

private:
  ::save_pointcloud::msg::BoundingBoxCenter msg_;
};

class Init_BoundingBoxCenter_x_max
{
public:
  explicit Init_BoundingBoxCenter_x_max(::save_pointcloud::msg::BoundingBoxCenter & msg)
  : msg_(msg)
  {}
  Init_BoundingBoxCenter_y_max x_max(::save_pointcloud::msg::BoundingBoxCenter::_x_max_type arg)
  {
    msg_.x_max = std::move(arg);
    return Init_BoundingBoxCenter_y_max(msg_);
  }

private:
  ::save_pointcloud::msg::BoundingBoxCenter msg_;
};

class Init_BoundingBoxCenter_y_min
{
public:
  explicit Init_BoundingBoxCenter_y_min(::save_pointcloud::msg::BoundingBoxCenter & msg)
  : msg_(msg)
  {}
  Init_BoundingBoxCenter_x_max y_min(::save_pointcloud::msg::BoundingBoxCenter::_y_min_type arg)
  {
    msg_.y_min = std::move(arg);
    return Init_BoundingBoxCenter_x_max(msg_);
  }

private:
  ::save_pointcloud::msg::BoundingBoxCenter msg_;
};

class Init_BoundingBoxCenter_x_min
{
public:
  explicit Init_BoundingBoxCenter_x_min(::save_pointcloud::msg::BoundingBoxCenter & msg)
  : msg_(msg)
  {}
  Init_BoundingBoxCenter_y_min x_min(::save_pointcloud::msg::BoundingBoxCenter::_x_min_type arg)
  {
    msg_.x_min = std::move(arg);
    return Init_BoundingBoxCenter_y_min(msg_);
  }

private:
  ::save_pointcloud::msg::BoundingBoxCenter msg_;
};

class Init_BoundingBoxCenter_center
{
public:
  Init_BoundingBoxCenter_center()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_BoundingBoxCenter_x_min center(::save_pointcloud::msg::BoundingBoxCenter::_center_type arg)
  {
    msg_.center = std::move(arg);
    return Init_BoundingBoxCenter_x_min(msg_);
  }

private:
  ::save_pointcloud::msg::BoundingBoxCenter msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::save_pointcloud::msg::BoundingBoxCenter>()
{
  return save_pointcloud::msg::builder::Init_BoundingBoxCenter_center();
}

}  // namespace save_pointcloud

#endif  // SAVE_POINTCLOUD__MSG__DETAIL__BOUNDING_BOX_CENTER__BUILDER_HPP_
