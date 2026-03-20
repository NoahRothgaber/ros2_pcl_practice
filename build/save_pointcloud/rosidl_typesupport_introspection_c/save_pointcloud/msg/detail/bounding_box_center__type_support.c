// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from save_pointcloud:msg/BoundingBoxCenter.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "save_pointcloud/msg/detail/bounding_box_center__rosidl_typesupport_introspection_c.h"
#include "save_pointcloud/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "save_pointcloud/msg/detail/bounding_box_center__functions.h"
#include "save_pointcloud/msg/detail/bounding_box_center__struct.h"


// Include directives for member types
// Member `center`
#include "geometry_msgs/msg/point.h"
// Member `center`
#include "geometry_msgs/msg/detail/point__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void save_pointcloud__msg__BoundingBoxCenter__rosidl_typesupport_introspection_c__BoundingBoxCenter_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  save_pointcloud__msg__BoundingBoxCenter__init(message_memory);
}

void save_pointcloud__msg__BoundingBoxCenter__rosidl_typesupport_introspection_c__BoundingBoxCenter_fini_function(void * message_memory)
{
  save_pointcloud__msg__BoundingBoxCenter__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember save_pointcloud__msg__BoundingBoxCenter__rosidl_typesupport_introspection_c__BoundingBoxCenter_message_member_array[5] = {
  {
    "center",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(save_pointcloud__msg__BoundingBoxCenter, center),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "x_min",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(save_pointcloud__msg__BoundingBoxCenter, x_min),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "y_min",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(save_pointcloud__msg__BoundingBoxCenter, y_min),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "x_max",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(save_pointcloud__msg__BoundingBoxCenter, x_max),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "y_max",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(save_pointcloud__msg__BoundingBoxCenter, y_max),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers save_pointcloud__msg__BoundingBoxCenter__rosidl_typesupport_introspection_c__BoundingBoxCenter_message_members = {
  "save_pointcloud__msg",  // message namespace
  "BoundingBoxCenter",  // message name
  5,  // number of fields
  sizeof(save_pointcloud__msg__BoundingBoxCenter),
  false,  // has_any_key_member_
  save_pointcloud__msg__BoundingBoxCenter__rosidl_typesupport_introspection_c__BoundingBoxCenter_message_member_array,  // message members
  save_pointcloud__msg__BoundingBoxCenter__rosidl_typesupport_introspection_c__BoundingBoxCenter_init_function,  // function to initialize message memory (memory has to be allocated)
  save_pointcloud__msg__BoundingBoxCenter__rosidl_typesupport_introspection_c__BoundingBoxCenter_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t save_pointcloud__msg__BoundingBoxCenter__rosidl_typesupport_introspection_c__BoundingBoxCenter_message_type_support_handle = {
  0,
  &save_pointcloud__msg__BoundingBoxCenter__rosidl_typesupport_introspection_c__BoundingBoxCenter_message_members,
  get_message_typesupport_handle_function,
  &save_pointcloud__msg__BoundingBoxCenter__get_type_hash,
  &save_pointcloud__msg__BoundingBoxCenter__get_type_description,
  &save_pointcloud__msg__BoundingBoxCenter__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_save_pointcloud
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, save_pointcloud, msg, BoundingBoxCenter)() {
  save_pointcloud__msg__BoundingBoxCenter__rosidl_typesupport_introspection_c__BoundingBoxCenter_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Point)();
  if (!save_pointcloud__msg__BoundingBoxCenter__rosidl_typesupport_introspection_c__BoundingBoxCenter_message_type_support_handle.typesupport_identifier) {
    save_pointcloud__msg__BoundingBoxCenter__rosidl_typesupport_introspection_c__BoundingBoxCenter_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &save_pointcloud__msg__BoundingBoxCenter__rosidl_typesupport_introspection_c__BoundingBoxCenter_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
