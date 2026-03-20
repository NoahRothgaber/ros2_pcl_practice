// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from save_pointcloud:msg/BoundingBoxCenter.idl
// generated code does not contain a copyright notice

#include "save_pointcloud/msg/detail/bounding_box_center__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_save_pointcloud
const rosidl_type_hash_t *
save_pointcloud__msg__BoundingBoxCenter__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x13, 0x06, 0x4f, 0x35, 0x0b, 0x31, 0xc6, 0xfe,
      0x4f, 0x1f, 0xe1, 0x25, 0xf5, 0xd5, 0xf4, 0xd5,
      0x9e, 0x7d, 0xf8, 0xf6, 0x8d, 0x9b, 0x70, 0x14,
      0x4f, 0xb4, 0x43, 0x67, 0x19, 0x1b, 0x89, 0xad,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "geometry_msgs/msg/detail/point__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t geometry_msgs__msg__Point__EXPECTED_HASH = {1, {
    0x69, 0x63, 0x08, 0x48, 0x42, 0xa9, 0xb0, 0x44,
    0x94, 0xd6, 0xb2, 0x94, 0x1d, 0x11, 0x44, 0x47,
    0x08, 0xd8, 0x92, 0xda, 0x2f, 0x4b, 0x09, 0x84,
    0x3b, 0x9c, 0x43, 0xf4, 0x2a, 0x7f, 0x68, 0x81,
  }};
#endif

static char save_pointcloud__msg__BoundingBoxCenter__TYPE_NAME[] = "save_pointcloud/msg/BoundingBoxCenter";
static char geometry_msgs__msg__Point__TYPE_NAME[] = "geometry_msgs/msg/Point";

// Define type names, field names, and default values
static char save_pointcloud__msg__BoundingBoxCenter__FIELD_NAME__center[] = "center";
static char save_pointcloud__msg__BoundingBoxCenter__FIELD_NAME__x_min[] = "x_min";
static char save_pointcloud__msg__BoundingBoxCenter__FIELD_NAME__y_min[] = "y_min";
static char save_pointcloud__msg__BoundingBoxCenter__FIELD_NAME__x_max[] = "x_max";
static char save_pointcloud__msg__BoundingBoxCenter__FIELD_NAME__y_max[] = "y_max";

static rosidl_runtime_c__type_description__Field save_pointcloud__msg__BoundingBoxCenter__FIELDS[] = {
  {
    {save_pointcloud__msg__BoundingBoxCenter__FIELD_NAME__center, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {geometry_msgs__msg__Point__TYPE_NAME, 23, 23},
    },
    {NULL, 0, 0},
  },
  {
    {save_pointcloud__msg__BoundingBoxCenter__FIELD_NAME__x_min, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {save_pointcloud__msg__BoundingBoxCenter__FIELD_NAME__y_min, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {save_pointcloud__msg__BoundingBoxCenter__FIELD_NAME__x_max, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {save_pointcloud__msg__BoundingBoxCenter__FIELD_NAME__y_max, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription save_pointcloud__msg__BoundingBoxCenter__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {geometry_msgs__msg__Point__TYPE_NAME, 23, 23},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
save_pointcloud__msg__BoundingBoxCenter__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {save_pointcloud__msg__BoundingBoxCenter__TYPE_NAME, 37, 37},
      {save_pointcloud__msg__BoundingBoxCenter__FIELDS, 5, 5},
    },
    {save_pointcloud__msg__BoundingBoxCenter__REFERENCED_TYPE_DESCRIPTIONS, 1, 1},
  };
  if (!constructed) {
    assert(0 == memcmp(&geometry_msgs__msg__Point__EXPECTED_HASH, geometry_msgs__msg__Point__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = geometry_msgs__msg__Point__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "geometry_msgs/Point center\n"
  "int32 x_min\n"
  "int32 y_min\n"
  "int32 x_max\n"
  "int32 y_max";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
save_pointcloud__msg__BoundingBoxCenter__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {save_pointcloud__msg__BoundingBoxCenter__TYPE_NAME, 37, 37},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 74, 74},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
save_pointcloud__msg__BoundingBoxCenter__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[2];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 2, 2};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *save_pointcloud__msg__BoundingBoxCenter__get_individual_type_description_source(NULL),
    sources[1] = *geometry_msgs__msg__Point__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
