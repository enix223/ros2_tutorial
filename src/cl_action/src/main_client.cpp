#include <rclcpp/rclcpp.hpp>

#include "cl_action/client.hpp"

int main(int argc, char const* argv[]) {
  rclcpp::init(argc, argv);

  auto client = std::make_shared<cl::RobotMoveActionClient>();
  client->send_goal();
  rclcpp::spin(client);

  rclcpp::shutdown();
  return 0;
}
