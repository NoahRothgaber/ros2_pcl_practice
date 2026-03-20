// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from save_pointcloud:msg/BoundingBoxCenter.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "save_pointcloud/msg/bounding_box_center.h"


#ifndef SAVE_POINTCLOUD__MSG__DETAIL__BOUNDING_BOX_CENTER__FUNCTIONS_H_
#define SAVE_POINTCLOUD__MSG__DETAIL__BOUNDING_BOX_CENTER__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/action_type_support_struct.h"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_runtime_c/type_description/type_description__struct.h"
#include "rosidl_runtime_c/type_description/type_source__struct.h"
#include "rosidl_runtime_c/type_hash.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "save_pointcloud/msg/rosidl_generator_c__visibility_control.h"

#include "save_pointcloud/msg/detail/bounding_box_center__struct.h"

/// Initialize msg/BoundingBoxCenter message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * save_pointcloud__msg__BoundingBoxCenter
 * )) before or use
 * save_pointcloud__msg__BoundingBoxCenter__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_save_pointcloud
bool
save_pointcloud__msg__BoundingBoxCenter__init(save_pointcloud__msg__BoundingBoxCenter * msg);

/// Finalize msg/BoundingBoxCenter message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_save_pointcloud
void
save_pointcloud__msg__BoundingBoxCenter__fini(save_pointcloud__msg__BoundingBoxCenter * msg);

/// Create msg/BoundingBoxCenter message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * save_pointcloud__msg__BoundingBoxCenter__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_save_pointcloud
save_pointcloud__msg__BoundingBoxCenter *
save_pointcloud__msg__BoundingBoxCenter__create(void);

/// Destroy msg/BoundingBoxCenter message.
/**
 * It calls
 * save_pointcloud__msg__BoundingBoxCenter__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_save_pointcloud
void
save_pointcloud__msg__BoundingBoxCenter__destroy(save_pointcloud__msg__BoundingBoxCenter * msg);

/// Check for msg/BoundingBoxCenter message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_save_pointcloud
bool
save_pointcloud__msg__BoundingBoxCenter__are_equal(const save_pointcloud__msg__BoundingBoxCenter * lhs, const save_pointcloud__msg__BoundingBoxCenter * rhs);

/// Copy a msg/BoundingBoxCenter message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_save_pointcloud
bool
save_pointcloud__msg__BoundingBoxCenter__copy(
  const save_pointcloud__msg__BoundingBoxCenter * input,
  save_pointcloud__msg__BoundingBoxCenter * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_save_pointcloud
const rosidl_type_hash_t *
save_pointcloud__msg__BoundingBoxCenter__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_save_pointcloud
const rosidl_runtime_c__type_description__TypeDescription *
save_pointcloud__msg__BoundingBoxCenter__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_save_pointcloud
const rosidl_runtime_c__type_description__TypeSource *
save_pointcloud__msg__BoundingBoxCenter__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_save_pointcloud
const rosidl_runtime_c__type_description__TypeSource__Sequence *
save_pointcloud__msg__BoundingBoxCenter__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of msg/BoundingBoxCenter messages.
/**
 * It allocates the memory for the number of elements and calls
 * save_pointcloud__msg__BoundingBoxCenter__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_save_pointcloud
bool
save_pointcloud__msg__BoundingBoxCenter__Sequence__init(save_pointcloud__msg__BoundingBoxCenter__Sequence * array, size_t size);

/// Finalize array of msg/BoundingBoxCenter messages.
/**
 * It calls
 * save_pointcloud__msg__BoundingBoxCenter__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_save_pointcloud
void
save_pointcloud__msg__BoundingBoxCenter__Sequence__fini(save_pointcloud__msg__BoundingBoxCenter__Sequence * array);

/// Create array of msg/BoundingBoxCenter messages.
/**
 * It allocates the memory for the array and calls
 * save_pointcloud__msg__BoundingBoxCenter__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_save_pointcloud
save_pointcloud__msg__BoundingBoxCenter__Sequence *
save_pointcloud__msg__BoundingBoxCenter__Sequence__create(size_t size);

/// Destroy array of msg/BoundingBoxCenter messages.
/**
 * It calls
 * save_pointcloud__msg__BoundingBoxCenter__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_save_pointcloud
void
save_pointcloud__msg__BoundingBoxCenter__Sequence__destroy(save_pointcloud__msg__BoundingBoxCenter__Sequence * array);

/// Check for msg/BoundingBoxCenter message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_save_pointcloud
bool
save_pointcloud__msg__BoundingBoxCenter__Sequence__are_equal(const save_pointcloud__msg__BoundingBoxCenter__Sequence * lhs, const save_pointcloud__msg__BoundingBoxCenter__Sequence * rhs);

/// Copy an array of msg/BoundingBoxCenter messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_save_pointcloud
bool
save_pointcloud__msg__BoundingBoxCenter__Sequence__copy(
  const save_pointcloud__msg__BoundingBoxCenter__Sequence * input,
  save_pointcloud__msg__BoundingBoxCenter__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // SAVE_POINTCLOUD__MSG__DETAIL__BOUNDING_BOX_CENTER__FUNCTIONS_H_
