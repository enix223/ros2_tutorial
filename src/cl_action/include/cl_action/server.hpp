#pragma once

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>

#include "cl_action/common.hpp"
#include "cl_robot_interfaces/action/robot_move.hpp"

namespace cl {
class RobotMoveActionServer : public rclcpp::Node {
 public:
  using RobotMove = cl_robot_interfaces::action::RobotMove;
  using ServerGoalHandleRobotMove =
      rclcpp_action::ServerGoalHandle<cl_robot_interfaces::action::RobotMove>;

  RobotMoveActionServer();

 private:
  rclcpp_action::GoalResponse handle_goal(
      const rclcpp_action::GoalUUID& uuid,
      std::shared_ptr<const RobotMove::Goal> goal);

  rclcpp_action::CancelResponse handle_cancel(
      const std::shared_ptr<ServerGoalHandleRobotMove> goal_handle);

  void handle_accepted(const std::shared_ptr<ServerGoalHandleRobotMove> handle);

  void execute(const std::shared_ptr<ServerGoalHandleRobotMove> handle);

  rclcpp_action::Server<RobotMove>::SharedPtr action_server_;
};

}  // namespace cl
