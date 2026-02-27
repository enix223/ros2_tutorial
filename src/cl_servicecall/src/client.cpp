#include "cl_servicecall/client.hpp"

#include <chrono>

#include "cl_servicecall/common.hpp"

using namespace std::chrono_literals;

cl::GreetingClient::GreetingClient() : Node("greeting_client"), counter_(0) {
  client_ = this->create_client<cl_greeting_interfaces::srv::Greeting>(
      cl::kGreetingServiceName);

  timer_ = this->create_wall_timer(
      1s, std::bind(&GreetingClient::timer_callback, this));

  RCLCPP_INFO(this->get_logger(), "start periodic service call...");
}

void cl::GreetingClient::timer_callback() {
  if (!client_->wait_for_service(1s)) {
    RCLCPP_WARN(this->get_logger(), "service unavailable");
    return;
  }

  auto request =
      std::make_shared<cl_greeting_interfaces::srv::Greeting_Request>();
  request->name = "Person " + std::to_string(this->counter_++);

  auto callback =
      [this](rclcpp::Client<cl_greeting_interfaces::srv::Greeting>::SharedFuture
                 future) {
        auto response = future.get();
        RCLCPP_INFO(this->get_logger(), "Receive service call result: %s",
                    response->message.c_str());
      };

  client_->async_send_request(request, callback);
}
