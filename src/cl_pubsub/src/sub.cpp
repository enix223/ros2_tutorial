#include "cl_pubsub/sub.hpp"

#include "cl_pubsub/common.hpp"

cl::SimpleSubscriber::SimpleSubscriber() : Node("simple_subscriber") {
  subscription_ = this->create_subscription<std_msgs::msg::String>(
      cl::kSimpleTopicName, 10,
      std::bind(&SimpleSubscriber::topic_callback, this,
                std::placeholders::_1));
}

void cl::SimpleSubscriber::topic_callback(const std_msgs::msg::String& msg) {
  RCLCPP_INFO(this->get_logger(), "Get message: %s", msg.data.c_str());
}
