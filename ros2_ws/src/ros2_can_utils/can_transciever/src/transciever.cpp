#include "can_transciever/transciever.h"


#include <chrono>
#include <functional>
#include <memory>
#include <string>
using std::placeholders::_1;
using namespace std::chrono_literals;

ros2can::Transciever::Transciever(): rclcpp::Node("Transciever") 
{
    publisher_can1_jetson_commands_stamped = this->create_publisher<can_msgs::msg::JetsonCommandsStamped>("/can1/JetsonCommandsStamped", 10);
    this->create_subscription<can_msgs::msg::JetsonCommandsStamped>(
        "/can1/JetsonCommandsStamped", 
        10, 
        [this](const can_msgs::msg::JetsonCommandsStamped::SharedPtr pMessage){
            received_data.can1.jetson_commands = decode::can1::jetson_commands(pMessage->data);
        }
    );

    timer_ = this->create_wall_timer(
      500ms, [this]() -> void {
        transmit(frame::decoded::can1::jetson_commands_t(0.1, 0.2, 0.3, 0.4, 0.5));
    });
}

ros2can::Transciever::~Transciever() 
{
}

void ros2can::Transciever::transmit(const frame::decoded::can1::jetson_commands_t frame_decoded)
{
    can_msgs::msg::JetsonCommandsStamped message;

    std_msgs::msg::Header header;
    header.stamp = this->get_clock()->now();
    header.frame_id = "can1";
    message.header = header;
    
    auto frame_encoded = encode::can1::jetson_commands(frame_decoded);
    message.data.jetson_brake_ratio = frame_encoded.jetson_brake_ratio;
    message.data.jetson_speed_target_left = frame_encoded.jetson_speed_target_left;
    message.data.jetson_speed_target_right = frame_encoded.jetson_speed_target_right;
    message.data.jetson_steering_angle_left = frame_encoded.jetson_steering_angle_left;
    message.data.jetson_steering_angle_right = frame_encoded.jetson_steering_angle_right;
    publisher_can1_jetson_commands_stamped->publish(message);
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    std::shared_ptr<ros2can::Transciever> transciever = std::make_shared<ros2can::Transciever>();
    rclcpp::spin(transciever);
    rclcpp::shutdown();
    return 0;
}

