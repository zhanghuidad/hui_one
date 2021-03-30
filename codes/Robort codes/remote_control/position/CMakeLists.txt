project(position)
cmake_minimum_required(VERSION 3.1)
add_compile_options(-std=c++11)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_module)
set(CMAKE_BUILD_TYPE Release)
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  roslib
  actionlib
  rm_msgs
)
catkin_package(
	INCLUDE_DIRS	
	CATKIN_DEPENDS roscpp std_msgs roslib
)


include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)


add_executable(main src/main.cpp)
target_include_directories(main 
	PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR} 
	${catkin_INCLUDE_DIRS}
)
target_link_libraries(main
   ${catkin_LIBRARIES}
)
#add_dependencies(main
#  rm_msgs_generate_messages)

