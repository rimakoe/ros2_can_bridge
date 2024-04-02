#ifndef _ENDEC_HPP_
#define _ENDEC_HPP_

#include "can_lib/can1_main_ft24.h"
#include <functional>

namespace canlib{
    namespace frame {
        namespace decoded {
            namespace can1 {
                struct jetson_commands_t {
                    double jetson_brake_ratio;
                    double jetson_speed_target_left;
                    double jetson_speed_target_right;
                    double jetson_steering_angle_left;
                    double jetson_steering_angle_right;
                    jetson_commands_t(){
                        this->jetson_brake_ratio = 0.0;
                        this->jetson_speed_target_left = 0.0;
                        this->jetson_speed_target_right = 0.0;
                        this->jetson_steering_angle_left = 0.0;
                        this->jetson_steering_angle_right = 0.0;  
                    }
                    jetson_commands_t(  double jetson_brake_ratio, 
                                        double jetson_speed_target_left,
                                        double jetson_speed_target_right,
                                        double jetson_steering_angle_left,
                                        double jetson_steering_angle_right
                                        ){
                        this->jetson_brake_ratio = jetson_brake_ratio;
                        this->jetson_speed_target_left = jetson_speed_target_left;
                        this->jetson_speed_target_right = jetson_speed_target_right;
                        this->jetson_steering_angle_left = jetson_steering_angle_left;
                        this->jetson_steering_angle_right = jetson_steering_angle_right;      
                    }
                };
            }
        }   
    }
    namespace encode{
        namespace can1{
            can1_main_ft24_jetson_commands_t jetson_commands(const frame::decoded::can1::jetson_commands_t frame_decoded){
                can1_main_ft24_jetson_commands_t frame_encoded;
                can1_main_ft24_jetson_commands_init(&frame_encoded);
                frame_encoded.jetson_brake_ratio = can1_main_ft24_jetson_commands_jetson_brake_ratio_encode(frame_decoded.jetson_brake_ratio);
                frame_encoded.jetson_speed_target_left = can1_main_ft24_jetson_commands_jetson_speed_target_left_encode(frame_decoded.jetson_speed_target_left);
                frame_encoded.jetson_speed_target_right = can1_main_ft24_jetson_commands_jetson_speed_target_right_encode(frame_decoded.jetson_speed_target_right);
                frame_encoded.jetson_steering_angle_left = can1_main_ft24_jetson_commands_jetson_steering_angle_left_encode(frame_decoded.jetson_steering_angle_left);
                frame_encoded.jetson_steering_angle_right = can1_main_ft24_jetson_commands_jetson_steering_angle_right_encode(frame_decoded.jetson_steering_angle_right);
                return frame_encoded;
            }
        }
    }
    namespace decode {
        namespace can1{
            frame::decoded::can1::jetson_commands_t jetson_commands(const can1_main_ft24_jetson_commands_t frame_encoded){
                frame::decoded::can1::jetson_commands_t frame_decoded;
                frame_decoded.jetson_brake_ratio = can1_main_ft24_jetson_commands_jetson_brake_ratio_decode(frame_encoded.jetson_brake_ratio);
                frame_decoded.jetson_speed_target_left = can1_main_ft24_jetson_commands_jetson_speed_target_left_decode(frame_encoded.jetson_speed_target_left);
                frame_decoded.jetson_speed_target_right = can1_main_ft24_jetson_commands_jetson_speed_target_right_decode(frame_encoded.jetson_speed_target_right);
                frame_decoded.jetson_steering_angle_left = can1_main_ft24_jetson_commands_jetson_steering_angle_left_decode(frame_encoded.jetson_steering_angle_left);
                frame_decoded.jetson_steering_angle_right = can1_main_ft24_jetson_commands_jetson_steering_angle_right_decode(frame_encoded.jetson_steering_angle_right);
                return frame_decoded;
            }
        }
    }
    // data structure
    struct data_t{
        struct can1_t
        {
            frame::decoded::can1::jetson_commands_t jetson_commands;
        } can1;
    } data;
    // callback structure
    namespace callback {
        namespace rcv{
            namespace can1
            {
                std::function<void(can1_main_ft24_jetson_commands_t)> jetson_commands = NULL;
            }
        }
    }
}


#endif // _ENDEC_HPP_