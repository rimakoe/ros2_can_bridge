#ifndef _TEST_NODE_H_
#define _TEST_NODE_H_

#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <rclcpp/rclcpp.hpp>

#include <can_lib/transciever.h>

class TestNode : public rclcpp::Node, canlib::Transciever
{
  public:
    TestNode();
    ~TestNode();
  
  private:
    bool quit = false;
};

#endif // _TEST_NODE_H_