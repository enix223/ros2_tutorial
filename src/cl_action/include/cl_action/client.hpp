#pragma once

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>

#include "cl_action/common.hpp"
#include "cl_robot_interfaces/action/robot_move.hpp"

namespace cl {
class RobotMoveActionClient : public rclcpp::Node {
 public:
  RobotMoveActionClient();
  void send_goal();

 private:
  void check_server_status();

  void feedback_callback(
      cl::ClientGoalHandleRobotMove::SharedPtr,
      const std::shared_ptr<const cl::RobotMove::Feedback> feedback);

  void result_callback(
      const cl::ClientGoalHandleRobotMove::WrappedResult& result);

  void goal_response_callback(
      const cl::ClientGoalHandleRobotMove::SharedPtr& goal_handle);

  rclcpp_action::Client<RobotMove>::SharedPtr client_;
  rclcpp::TimerBase::SharedPtr timer_;
  std::shared_ptr<ServerGoalHandleRobotMove> goal_handle_;
};

}  // namespace cl
