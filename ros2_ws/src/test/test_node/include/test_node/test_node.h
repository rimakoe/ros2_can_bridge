#ifndef _TEST_NODE_H_
#define _TEST_NODE_H_

#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include <can_transciever/transciever.h>

class TestNode : public ros2can::Transciever
{
  public:
    TestNode();
    ~TestNode();
  
  private:
    rclcpp::TimerBase::SharedPtr timer_;
};

#endif // _TEST_NODE_H_