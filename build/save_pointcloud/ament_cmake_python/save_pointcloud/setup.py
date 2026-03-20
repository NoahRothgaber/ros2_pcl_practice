from setuptools import find_packages
from setuptools import setup

setup(
    name='save_pointcloud',
    version='0.0.0',
    packages=find_packages(
        include=('save_pointcloud', 'save_pointcloud.*')),
)
