cmake_minimum_required(VERSION 3.8)
project(computer_vision)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(cv_node src/cv_node.cpp)
ament_target_dependencies(cv_node rclcpp sensor_msgs cv_bridge OpenCV)

install(TARGETS
  cv_node
  DESTINATION lib/${PROJECT_NAME})

# add_executable(cv_node src/cv_node.cpp)
# target_include_directories(cv_node PUBLIC
#   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#   $<INSTALL_INTERFACE:include>
#   # Include directories for ROS 2 and OpenCV
#   ${rclcpp_INCLUDE_DIRS}
#   ${sensor_msgs_INCLUDE_DIRS}
#   ${cv_bridge_INCLUDE_DIRS}
#   ${OpenCV_INCLUDE_DIRS}
# )
# target_compile_features(cv_node PUBLIC c_std_99 cxx_std_17) # Require C99 and C++17

# # Link libraries to the executable
# target_link_libraries(cv_node
#   # Link ROS 2 and OpenCV libraries
#   ${rclcpp_LIBRARIES}
#   ${cv_bridge_LIBRARIES}
#   ${OpenCV_LIBS}
# )


ament_package()
