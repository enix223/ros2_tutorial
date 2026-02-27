#include "cl_servicecall/server.hpp"

int main(int argc, char const* argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<cl::GreetingServer>());
  rclcpp::shutdown();
  return 0;
}
