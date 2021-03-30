cmake_minimum_required(VERSION 2.8)
project(SiftObject)
find_package(OpenCV REQUIRED)

#include_directories( ${OpenCV_INCLUDE_DIRS} )
#add_library(yanseshibie SHARED yanseshibie.cpp)

#add_executable(houghline houghline.cpp)
#target_link_libraries(houghline ${OpenCV_LIBS})

#add_executable(houghcricle houghcricle.cpp)
#target_link_libraries(houghcricle ${OpenCV_LIBS})


#add_executable(Use use.cpp)
#target_link_libraries(Use yanseshibie)
#target_link_libraries(Use ${OpenCV_LIBS})

add_executable(Test test.cpp)
target_link_libraries(Test ${OpenCV_LIBS})
