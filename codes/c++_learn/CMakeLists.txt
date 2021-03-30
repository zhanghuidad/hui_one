cmake_minimum_required(VERSION 2.8)

#声明一个cmake工程
project ( HelloOpencv )

find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(test myclasses.cpp two.cpp)

#add_executable(three_opencv three_opencv.cpp)
#target_link_libraries(three_opencv ${OpenCV_LIBS})
