cmake_minimum_required(VERSION 3.8)
project(computer_vision)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

add_executable(cv_node src/cv_node.cpp)
target_include_directories(cv_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(cv_node PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17

install(TARGETS cv_node
  DESTINATION lib/${PROJECT_NAME})

ament_package()
