cmake_minimum_required(VERSION 3.0.2)
project(moebiustech_stm32_ros)


find_package(catkin REQUIRED COMPONENTS
  controller_manager
  hardware_interface
  message_generation
  realtime_tools
  roscpp
  roslaunch
  rosserial_server
  sensor_msgs
  std_msgs
  topic_tools
)

################################################
## Declare ROS messages, services and actions ##
################################################

## Generate messages in the 'msg' folder
add_message_files(FILES
  JointFeedback.msg
  Status.msg
  Drive.msg
  Feedback.msg
)

## Generate added messages and services with any dependencies listed here
generate_messages(DEPENDENCIES
  std_msgs
)

###################################
## catkin specific configuration ##
###################################

catkin_package(
  CATKIN_DEPENDS
  message_runtime
#  INCLUDE_DIRS include
#  LIBRARIES sengi_ros
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(moebiustech_stm32_node
  src/moebiustech_stm32_node.cpp
)

add_dependencies(moebiustech_stm32_node moebiustech_stm32_ros_gencpp)
target_link_libraries(moebiustech_stm32_node
  ${catkin_LIBRARIES}
)




#############
## Install ##
#############

install(TARGETS moebiustech_stm32_node
    ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
    LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
    RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
    )

install(DIRECTORY launch/
   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch )

install(DIRECTORY include/
   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/include )

install(DIRECTORY src/
   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/src )

install(DIRECTORY msg/
   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/msg )



#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_moebiustech_stm32_ros.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
