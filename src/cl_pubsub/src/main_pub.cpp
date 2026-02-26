#include "cl_pubsub/pub.hpp"

int main(int argc, char const* argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<cl::SimplePublisher>());
  rclcpp::shutdown();
  return 0;
}
