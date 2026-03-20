// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from save_pointcloud:msg/BoundingBoxCenter.idl
// generated code does not contain a copyright notice
#include "save_pointcloud/msg/detail/bounding_box_center__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <cstddef>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/serialization_helpers.hpp"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "save_pointcloud/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "save_pointcloud/msg/detail/bounding_box_center__struct.h"
#include "save_pointcloud/msg/detail/bounding_box_center__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "geometry_msgs/msg/detail/point__functions.h"  // center

// forward declare type support functions

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_save_pointcloud
bool cdr_serialize_geometry_msgs__msg__Point(
  const geometry_msgs__msg__Point * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_save_pointcloud
bool cdr_deserialize_geometry_msgs__msg__Point(
  eprosima::fastcdr::Cdr & cdr,
  geometry_msgs__msg__Point * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_save_pointcloud
size_t get_serialized_size_geometry_msgs__msg__Point(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_save_pointcloud
size_t max_serialized_size_geometry_msgs__msg__Point(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_save_pointcloud
bool cdr_serialize_key_geometry_msgs__msg__Point(
  const geometry_msgs__msg__Point * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_save_pointcloud
size_t get_serialized_size_key_geometry_msgs__msg__Point(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_save_pointcloud
size_t max_serialized_size_key_geometry_msgs__msg__Point(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_save_pointcloud
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, geometry_msgs, msg, Point)();


using _BoundingBoxCenter__ros_msg_type = save_pointcloud__msg__BoundingBoxCenter;


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_save_pointcloud
bool cdr_serialize_save_pointcloud__msg__BoundingBoxCenter(
  const save_pointcloud__msg__BoundingBoxCenter * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: center
  {
    cdr_serialize_geometry_msgs__msg__Point(
      &ros_message->center, cdr);
  }

  // Field name: x_min
  {
    cdr << ros_message->x_min;
  }

  // Field name: y_min
  {
    cdr << ros_message->y_min;
  }

  // Field name: x_max
  {
    cdr << ros_message->x_max;
  }

  // Field name: y_max
  {
    cdr << ros_message->y_max;
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_save_pointcloud
bool cdr_deserialize_save_pointcloud__msg__BoundingBoxCenter(
  eprosima::fastcdr::Cdr & cdr,
  save_pointcloud__msg__BoundingBoxCenter * ros_message)
{
  // Field name: center
  {
    cdr_deserialize_geometry_msgs__msg__Point(cdr, &ros_message->center);
  }

  // Field name: x_min
  {
    cdr >> ros_message->x_min;
  }

  // Field name: y_min
  {
    cdr >> ros_message->y_min;
  }

  // Field name: x_max
  {
    cdr >> ros_message->x_max;
  }

  // Field name: y_max
  {
    cdr >> ros_message->y_max;
  }

  return true;
}  // NOLINT(readability/fn_size)


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_save_pointcloud
size_t get_serialized_size_save_pointcloud__msg__BoundingBoxCenter(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _BoundingBoxCenter__ros_msg_type * ros_message = static_cast<const _BoundingBoxCenter__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: center
  current_alignment += get_serialized_size_geometry_msgs__msg__Point(
    &(ros_message->center), current_alignment);

  // Field name: x_min
  {
    size_t item_size = sizeof(ros_message->x_min);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: y_min
  {
    size_t item_size = sizeof(ros_message->y_min);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: x_max
  {
    size_t item_size = sizeof(ros_message->x_max);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: y_max
  {
    size_t item_size = sizeof(ros_message->y_max);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_save_pointcloud
size_t max_serialized_size_save_pointcloud__msg__BoundingBoxCenter(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // Field name: center
  {
    size_t array_size = 1;
    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_geometry_msgs__msg__Point(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  // Field name: x_min
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: y_min
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: x_max
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: y_max
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }


  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = save_pointcloud__msg__BoundingBoxCenter;
    is_plain =
      (
      offsetof(DataType, y_max) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_save_pointcloud
bool cdr_serialize_key_save_pointcloud__msg__BoundingBoxCenter(
  const save_pointcloud__msg__BoundingBoxCenter * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: center
  {
    cdr_serialize_key_geometry_msgs__msg__Point(
      &ros_message->center, cdr);
  }

  // Field name: x_min
  {
    cdr << ros_message->x_min;
  }

  // Field name: y_min
  {
    cdr << ros_message->y_min;
  }

  // Field name: x_max
  {
    cdr << ros_message->x_max;
  }

  // Field name: y_max
  {
    cdr << ros_message->y_max;
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_save_pointcloud
size_t get_serialized_size_key_save_pointcloud__msg__BoundingBoxCenter(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _BoundingBoxCenter__ros_msg_type * ros_message = static_cast<const _BoundingBoxCenter__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;

  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: center
  current_alignment += get_serialized_size_key_geometry_msgs__msg__Point(
    &(ros_message->center), current_alignment);

  // Field name: x_min
  {
    size_t item_size = sizeof(ros_message->x_min);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: y_min
  {
    size_t item_size = sizeof(ros_message->y_min);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: x_max
  {
    size_t item_size = sizeof(ros_message->x_max);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: y_max
  {
    size_t item_size = sizeof(ros_message->y_max);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_save_pointcloud
size_t max_serialized_size_key_save_pointcloud__msg__BoundingBoxCenter(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;
  // Field name: center
  {
    size_t array_size = 1;
    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_key_geometry_msgs__msg__Point(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  // Field name: x_min
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: y_min
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: x_max
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: y_max
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = save_pointcloud__msg__BoundingBoxCenter;
    is_plain =
      (
      offsetof(DataType, y_max) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}


static bool _BoundingBoxCenter__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const save_pointcloud__msg__BoundingBoxCenter * ros_message = static_cast<const save_pointcloud__msg__BoundingBoxCenter *>(untyped_ros_message);
  (void)ros_message;
  return cdr_serialize_save_pointcloud__msg__BoundingBoxCenter(ros_message, cdr);
}

static bool _BoundingBoxCenter__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  save_pointcloud__msg__BoundingBoxCenter * ros_message = static_cast<save_pointcloud__msg__BoundingBoxCenter *>(untyped_ros_message);
  (void)ros_message;
  return cdr_deserialize_save_pointcloud__msg__BoundingBoxCenter(cdr, ros_message);
}

static uint32_t _BoundingBoxCenter__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_save_pointcloud__msg__BoundingBoxCenter(
      untyped_ros_message, 0));
}

static size_t _BoundingBoxCenter__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_save_pointcloud__msg__BoundingBoxCenter(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_BoundingBoxCenter = {
  "save_pointcloud::msg",
  "BoundingBoxCenter",
  _BoundingBoxCenter__cdr_serialize,
  _BoundingBoxCenter__cdr_deserialize,
  _BoundingBoxCenter__get_serialized_size,
  _BoundingBoxCenter__max_serialized_size,
  nullptr
};

static rosidl_message_type_support_t _BoundingBoxCenter__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_BoundingBoxCenter,
  get_message_typesupport_handle_function,
  &save_pointcloud__msg__BoundingBoxCenter__get_type_hash,
  &save_pointcloud__msg__BoundingBoxCenter__get_type_description,
  &save_pointcloud__msg__BoundingBoxCenter__get_type_description_sources,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, save_pointcloud, msg, BoundingBoxCenter)() {
  return &_BoundingBoxCenter__type_support;
}

#if defined(__cplusplus)
}
#endif
