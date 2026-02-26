#include "cl_pubsub/pub.hpp"

#include "cl_pubsub/common.hpp"

using namespace std::chrono_literals;

cl::SimplePublisher::SimplePublisher() : Node("simple_publisher"), count_(0) {
  publisher_ =
      this->create_publisher<std_msgs::msg::String>(cl::kSimpleTopicName, 10);
  timer_ = this->create_wall_timer(
      500ms, std::bind(&SimplePublisher::timer_callback, this));
}

void cl::SimplePublisher::timer_callback() {
  auto message = std_msgs::msg::String();
  message.data = "Hello world! " + std::to_string(count_++);
  RCLCPP_INFO(this->get_logger(), "publishing %s", message.data.c_str());
  publisher_->publish(message);
}
