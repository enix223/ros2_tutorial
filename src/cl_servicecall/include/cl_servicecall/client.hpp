#pragma once

#include <rclcpp/rclcpp.hpp>

#include "cl_greeting_interfaces/srv/greeting.hpp"

namespace cl {

class GreetingClient : public rclcpp::Node {
 public:
  GreetingClient();

 private:
  void timer_callback();

  rclcpp::Client<cl_greeting_interfaces::srv::Greeting>::SharedPtr client_;
  rclcpp::TimerBase::SharedPtr timer_;
  int counter_;
};

}  // namespace cl
