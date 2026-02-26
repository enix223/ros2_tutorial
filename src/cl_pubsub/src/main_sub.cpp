#include "cl_pubsub/sub.hpp"

int main(int argc, char const* argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<cl::SimpleSubscriber>());
  rclcpp::shutdown();
  return 0;
}