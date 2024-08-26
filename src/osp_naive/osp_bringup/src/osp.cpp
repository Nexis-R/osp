#include "osp_bringup/osp.hpp"

using namespace osp;

using std::placeholders::_1;

Osp::Osp() : Node("osp") {
  joy_sub = this->create_subscription<sensor_msgs::msg::Joy>(
      "/joy", 1, std::bind(&Osp::handle_joy, this, _1));

  crawler_left_pub =
      this->create_publisher<std_msgs::msg::Float32>("command_crawler_left", 1);
  crawler_right_pub =
      this->create_publisher<std_msgs::msg::Float32>("command_crawler_right", 1);

  flipper_left_front_pub =
      this->create_publisher<std_msgs::msg::Float32>("command_flipper_left_front", 1);
  flipper_right_front_pub =
      this->create_publisher<std_msgs::msg::Float32>("command_flipper_right_front", 1);
  flipper_left_back_pub =
      this->create_publisher<std_msgs::msg::Float32>("command_flipper_left_back", 1);
  flipper_right_back_pub =
      this->create_publisher<std_msgs::msg::Float32>("command_flipper_right_back", 1);
}

void Osp::handle_joy(const sensor_msgs::msg::Joy::SharedPtr joy) {
  const float vx = joy->axes.at(1);
  const float va = joy->axes.at(3);

  std_msgs::msg::Float32 left_speed;
  std_msgs::msg::Float32 right_speed;
  left_speed.set__data(vx * 2000.0 - va * 1000.0);
  right_speed.set__data(vx * 2000.0 + va * 1000.0);

  crawler_left_pub->publish(left_speed);
  crawler_right_pub->publish(right_speed);

  // L1
  std_msgs::msg::Float32 flipper_speed;
  std_msgs::msg::Float32 speed_zero;
  speed_zero.set__data(0.0);
  flipper_speed.set__data(joy->axes.at(4) * 1.0);
  if (joy->buttons.at(4)) {
    flipper_left_front_pub->publish(flipper_speed);
  } else {
    flipper_left_front_pub->publish(speed_zero);
  }
  // R1
  if (joy->buttons.at(5)) {
    flipper_right_front_pub->publish(flipper_speed);
  } else {
    flipper_right_front_pub->publish(speed_zero);
  }
  // L2
  if (joy->buttons.at(6)) {
    flipper_left_back_pub->publish(flipper_speed);
  } else {
    flipper_left_back_pub->publish(speed_zero);
  }
  // R2
  if (joy->buttons.at(7)) {
    flipper_right_back_pub->publish(flipper_speed);
  } else {
    flipper_right_back_pub->publish(speed_zero);
  }
}