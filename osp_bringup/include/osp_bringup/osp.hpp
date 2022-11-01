#pragma once

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include "std_msgs/msg/float32.hpp"

namespace osp {

class Osp : public rclcpp::Node {
 public:
  Osp();

 private:
  void handle_joy(const sensor_msgs::msg::Joy::SharedPtr joy);

  rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr joy_sub;

  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr crawler_left_pub;
  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr crawler_right_pub;

  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr flipper_left_front_pub;
  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr flipper_right_front_pub;
  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr flipper_left_back_pub;
  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr flipper_right_back_pub;
};

}  // namespace osp
