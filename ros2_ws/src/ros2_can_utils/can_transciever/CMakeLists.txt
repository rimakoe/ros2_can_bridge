cmake_minimum_required(VERSION 3.8)
project(can_transciever)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(can_msgs REQUIRED)
find_package(can_interface REQUIRED)

include_directories(include ${can_msgs_INCLUDE_DIRS} ${can_interface_INCLUDE_DIRS})
add_library(${PROJECT_NAME} SHARED src/transciever.cpp include/${PROJECT_NAME}/endec.hpp)
target_link_libraries(${PROJECT_NAME} ${rclcpp_LIBRARIES} ${can_msgs_LIBRARIES} ${can_interface_LIBRARIES})
ament_target_dependencies(${PROJECT_NAME} rclcpp can_msgs can_interface)
ament_export_targets(${PROJECT_NAME} HAS_LIBRARY_TARGET)
ament_export_dependencies(can_msgs can_interface rclcpp)
ament_export_include_directories(include)

install(
  DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

install(
  DIRECTORY include/${PROJECT_NAME}
  DESTINATION include
)

install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib/${PROJECT_NAME}
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

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

ament_package()
