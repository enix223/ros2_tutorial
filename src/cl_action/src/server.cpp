#include "cl_action/server.hpp"

cl::RobotMoveActionServer::RobotMoveActionServer() : Node("robot_move_server") {
  action_server_ = rclcpp_action::create_server<RobotMove>(
      this, cl::kRobotMoveActionName,
      std::bind(&RobotMoveActionServer::handle_goal, this,
                std::placeholders::_1, std::placeholders::_2),
      std::bind(&RobotMoveActionServer::handle_cancel, this,
                std::placeholders::_1),
      std::bind(&RobotMoveActionServer::handle_accepted, this,
                std::placeholders::_1));
  RCLCPP_INFO(get_logger(), "server started");
}

rclcpp_action::GoalResponse cl::RobotMoveActionServer::handle_goal(
    const rclcpp_action::GoalUUID&,
    std::shared_ptr<const RobotMove::Goal> goal) {
  RCLCPP_INFO(this->get_logger(),
              "accepted move goal, move to (%.2f, %.2f, %.2f), speed %.2f",
              goal->target_position.x, goal->target_position.y,
              goal->target_position.z, goal->target_speed);
  return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
}

rclcpp_action::CancelResponse cl::RobotMoveActionServer::handle_cancel(
    const std::shared_ptr<ServerGoalHandleRobotMove>) {
  RCLCPP_INFO(this->get_logger(), "accept cancel request");
  return rclcpp_action::CancelResponse::ACCEPT;
}

void cl::RobotMoveActionServer::handle_accepted(
    const std::shared_ptr<ServerGoalHandleRobotMove> goal_handle) {
  RCLCPP_INFO(this->get_logger(), "action accepted, start moving...");
  std::thread{[this, goal_handle] { this->execute(goal_handle); }}.detach();
}

void cl::RobotMoveActionServer::execute(
    const std::shared_ptr<ServerGoalHandleRobotMove> goal_handle) {
  auto goal = goal_handle->get_goal();
  auto feedback = std::make_shared<RobotMove::Feedback>();
  auto result = std::make_shared<RobotMove::Result>();

  float moved = 0.0f;
  float total_distance =
      sqrt(pow(goal->target_position.x, 2) + pow(goal->target_position.y, 2) +
           pow(goal->target_position.z, 2));

  while (moved < total_distance) {
    if (goal_handle->is_canceling()) {
      result->success = false;
      result->message = "canceled";
      result->final_position.x =
          moved / total_distance * goal->target_position.x;
      result->final_position.y =
          moved / total_distance * goal->target_position.y;
      result->final_position.z =
          moved / total_distance * goal->target_position.z;
      goal_handle->canceled(result);
      RCLCPP_INFO(this->get_logger(), "action canceled");
      return;
    }

    moved += goal->target_speed * 0.5;
    feedback->current_position.x =
        moved / total_distance * goal->target_position.x;
    feedback->current_position.y =
        moved / total_distance * goal->target_position.y;
    feedback->current_position.z =
        moved / total_distance * goal->target_position.z;
    goal_handle->publish_feedback(feedback);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }

  // done
  result->success = true;
  result->message = "success";
  goal_handle->succeed(result);
  RCLCPP_INFO(this->get_logger(), "action done");
}
