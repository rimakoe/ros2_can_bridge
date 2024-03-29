#include "can_transciever/transciever.h"
#include "transciever.h"

using namespace rclcpp_lifecycle;
using namespace rclcpp_lifecycle::node_interfaces;

Transciever::Transciever() : rclcpp_lifecycle::LifecycleNode("can_transciever")
{
    RCLCPP_INFO(this->get_logger(), "Node init finished");
}

Transciever::~Transciever(){
}

CR Transciever::on_create(const State &previous_state)
{
    return CR();
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Transciever>());
    rclcpp::shutdown();
    return 0;
}
