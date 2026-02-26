#include <chrono>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

namespace cl {

class SimpleSubscriber : public rclcpp::Node {
 public:
  SimpleSubscriber();

 private:
  void topic_callback(const std_msgs::msg::String& msg);

  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

}  // namespace cl
