#include "can_lib/transciever.h"
#include <thread>
using namespace std::chrono_literals;

extern "C" canlib::Transciever::Transciever(){
    // Initialize can frames
    can1_main_ft24_jetson_commands_init(&can1_main_ft24_jetson_commands_frame);

    // Setup CAN Bus
    if ((socket_instance = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
        printf("Cant Init CAN Socket");
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
        printf("Cant Bind CAN Bus Socket");
        return;
    }
}

extern "C" canlib::Transciever::~Transciever(){
}

bool canlib::Transciever::read(struct can_frame &frame, int timeout_usec){
    fd_set readSet;
    FD_ZERO(&readSet);
    FD_SET(socket_instance, &readSet);
    struct timeval timeout_tv;
    timeout_tv.tv_sec = 0;
    timeout_tv.tv_usec = timeout_usec;
    if (!select(socket_instance + 1, &readSet, NULL, NULL, &timeout_tv))
    {
        return false;
    }

    // read frame
    int nbytes = ::read(socket_instance, &frame, sizeof(struct can_frame));

    return nbytes == sizeof(struct can_frame);
}

extern "C" bool canlib::Transciever::receive(int timeout_us){
    can_frame can_frame_raw;
    if(read(can_frame_raw, timeout_us)){
        switch (can_frame_raw.can_id){
            case CAN1_MAIN_FT24_JETSON_COMMANDS_FRAME_ID:
            {
                can1_main_ft24_jetson_commands_t can1_main_ft24_jetson_commands;
                can1_main_ft24_jetson_commands_unpack(&can1_main_ft24_jetson_commands, can_frame_raw.data, can_frame_raw.can_dlc);
                canlib::data.can1.jetson_commands = canlib::decode::can1::jetson_commands(can1_main_ft24_jetson_commands);
                if(canlib::callback::rcv::can1::jetson_commands != NULL){
                    canlib::callback::rcv::can1::jetson_commands(can1_main_ft24_jetson_commands);
                }
                return true;
            }
            default:
                return false;
        }
    }
}


extern "C" void canlib::Transciever::transmit(canlib::frame::decoded::can1::jetson_commands_t jetson_commands){
    frame = can_frame();

    can1_main_ft24_jetson_commands_frame = canlib::encode::can1::jetson_commands(jetson_commands);
    int command_can_frame_size = can1_main_ft24_jetson_commands_pack(reinterpret_cast<uint8_t*>(&frame.data), &can1_main_ft24_jetson_commands_frame, sizeof(frame.data));

    if (command_can_frame_size < 0) {
        perror("Pack");
        printf("CAN Frame size unacceptable");
        return;
    }

    frame.can_id = CAN1_MAIN_FT24_JETSON_COMMANDS_FRAME_ID;
    frame.can_dlc = CAN1_MAIN_FT24_JETSON_COMMANDS_LENGTH;
    
    if (::write(socket_instance, &frame, sizeof(struct can_frame)) < 0) {
        perror("Write to device: ");
        printf("Not able to write to socket can");
        return;
    }
}

// For testing 
int main(int argc, char **argv)
{
    canlib::Transciever transciever;
    transciever = canlib::Transciever();
    auto now = std::chrono::steady_clock::now;
    auto work_duration = 10s;
    auto start = now();

    std::thread t1([&](void) -> void {
        printf("start thread\n");
        using namespace std::chrono;
        auto start = high_resolution_clock::now();
        auto prev = start;
        auto execution_time = 10s;
        auto before_action = start;
        auto after_action = start;
        auto desired_iteration_time = 10ms;
        auto waiting_time = 0ms;
        while (std::chrono::duration_cast<std::chrono::seconds>(high_resolution_clock::now() - start) < execution_time)
        {
            // printf("%d\n", std::chrono::duration_cast<std::chrono::milliseconds>(high_resolution_clock::now() - start).count());
            before_action = high_resolution_clock::now();
            transciever.transmit(canlib::frame::decoded::can1::jetson_commands_t(0.1, 0.2, 0.3, 0.4, 0.5));
            after_action = high_resolution_clock::now();

            // delay until time to iterate again
            waiting_time = desired_iteration_time - std::chrono::duration_cast<std::chrono::milliseconds>(after_action - before_action);
            std::this_thread::sleep_for(waiting_time);
        }
    });

    t1.join();
    return 0;
}
