cmake_minimum_required(VERSION 3.5)
project(osp_rviz)

if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

install(DIRECTORY
  include
  DESTINATION share/${PROJECT_NAME})

find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)

install(DIRECTORY
  urdf
  DESTINATION share/${PROJECT_NAME})

install(DIRECTORY
  meshes
  DESTINATION share/${PROJECT_NAME})

install(DIRECTORY
  config
  DESTINATION share/${PROJECT_NAME})

ament_auto_add_library(osplib SHARED
  include/osp_rviz/osp_rviz.hpp
  src/osp_rviz.cpp
  src/osp_rviz_node.cpp)

ament_auto_add_executable(osp_rviz
  src/osp_rviz_node.cpp)

ament_auto_package()
