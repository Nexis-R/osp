#include "osp_bringup/osp.hpp"

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<osp::Osp>());
  rclcpp::shutdown();
  return 0;
}