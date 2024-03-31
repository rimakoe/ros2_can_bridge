#include "can_bridge/bridge.h"

using namespace std::chrono_literals;

ros2can::Bridge::Bridge() : rclcpp::Node("can_bridge")
{
    // Instatiate Subcscribers
    subscription_jetson_commands_stamped = this->create_subscription<can_msgs::msg::JetsonCommandsStamped>(
        "/can1/JetsonCommandsStamped",
        10,
        std::bind(&ros2can::Bridge::callback_jetson_commands_stamped, this, std::placeholders::_1));

    // Initialize can frames
    can1_main_ft24_jetson_commands_init(&can1_main_ft24_jetson_commands_frame);

    // Setup CAN Bus
    if ((socket_instance = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
        RCLCPP_ERROR(this->get_logger(), "Cant Init CAN Socket");
        return;
    }

    struct ifreq ifr;
    strcpy(ifr.ifr_name, "vcan0" );
    ioctl(socket_instance, SIOCGIFINDEX, &ifr);

    struct sockaddr_can addr;
    memset(&addr, 0, sizeof(addr));
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    if (bind(socket_instance, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Bind");
        RCLCPP_ERROR(this->get_logger(), "Cant Bind CAN Bus Socket");
        return;
    }

    RCLCPP_INFO(this->get_logger(), "Node init finished");
}

ros2can::Bridge::~Bridge(){
}

void ros2can::Bridge::callback_jetson_commands_stamped(const can_msgs::msg::JetsonCommandsStamped::SharedPtr pMsg)
{ 
    frame = can_frame();
    can1_main_ft24_jetson_commands_frame.jetson_speed_target_left = pMsg->data.jetson_speed_target_left;                                                                                                                                                    
    can1_main_ft24_jetson_commands_frame.jetson_speed_target_right = pMsg->data.jetson_speed_target_right;
    can1_main_ft24_jetson_commands_frame.jetson_steering_angle_left = pMsg->data.jetson_steering_angle_left;
    can1_main_ft24_jetson_commands_frame.jetson_steering_angle_right = pMsg->data.jetson_steering_angle_right;
    

    int command_can_frame_size = can1_main_ft24_jetson_commands_pack(reinterpret_cast<uint8_t*>(&frame.data), &can1_main_ft24_jetson_commands_frame, sizeof(frame.data));

    if (command_can_frame_size < 0) {
        perror("Pack");
        RCLCPP_ERROR(this->get_logger(), "CAN Frame size unacceptable");
        return;
    }

    frame.can_id = pMsg->id;
    frame.can_dlc = pMsg->dlc;
    
    if (::write(socket_instance, &frame, sizeof(struct can_frame)) < 0) {
        perror("Write to device: ");
        RCLCPP_ERROR(this->get_logger(), "Not able to write to socket can");
        return;
    }
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    std::shared_ptr<ros2can::Bridge> bridge = std::make_shared<ros2can::Bridge>();
    rclcpp::spin(bridge);
    rclcpp::shutdown();
    return 0;
}
