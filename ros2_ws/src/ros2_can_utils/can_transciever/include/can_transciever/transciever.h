#ifndef _CAN_TRANSCIEVER_H_
#define _CAN_TRANSCIEVER_H_

#include <rclcpp/rclcpp.hpp>
#include <can_msgs/messages.h>
#include "endec.hpp"

namespace ros2can{
    class Transciever : public rclcpp::Node
    {
    public:
        Transciever();
        ~Transciever();
    private:
        // functions
        void transmit(const frame::decoded::can1::jetson_commands_t frame_decoded);
        
        // publisher
        rclcpp::Publisher<can_msgs::msg::JetsonCommandsStamped>::SharedPtr publisher_can1_jetson_commands_stamped;
        
        // subscriber
        rclcpp::Subscription<can_msgs::msg::JetsonCommandsStamped>::SharedPtr subscription_can1_jetson_commands_stamped;
        
        // data structures
        struct received_data_t{
            struct can1_t
            {
                frame::decoded::can1::jetson_commands_t jetson_commands;
            } can1;
        } received_data;

        rclcpp::TimerBase::SharedPtr timer_;
    };
}

#endif // _CAN_TRANSCIEVER_H_
