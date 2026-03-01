cmake_minimum_required(VERSION 3.8)
project(cl_action)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(action_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

rosidl_generate_interfaces(${PROJECT_NAME}
  "action/RobotMove.action"
  
  DEPENDENCIES 
    action_msgs
    geometry_msgs
    builtin_interfaces
)

# Create server executable
add_executable(server src/main_server.cpp)
ament_target_dependencies(server rclcpp)
target_include_directories(server PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Create client executable
add_executable(client src/main_client.cpp)
ament_target_dependencies(client rclcpp)
target_include_directories(client PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Install executables
install(TARGETS
  server
  client
  DESTINATION lib/${PROJECT_NAME})

ament_package()
