// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from save_pointcloud:msg/BoundingBoxCenter.idl
// generated code does not contain a copyright notice
#include "save_pointcloud/msg/detail/bounding_box_center__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `center`
#include "geometry_msgs/msg/detail/point__functions.h"

bool
save_pointcloud__msg__BoundingBoxCenter__init(save_pointcloud__msg__BoundingBoxCenter * msg)
{
  if (!msg) {
    return false;
  }
  // center
  if (!geometry_msgs__msg__Point__init(&msg->center)) {
    save_pointcloud__msg__BoundingBoxCenter__fini(msg);
    return false;
  }
  // x_min
  // y_min
  // x_max
  // y_max
  return true;
}

void
save_pointcloud__msg__BoundingBoxCenter__fini(save_pointcloud__msg__BoundingBoxCenter * msg)
{
  if (!msg) {
    return;
  }
  // center
  geometry_msgs__msg__Point__fini(&msg->center);
  // x_min
  // y_min
  // x_max
  // y_max
}

bool
save_pointcloud__msg__BoundingBoxCenter__are_equal(const save_pointcloud__msg__BoundingBoxCenter * lhs, const save_pointcloud__msg__BoundingBoxCenter * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // center
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->center), &(rhs->center)))
  {
    return false;
  }
  // x_min
  if (lhs->x_min != rhs->x_min) {
    return false;
  }
  // y_min
  if (lhs->y_min != rhs->y_min) {
    return false;
  }
  // x_max
  if (lhs->x_max != rhs->x_max) {
    return false;
  }
  // y_max
  if (lhs->y_max != rhs->y_max) {
    return false;
  }
  return true;
}

bool
save_pointcloud__msg__BoundingBoxCenter__copy(
  const save_pointcloud__msg__BoundingBoxCenter * input,
  save_pointcloud__msg__BoundingBoxCenter * output)
{
  if (!input || !output) {
    return false;
  }
  // center
  if (!geometry_msgs__msg__Point__copy(
      &(input->center), &(output->center)))
  {
    return false;
  }
  // x_min
  output->x_min = input->x_min;
  // y_min
  output->y_min = input->y_min;
  // x_max
  output->x_max = input->x_max;
  // y_max
  output->y_max = input->y_max;
  return true;
}

save_pointcloud__msg__BoundingBoxCenter *
save_pointcloud__msg__BoundingBoxCenter__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  save_pointcloud__msg__BoundingBoxCenter * msg = (save_pointcloud__msg__BoundingBoxCenter *)allocator.allocate(sizeof(save_pointcloud__msg__BoundingBoxCenter), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(save_pointcloud__msg__BoundingBoxCenter));
  bool success = save_pointcloud__msg__BoundingBoxCenter__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
save_pointcloud__msg__BoundingBoxCenter__destroy(save_pointcloud__msg__BoundingBoxCenter * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    save_pointcloud__msg__BoundingBoxCenter__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
save_pointcloud__msg__BoundingBoxCenter__Sequence__init(save_pointcloud__msg__BoundingBoxCenter__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  save_pointcloud__msg__BoundingBoxCenter * data = NULL;

  if (size) {
    data = (save_pointcloud__msg__BoundingBoxCenter *)allocator.zero_allocate(size, sizeof(save_pointcloud__msg__BoundingBoxCenter), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = save_pointcloud__msg__BoundingBoxCenter__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        save_pointcloud__msg__BoundingBoxCenter__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
save_pointcloud__msg__BoundingBoxCenter__Sequence__fini(save_pointcloud__msg__BoundingBoxCenter__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      save_pointcloud__msg__BoundingBoxCenter__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

save_pointcloud__msg__BoundingBoxCenter__Sequence *
save_pointcloud__msg__BoundingBoxCenter__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  save_pointcloud__msg__BoundingBoxCenter__Sequence * array = (save_pointcloud__msg__BoundingBoxCenter__Sequence *)allocator.allocate(sizeof(save_pointcloud__msg__BoundingBoxCenter__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = save_pointcloud__msg__BoundingBoxCenter__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
save_pointcloud__msg__BoundingBoxCenter__Sequence__destroy(save_pointcloud__msg__BoundingBoxCenter__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    save_pointcloud__msg__BoundingBoxCenter__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
save_pointcloud__msg__BoundingBoxCenter__Sequence__are_equal(const save_pointcloud__msg__BoundingBoxCenter__Sequence * lhs, const save_pointcloud__msg__BoundingBoxCenter__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!save_pointcloud__msg__BoundingBoxCenter__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
save_pointcloud__msg__BoundingBoxCenter__Sequence__copy(
  const save_pointcloud__msg__BoundingBoxCenter__Sequence * input,
  save_pointcloud__msg__BoundingBoxCenter__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(save_pointcloud__msg__BoundingBoxCenter);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    save_pointcloud__msg__BoundingBoxCenter * data =
      (save_pointcloud__msg__BoundingBoxCenter *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!save_pointcloud__msg__BoundingBoxCenter__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          save_pointcloud__msg__BoundingBoxCenter__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!save_pointcloud__msg__BoundingBoxCenter__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
