# generated from rosidl_generator_py/resource/_idl.py.em
# with input from save_pointcloud:msg/BoundingBoxCenter.idl
# generated code does not contain a copyright notice

# This is being done at the module level and not on the instance level to avoid looking
# for the same variable multiple times on each instance. This variable is not supposed to
# change during runtime so it makes sense to only look for it once.
from os import getenv

ros_python_check_fields = getenv('ROS_PYTHON_CHECK_FIELDS', default='')


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_BoundingBoxCenter(type):
    """Metaclass of message 'BoundingBoxCenter'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('save_pointcloud')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'save_pointcloud.msg.BoundingBoxCenter')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__bounding_box_center
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__bounding_box_center
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__bounding_box_center
            cls._TYPE_SUPPORT = module.type_support_msg__msg__bounding_box_center
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__bounding_box_center

            from geometry_msgs.msg import Point
            if Point.__class__._TYPE_SUPPORT is None:
                Point.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class BoundingBoxCenter(metaclass=Metaclass_BoundingBoxCenter):
    """Message class 'BoundingBoxCenter'."""

    __slots__ = [
        '_center',
        '_x_min',
        '_y_min',
        '_x_max',
        '_y_max',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'center': 'geometry_msgs/Point',
        'x_min': 'int32',
        'y_min': 'int32',
        'x_max': 'int32',
        'y_max': 'int32',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Point'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        if 'check_fields' in kwargs:
            self._check_fields = kwargs['check_fields']
        else:
            self._check_fields = ros_python_check_fields == '1'
        if self._check_fields:
            assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
                'Invalid arguments passed to constructor: %s' % \
                ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from geometry_msgs.msg import Point
        self.center = kwargs.get('center', Point())
        self.x_min = kwargs.get('x_min', int())
        self.y_min = kwargs.get('y_min', int())
        self.x_max = kwargs.get('x_max', int())
        self.y_max = kwargs.get('y_max', int())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.get_fields_and_field_types().keys(), self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    if self._check_fields:
                        assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.center != other.center:
            return False
        if self.x_min != other.x_min:
            return False
        if self.y_min != other.y_min:
            return False
        if self.x_max != other.x_max:
            return False
        if self.y_max != other.y_max:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def center(self):
        """Message field 'center'."""
        return self._center

    @center.setter
    def center(self, value):
        if self._check_fields:
            from geometry_msgs.msg import Point
            assert \
                isinstance(value, Point), \
                "The 'center' field must be a sub message of type 'Point'"
        self._center = value

    @builtins.property
    def x_min(self):
        """Message field 'x_min'."""
        return self._x_min

    @x_min.setter
    def x_min(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'x_min' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'x_min' field must be an integer in [-2147483648, 2147483647]"
        self._x_min = value

    @builtins.property
    def y_min(self):
        """Message field 'y_min'."""
        return self._y_min

    @y_min.setter
    def y_min(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'y_min' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'y_min' field must be an integer in [-2147483648, 2147483647]"
        self._y_min = value

    @builtins.property
    def x_max(self):
        """Message field 'x_max'."""
        return self._x_max

    @x_max.setter
    def x_max(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'x_max' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'x_max' field must be an integer in [-2147483648, 2147483647]"
        self._x_max = value

    @builtins.property
    def y_max(self):
        """Message field 'y_max'."""
        return self._y_max

    @y_max.setter
    def y_max(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'y_max' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'y_max' field must be an integer in [-2147483648, 2147483647]"
        self._y_max = value
