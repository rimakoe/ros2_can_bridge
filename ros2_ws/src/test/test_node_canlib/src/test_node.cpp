#include "test_node_canlib/test_node.h"

using namespace std::chrono_literals;

TestNode::TestNode(): rclcpp::Node("test_node_canlib"), canlib::Transciever() {
    // Use callbacks to customize the decoding of the incoming data
    canlib::callback::rcv::can1::jetson_commands = [&](can1_main_ft24_jetson_commands_t frame_encoded){
      RCLCPP_INFO(this->get_logger(), "Hello from callback %lf\n", canlib::data.can1.jetson_commands.jetson_speed_target_left);
    };

    // Use a thread to continuously update the can messages
    std::thread receiver([this](){
      while(rclcpp::ok()){
        if(receive()){
          RCLCPP_INFO(this->get_logger(), "Received data");
        }
      }
      RCLCPP_INFO(this->get_logger(), "Receiver is shutting down");
    });

    // Just for an example send contnuosly data
    std::thread transmitter([this](){
      while(rclcpp::ok()){
        transmit(canlib::frame::decoded::can1::jetson_commands_t(
          0.1, 
          0.2, 
          0.3, 
          0.4, 
          0.5
        ));
        sleep(1);   
        }
      RCLCPP_INFO(this->get_logger(), "Transmitter is shutting down");
    });

    receiver.join();
    transmitter.join();
}

TestNode::~TestNode(){
  RCLCPP_INFO(this->get_logger(), "TestNode destructor called");
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TestNode>());
  rclcpp::shutdown();
  return 0;
}