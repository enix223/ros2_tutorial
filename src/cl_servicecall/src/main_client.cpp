#include "cl_servicecall/client.hpp"

int main(int argc, char const* argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<cl::GreetingClient>());
  rclcpp::shutdown();
  return 0;
}
