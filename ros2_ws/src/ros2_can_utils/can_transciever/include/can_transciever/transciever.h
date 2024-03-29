
#ifndef ROS2_TO_CAN_CONVERTER_H
#define ROS2_TO_CAN_CONVERTER_H

#include <rclcpp/logger.hpp>
#include <rclcpp_lifecycle/lifecycle_node.hpp>
#include "messages.h"

using CR = rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn;
using State = rclcpp_lifecycle::State;

class Transciever : public rclcpp_lifecycle::LifecycleNode
{
public:
    Transciever();
    ~Transciever();

private:

    rclcpp::Publisher<can_msgs::msg::AbxBrakeT>::SharedPtr publisher_abx_brake_t;
    CR on_create(const State & previous_state);
    CR on_configure(const State & previous_state);
    CR on_cleanup(const State & previous_state);
    CR on_activate(const State & previous_state);
    CR on_deactivate(const State & previous_state);
    CR on_on_error(const State & previous_state);
    CR on_shutdown(const State & previous_state);

};

#endif  // ROS2_TO_CAN_CONVERTER_H
