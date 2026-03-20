// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from save_pointcloud:msg/BoundingBoxCenter.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "save_pointcloud/msg/bounding_box_center.h"


#ifndef SAVE_POINTCLOUD__MSG__DETAIL__BOUNDING_BOX_CENTER__STRUCT_H_
#define SAVE_POINTCLOUD__MSG__DETAIL__BOUNDING_BOX_CENTER__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'center'
#include "geometry_msgs/msg/detail/point__struct.h"

/// Struct defined in msg/BoundingBoxCenter in the package save_pointcloud.
typedef struct save_pointcloud__msg__BoundingBoxCenter
{
  geometry_msgs__msg__Point center;
  int32_t x_min;
  int32_t y_min;
  int32_t x_max;
  int32_t y_max;
} save_pointcloud__msg__BoundingBoxCenter;

// Struct for a sequence of save_pointcloud__msg__BoundingBoxCenter.
typedef struct save_pointcloud__msg__BoundingBoxCenter__Sequence
{
  save_pointcloud__msg__BoundingBoxCenter * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} save_pointcloud__msg__BoundingBoxCenter__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SAVE_POINTCLOUD__MSG__DETAIL__BOUNDING_BOX_CENTER__STRUCT_H_
