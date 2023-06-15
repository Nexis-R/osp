#pragma once

#include <rclcpp/rclcpp.hpp>
#include "std_msgs/msg/float32.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include <memory>
#include <vector>

namespace flipper_visualize{
  struct Flipper {

    uint16_t id;
    double angle;

    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr angle_sub; //recieved angle
    std::vector<std::double_t> coefficient;
    std::vector<std::double_t> offset;
  
    void handle_angle(const std_msgs::msg::Float32::SharedPtr angle);
  };

  class Flipper_visualize: public rclcpp::Node {
   public:
    Flipper_visualize();
  
   private:
 
    void handle_pub_data();
    rclcpp::TimerBase::SharedPtr timer;
    rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr joint_state_pub;   //angle will be sended to rviz

    sensor_msgs::msg::JointState joint_state;

    std::map<int64_t, Flipper> flippers;
    std::map<int16_t,double_t> coefficients;
    std::map<int16_t,double_t> offsets;
    
  };
} //namespace flipper_visualize