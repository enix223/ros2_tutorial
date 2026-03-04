#include "cl_action/client.hpp"

cl::RobotMoveActionClient::RobotMoveActionClient() : Node("robot_move_client") {
  client_ =
      rclcpp_action::create_client<RobotMove>(this, cl::kRobotMoveActionName);
  timer_ = this->create_wall_timer(
      std::chrono::seconds(1),
      std::bind(&RobotMoveActionClient::check_server_status, this));
}

void cl::RobotMoveActionClient::check_server_status() {
  if (client_->action_server_is_ready()) {
    RCLCPP_INFO(get_logger(), "Action server ready");
    timer_->cancel();
  }
}

void cl::RobotMoveActionClient::feedback_callback(
    cl::ClientGoalHandleRobotMove::SharedPtr,
    const std::shared_ptr<const cl::RobotMove::Feedback> feedback) {
  RCLCPP_INFO(get_logger(), "current position, x=%.2f, y=%.2f, z=%.2f",
              feedback->current_position.x, feedback->current_position.y,
              feedback->current_position.z);
}

void cl::RobotMoveActionClient::result_callback(
    const cl::ClientGoalHandleRobotMove::WrappedResult& result) {
  switch (result.code) {
    case rclcpp_action::ResultCode::SUCCEEDED:
      RCLCPP_INFO(get_logger(), "Task done");
      break;
    case rclcpp_action::ResultCode::CANCELED:
      RCLCPP_INFO(get_logger(), "Task canceled");
      break;
    case rclcpp_action::ResultCode::ABORTED:
      RCLCPP_INFO(get_logger(), "Task aborted");
      break;
    default:
      RCLCPP_INFO(get_logger(), "unkonwn");
      break;
  }
}

void cl::RobotMoveActionClient::goal_response_callback(
    const cl::ClientGoalHandleRobotMove::SharedPtr& goal_handle) {
  if (!goal_handle) {
    RCLCPP_ERROR(get_logger(), "goal is rejected");
  } else {
    RCLCPP_INFO(get_logger(), "waiting for goal being accepted");
  }
}

void cl::RobotMoveActionClient::send_goal() {
  RCLCPP_INFO(get_logger(), "Send goal");
  if (!client_->wait_for_action_server(std::chrono::seconds(10))) {
    RCLCPP_ERROR(get_logger(), "Action server not ready");
    return;
  }

  // callbacks
  auto goal_options = rclcpp_action::Client<RobotMove>::SendGoalOptions();
  goal_options.feedback_callback =
      std::bind(&RobotMoveActionClient::feedback_callback, this,
                std::placeholders::_1, std::placeholders::_2);
  goal_options.result_callback = std::bind(
      &RobotMoveActionClient::result_callback, this, std::placeholders::_1);
  goal_options.goal_response_callback =
      std::bind(&RobotMoveActionClient::goal_response_callback, this,
                std::placeholders::_1);

  auto goal_msg = RobotMove::Goal();
  goal_msg.target_speed = 2;
  goal_msg.target_position.x = 10;
  goal_msg.target_position.y = 10;
  goal_msg.target_position.z = 0;
  client_->async_send_goal(goal_msg, goal_options);
}
