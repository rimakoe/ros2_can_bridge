cmake_minimum_required(VERSION 3.8)
project(test_node_canlib)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# set(LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:/usr/local/lib/can_lib)
set(STANDARD_CPP_LIB_DIR /usr/local/lib)
set(STANDARD_CPP_INCLUDE_DIR /usr/local/include)
set(can_lib_DIR ${STANDARD_CPP_LIB_DIR}/${PROJECT_NAME})
# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(can_msgs REQUIRED)

include_directories(include ${can_lib_INCLUDE_DIRS} ${can_msgs_INCLUDE_DIRS} ${STANDARD_CPP_INCLUDE_DIR}/can_lib)
add_executable(${PROJECT_NAME} src/test_node.cpp)
target_link_libraries(${PROJECT_NAME} ${rclcpp_LIBRARIES} ${can_msgs_LIBRARIES} ${STANDARD_CPP_LIB_DIR}/can_lib/libcan_lib.so)
ament_target_dependencies(${PROJECT_NAME} rclcpp can_msgs)

install(
  DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

install(
  DIRECTORY include/${PROJECT_NAME}
  DESTINATION include
)

install(
  DIRECTORY /usr/local/lib/can_lib
  DESTINATION lib
)

install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}
  LIBRARY DESTINATION lib/${PROJECT_NAME}
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
