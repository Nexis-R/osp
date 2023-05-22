cmake_minimum_required(VERSION 3.5)
project(osp_teleop)

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME})

install(DIRECTORY
  config
  DESTINATION share/${PROJECT_NAME})

  install(DIRECTORY
  urdf
  DESTINATION share/${PROJECT_NAME})

install(DIRECTORY
  meshes
  DESTINATION share/${PROJECT_NAME})


find_package(ament_cmake REQUIRED)

ament_package()
