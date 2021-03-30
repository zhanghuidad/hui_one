project(transform)
cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_module)
set(CMAKE_BUILD_TYPE Release)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  roslib
  tf
  roborts_common
  rm_msgs
  )
catkin_package(
	INCLUDE_DIRS	include
	CATKIN_DEPENDS roscpp std_msgs roslib rm_msgs
)
###Settings for protobuffer
find_package(ProtoBuf REQUIRED)
file(GLOB ProtoFiles "${CMAKE_CURRENT_SOURCE_DIR}/proto/*.proto")
rrts_protobuf_generate_cpp(${CMAKE_CURRENT_SOURCE_DIR}/proto PROTO_SRCS PROTO_HDRS ${ProtoFiles})
include_directories(proto/)

###Adding executable files
#include_directories(include)
#add_executable(${PROJECT_NAME}_gimbal ${PROTO_SRCS} ${PROTO_HDRS} src/gimbal_transform.cpp)
#t#arget_include_directories(${PROJECT_NAME}_gimbal
#  PUBLIC
#  ${catkin_INCLUDE_DIRS}
#  )
#target_link_libraries(${PROJECT_NAME}_gimbal ${catkin_LIBRARIES} #${PROTOBUF_LIBRARIES})
#add_dependencies(${PROJECT_NAME}_gimbal rm_msgs_generate_messages)

