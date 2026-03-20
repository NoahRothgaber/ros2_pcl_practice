// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from save_pointcloud:msg/BoundingBoxCenter.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "save_pointcloud/msg/bounding_box_center.hpp"


#ifndef SAVE_POINTCLOUD__MSG__DETAIL__BOUNDING_BOX_CENTER__TRAITS_HPP_
#define SAVE_POINTCLOUD__MSG__DETAIL__BOUNDING_BOX_CENTER__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "save_pointcloud/msg/detail/bounding_box_center__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'center'
#include "geometry_msgs/msg/detail/point__traits.hpp"

namespace save_pointcloud
{

namespace msg
{

inline void to_flow_style_yaml(
  const BoundingBoxCenter & msg,
  std::ostream & out)
{
  out << "{";
  // member: center
  {
    out << "center: ";
    to_flow_style_yaml(msg.center, out);
    out << ", ";
  }

  // member: x_min
  {
    out << "x_min: ";
    rosidl_generator_traits::value_to_yaml(msg.x_min, out);
    out << ", ";
  }

  // member: y_min
  {
    out << "y_min: ";
    rosidl_generator_traits::value_to_yaml(msg.y_min, out);
    out << ", ";
  }

  // member: x_max
  {
    out << "x_max: ";
    rosidl_generator_traits::value_to_yaml(msg.x_max, out);
    out << ", ";
  }

  // member: y_max
  {
    out << "y_max: ";
    rosidl_generator_traits::value_to_yaml(msg.y_max, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const BoundingBoxCenter & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: center
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "center:\n";
    to_block_style_yaml(msg.center, out, indentation + 2);
  }

  // member: x_min
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x_min: ";
    rosidl_generator_traits::value_to_yaml(msg.x_min, out);
    out << "\n";
  }

  // member: y_min
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y_min: ";
    rosidl_generator_traits::value_to_yaml(msg.y_min, out);
    out << "\n";
  }

  // member: x_max
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x_max: ";
    rosidl_generator_traits::value_to_yaml(msg.x_max, out);
    out << "\n";
  }

  // member: y_max
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y_max: ";
    rosidl_generator_traits::value_to_yaml(msg.y_max, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const BoundingBoxCenter & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace save_pointcloud

namespace rosidl_generator_traits
{

[[deprecated("use save_pointcloud::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const save_pointcloud::msg::BoundingBoxCenter & msg,
  std::ostream & out, size_t indentation = 0)
{
  save_pointcloud::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use save_pointcloud::msg::to_yaml() instead")]]
inline std::string to_yaml(const save_pointcloud::msg::BoundingBoxCenter & msg)
{
  return save_pointcloud::msg::to_yaml(msg);
}

template<>
inline const char * data_type<save_pointcloud::msg::BoundingBoxCenter>()
{
  return "save_pointcloud::msg::BoundingBoxCenter";
}

template<>
inline const char * name<save_pointcloud::msg::BoundingBoxCenter>()
{
  return "save_pointcloud/msg/BoundingBoxCenter";
}

template<>
struct has_fixed_size<save_pointcloud::msg::BoundingBoxCenter>
  : std::integral_constant<bool, has_fixed_size<geometry_msgs::msg::Point>::value> {};

template<>
struct has_bounded_size<save_pointcloud::msg::BoundingBoxCenter>
  : std::integral_constant<bool, has_bounded_size<geometry_msgs::msg::Point>::value> {};

template<>
struct is_message<save_pointcloud::msg::BoundingBoxCenter>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SAVE_POINTCLOUD__MSG__DETAIL__BOUNDING_BOX_CENTER__TRAITS_HPP_
