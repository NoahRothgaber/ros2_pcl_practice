// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from save_pointcloud:msg/BoundingBoxCenter.idl
// generated code does not contain a copyright notice
#ifndef SAVE_POINTCLOUD__MSG__DETAIL__BOUNDING_BOX_CENTER__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define SAVE_POINTCLOUD__MSG__DETAIL__BOUNDING_BOX_CENTER__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "save_pointcloud/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "save_pointcloud/msg/detail/bounding_box_center__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_save_pointcloud
bool cdr_serialize_save_pointcloud__msg__BoundingBoxCenter(
  const save_pointcloud__msg__BoundingBoxCenter * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_save_pointcloud
bool cdr_deserialize_save_pointcloud__msg__BoundingBoxCenter(
  eprosima::fastcdr::Cdr &,
  save_pointcloud__msg__BoundingBoxCenter * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_save_pointcloud
size_t get_serialized_size_save_pointcloud__msg__BoundingBoxCenter(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_save_pointcloud
size_t max_serialized_size_save_pointcloud__msg__BoundingBoxCenter(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_save_pointcloud
bool cdr_serialize_key_save_pointcloud__msg__BoundingBoxCenter(
  const save_pointcloud__msg__BoundingBoxCenter * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_save_pointcloud
size_t get_serialized_size_key_save_pointcloud__msg__BoundingBoxCenter(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_save_pointcloud
size_t max_serialized_size_key_save_pointcloud__msg__BoundingBoxCenter(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_save_pointcloud
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, save_pointcloud, msg, BoundingBoxCenter)();

#ifdef __cplusplus
}
#endif

#endif  // SAVE_POINTCLOUD__MSG__DETAIL__BOUNDING_BOX_CENTER__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
