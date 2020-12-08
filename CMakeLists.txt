cmake_minimum_required(VERSION 3.0.2)
project(ros_processing)
find_package(catkin REQUIRED COMPONENTS
  roscpp
  roslib
  std_msgs
)
find_package(JNI REQUIRED)
catkin_package()
include_directories(
  ${catkin_INCLUDE_DIRS}
  ${JNI_INCLUDE_DIRS}
  submodules/TypedJNI
)
add_executable(${PROJECT_NAME}_node src/ros_processing_node.cpp submodules/TypedJNI/typedjni.cpp)
set_target_properties(${PROJECT_NAME}_node PROPERTIES OUTPUT_NAME node PREFIX "")
target_link_libraries(${PROJECT_NAME}_node
  ${catkin_LIBRARIES}
  ${JNI_LIBRARIES}
)
# TODO: build processing jar
# TODO: install processing jar
