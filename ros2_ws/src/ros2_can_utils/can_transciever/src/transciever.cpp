#include "can_transciever/transciever.h"

using namespace std::chrono_literals;

Transciever::Transciever() : rclcpp::Node("can_transciever")
{
    publisher_abx_brake_t = this->create_publisher<can_msgs::msg::AbxBrakeTStamped>("/can1/abx/brake", 10);
    timer_ = this->create_wall_timer(500ms, std::bind(&Transciever::timer_callback, this));
    RCLCPP_INFO(this->get_logger(), "Node init finished");
}

Transciever::~Transciever(){
}

void Transciever::timer_callback()
{
    auto message = can_msgs::msg::AbxBrakeTStamped();
    uint16_t fl = 187;
    message.data.abx_brake_t_fl = fl; 
    RCLCPP_INFO(this->get_logger(), "Publishing data");
    publisher_abx_brake_t->publish(message);
} 

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    std::shared_ptr<Transciever> transciever = std::make_shared<Transciever>();
    rclcpp::spin(transciever);
    rclcpp::shutdown();
    return 0;
}
