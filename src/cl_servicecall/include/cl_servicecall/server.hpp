#pragma once

#include <memory>
#include <rclcpp/rclcpp.hpp>

#include "cl_greeting_interfaces/srv/greeting.hpp"

namespace cl {

class GreetingServer : public rclcpp::Node {
 public:
  GreetingServer();

 private:
  void handle_greeting(
      const std::shared_ptr<cl_greeting_interfaces::srv::Greeting_Request>
          request,
      std::shared_ptr<cl_greeting_interfaces::srv::Greeting_Response> response);

  rclcpp::Service<cl_greeting_interfaces::srv::Greeting>::SharedPtr service_;
};

}  // namespace cl
