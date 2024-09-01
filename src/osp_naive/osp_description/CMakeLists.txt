cmake_minimum_required(VERSION 3.5)
project(osp_description)

install(DIRECTORY
  launch
  meshes
  urdf
  rviz
  DESTINATION share/${PROJECT_NAME})

find_package(ament_cmake REQUIRED)

ament_package()
