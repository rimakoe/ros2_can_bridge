#include "test_node/test_node.h"

using namespace std::chrono_literals;

TestNode::TestNode(){
    timer_ = this->create_wall_timer(
      500ms, [this]() -> void {
        transmit(ros2can::frame::decoded::can1::jetson_commands_t(
          0.1, 
          0.2, 
          0.3, 
          0.4, 
          0.5
        ));
    });
}

TestNode::~TestNode(){

}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TestNode>());
  rclcpp::shutdown();
  return 0;
}