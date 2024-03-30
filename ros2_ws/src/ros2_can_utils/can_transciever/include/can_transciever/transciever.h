
#ifndef ROS2_TO_CAN_CONVERTER_H
#define ROS2_TO_CAN_CONVERTER_H

// #include <rclcpp_lifecycle/lifecycle_node.hpp>
#include <rclcpp/logger.hpp>
#include <rclcpp/node.hpp>
#include <rclcpp/rclcpp.hpp>
#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <can_msgs/messages.h>

// using CR = rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn;
// using State = rclcpp_lifecycle::State;

class Transciever : public rclcpp::Node
{
public:
    Transciever();
    ~Transciever();

private:
    void timer_callback();
    rclcpp::Publisher<can_msgs::msg::AbxBrakeTStamped>::SharedPtr publisher_abx_brake_t;
    rclcpp::TimerBase::SharedPtr timer_;
    // CR on_create(const State & previous_state);
    // CR on_configure(const State & previous_state);
    // CR on_cleanup(const State & previous_state);
    // CR on_activate(const State & previous_state);
    // CR on_deactivate(const State & previous_state);
    // CR on_on_error(const State & previous_state);
    // CR on_shutdown(const State & previous_state);

};

#endif  // ROS2_TO_CAN_CONVERTER_H
