project(global_planner)

add_subdirectory(a_star_planner)
set(CMAKE_BUILD_TYPE Release)
file(GLOB ProtoFiles "${CMAKE_CURRENT_SOURCE_DIR}/proto/*.proto")
rrts_protobuf_generate_cpp(${CMAKE_CURRENT_SOURCE_DIR}/proto GlobalPlannerProtoSrc GlobalPlannerProtoHds ${ProtoFiles})

include_directories(${catkin_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}_node
  ${GlobalPlannerProtoSrc}
  ${GlobalPlannerProtoHds}
  global_planner_node.cpp
)
target_link_libraries(${PROJECT_NAME}_node
  PRIVATE
  planning::global_planner::a_star_planner
  roborts_costmap
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
  ${GLOG_LIBRARY}
)
add_dependencies(${PROJECT_NAME}_node
  rm_msgs_generate_messages)

add_executable(${PROJECT_NAME}_test
  global_planner_test.cpp)
target_link_libraries(${PROJECT_NAME}_test
  PRIVATE
  ${catkin_LIBRARIES}
)
add_dependencies(${PROJECT_NAME}_test
  rm_msgs_generate_messages)

add_executable(${PROJECT_NAME}_base_test
  base_test.cpp)
target_link_libraries(${PROJECT_NAME}_base_test
  PRIVATE
  ${catkin_LIBRARIES}
)
add_dependencies(${PROJECT_NAME}_base_test
  rm_msgs_generate_messages)

add_executable(${PROJECT_NAME}_8
  global_planner_8.cpp)
target_link_libraries(${PROJECT_NAME}_8
  PRIVATE
  ${catkin_LIBRARIES}
)
add_dependencies(${PROJECT_NAME}_8
  rm_msgs_generate_messages)

add_executable(${PROJECT_NAME}_buff_test
  global_planner_buff_test.cpp)
target_link_libraries(${PROJECT_NAME}_buff_test
  PRIVATE
  ${catkin_LIBRARIES}
)
add_dependencies(${PROJECT_NAME}_buff_test
  rm_msgs_generate_messages)


  add_executable(${PROJECT_NAME}_8_buff
  global_planner_8_buff.cpp)
target_link_libraries(${PROJECT_NAME}_8_buff
  PRIVATE
  ${catkin_LIBRARIES}
)
add_dependencies(${PROJECT_NAME}_8_buff
  rm_msgs_generate_messages)


   add_executable(${PROJECT_NAME}_0314_bule
  global_planner_0314_bule.cpp)
target_link_libraries(${PROJECT_NAME}_0314_bule
  PRIVATE
  ${catkin_LIBRARIES}
)
add_dependencies(${PROJECT_NAME}_0314_bule
  rm_msgs_generate_messages)
