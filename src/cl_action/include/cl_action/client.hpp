#pragma once

#include <rclcpp/rclcpp.hpp>

namespace cl {
class RobotMoveActionClient : public rclcpp::Node {
 public:
  RobotMoveActionClient();
};

}  // namespace cl
