project(serial)
cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_module)
set(CMAKE_BUILD_TYPE Release)


find_package(Glog REQUIRED)
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  roslib
  actionlib
  common
  rm_msgs
  tf
  tf2_ros
  )
catkin_package(
	INCLUDE_DIRS	
	CATKIN_DEPENDS roscpp std_msgs roslib
)
#include_directories(${CMAKE_SOURCE_DIR} ${catkin_INCLUDE_DIRS})
find_package(ProtoBuf REQUIRED)
file(GLOB ProtoFiles "${CMAKE_CURRENT_SOURCE_DIR}/proto/*.proto")
rrts_protobuf_generate_cpp(${CMAKE_CURRENT_SOURCE_DIR}/proto PROTO_SRCS PROTO_HDRS ${ProtoFiles})
include_directories(proto/)




add_executable(serial_com_node ${SerialProtoSrc} ${SerialProtoHds} ${PROTO_SRCS} ${PROTO_HDRS} serial_com_node.cpp)
target_include_directories(serial_com_node 
	PUBLIC 
	${CMAKE_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR} 
	${catkin_INCLUDE_DIRS}
)
target_link_libraries(serial_com_node
		PRIVATE
		common::rrts
        ${catkin_LIBRARIES}
        ${PROTOBUF_LIBRARIES}
        ${GLOG_LIBRARY}
        )
add_dependencies(serial_com_node
  rm_msgs_generate_messages)
