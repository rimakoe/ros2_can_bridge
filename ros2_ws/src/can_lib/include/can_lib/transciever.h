#ifndef _TRANSCIEVER_H_
#define _TRANSCIEVER_H_

#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>


#include "can_lib/endec.hpp"

namespace canlib{
    bool quit_receiver = false;

    class Transciever{
    public:
        Transciever();
        ~Transciever();

        virtual void transmit(canlib::frame::decoded::can1::jetson_commands_t jetson_commands);
        virtual bool receive(int timeout_us = 10000); // Stores the received frames into a struct based on the dbc file

    private:
        virtual bool read(struct can_frame &frame, int timeout_usec);

        can1_main_ft24_jetson_commands_t can1_main_ft24_jetson_commands_frame;

        struct can_frame frame;
        int socket_instance;
    };

}

#endif // _TRANSCIEVER_H_