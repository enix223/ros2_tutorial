#include <rclcpp/rclcpp.hpp>

#include "cl_action/server.hpp"

int main(int argc, char const* argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<cl::RobotMoveActionServer>());
  rclcpp::shutdown();
  return 0;
}
