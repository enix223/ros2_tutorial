#pragma once

#include <rclcpp_action/rclcpp_action.hpp>

#include "cl_robot_interfaces/action/robot_move.hpp"

namespace cl {
constexpr const char* kRobotMoveActionName = "robot_action_move";

using RobotMove = cl_robot_interfaces::action::RobotMove;
using ServerGoalHandleRobotMove = rclcpp_action::ServerGoalHandle<RobotMove>;
using ClientGoalHandleRobotMove = rclcpp_action::ClientGoalHandle<RobotMove>;

}  // namespace cl
