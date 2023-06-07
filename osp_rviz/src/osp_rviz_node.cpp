#include "osp_rviz/osp_rviz.hpp"

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<flipper_visualize::Flipper_visualize>());
  rclcpp::shutdown();
}