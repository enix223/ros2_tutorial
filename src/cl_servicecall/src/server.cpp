#include "cl_servicecall/server.hpp"

#include <string>

#include "cl_servicecall/common.hpp"

cl::GreetingServer::GreetingServer() : Node("greeting_server") {
  service_ = this->create_service<cl_greeting_interfaces::srv::Greeting>(
      cl::kGreetingServiceName,
      std::bind(&GreetingServer::handle_greeting, this, std::placeholders::_1,
                std::placeholders::_2));

  RCLCPP_INFO(this->get_logger(), "waiting for client...");
}

void cl::GreetingServer::handle_greeting(
    const std::shared_ptr<cl_greeting_interfaces::srv::Greeting_Request>
        request,
    std::shared_ptr<cl_greeting_interfaces::srv::Greeting_Response> response) {
  auto now = this->get_clock()->now();
  RCLCPP_INFO(this->get_logger(), "Receive request, name = %s",
              request->name.c_str());
  response->message = "Hello, " + request->name;
}