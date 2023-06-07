#include "osp_rviz/osp_rviz.hpp"

using namespace flipper_visualize;

using std::placeholders::_1;
using std::placeholders::_2;


Flipper_visualize::Flipper_visualize() : Node("Flipper_angle"){ //constructor
     auto logger = this->get_logger();

     this->declare_parameter("ids", std::vector<int64_t>{{1}});
     this->declare_parameter("dataout_freq", 10);
     this->declare_parameter("joint_name", std::vector<std::string>(4,""));
     this->declare_parameter("frame_id", "");
     this->declare_parameter("angle_coefficient", std::vector<std::double_t>{{1}});
     this->declare_parameter("angle_offset", std::vector<std::double_t>{{1}});

     const auto ids = this->get_parameter("ids").as_integer_array(); 
     const auto dataout_freq = this->get_parameter("dataout_freq").as_int();
     const auto joint_name = this->get_parameter("joint_name").as_string_array();
     const auto frame_id = this->get_parameter("frame_id").as_string();
     const auto angle_coefficient = this->get_parameter("angle_coefficient").as_double_array();
     const auto angle_offset = this->get_parameter("angle_offset").as_double_array();

     Flipper flipper;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//subscriber
     for (const auto& id : ids) {

       flipper.id = id;
       flippers[id] = flipper;
       coefficients.insert_or_assign(id,angle_coefficient.at(id - ids.front()));
       offsets.insert_or_assign(id,angle_offset.at(id - ids.front()));

      const std::string motor_namespace = "dynamixel/motor" + std::to_string(id); //generate string "dynamixel_h54/motorN" (N:2,3,4,5)

      flippers[id].angle_sub =
      this->create_subscription<std_msgs::msg::Float32>( //generate subscriber. name determinated in "dynamixel_h54" node
          motor_namespace + "/angle", 1,
          std::bind(&Flipper::handle_angle, &flippers[id], _1));
    }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//publisher
     joint_state_pub = this->create_publisher<sensor_msgs::msg::JointState>( //generate publisher
      "joint_states", 1);

     joint_state.header.stamp = this->now();
     for (size_t i = 0; i < joint_name.size(); ++i) { // set joint name
      joint_state.name.push_back(joint_name[i]);
    }
     joint_state.header.frame_id = frame_id;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//determinate frequency of publish
    timer =
      this->create_wall_timer(std::chrono::milliseconds(1000 / dataout_freq),
                                std::bind(&Flipper_visualize::handle_pub_data, this));
}

void Flipper_visualize::handle_pub_data() { //publisher
     for (auto&[id, flipper]: flippers) {
          joint_state.position.push_back(coefficients.at(id) *(flipper.angle + offsets.at(id)));
     }
         joint_state.header.stamp = this->now();
         joint_state_pub->publish(joint_state);
         joint_state.position.clear();
}

void Flipper::handle_angle( //subscriber
    const std_msgs::msg::Float32::SharedPtr angle){
    this->angle = angle->data;
}