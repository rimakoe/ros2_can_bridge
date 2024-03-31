
#ifndef ROS2_TO_CAN_CONVERTER_H
#define ROS2_TO_CAN_CONVERTER_H

#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <rclcpp/logger.hpp>
#include <rclcpp/node.hpp>
#include <rclcpp/rclcpp.hpp>
#include <can_msgs/messages.h>
#include <can_interface/can1_main_ft24.h>

namespace ros2can{
    class Bridge : public rclcpp::Node
    {
    public:
        Bridge();
        ~Bridge();
    private:
        void callback_jetson_commands_stamped(const can_msgs::msg::JetsonCommandsStamped::SharedPtr pMsg);
        rclcpp::Subscription<can_msgs::msg::JetsonCommandsStamped>::SharedPtr subscription_jetson_commands_stamped;
        can1_main_ft24_jetson_commands_t can1_main_ft24_jetson_commands_frame;
        struct can_frame frame;
        int socket_instance;
    };
}
#endif  // ROS2_TO_CAN_CONVERTER_H
