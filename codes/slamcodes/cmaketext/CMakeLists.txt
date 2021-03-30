cmake_minimum_required(VERSION 2.8)

#声明一个cmake工程
project ( HelloSlam )



#find_package(OpenCV REQUIRED)
#include_directories( ${OpenCV_INCLUDE_DIRS} )
##
#add_library(libhelloslam SHARED libhelloslam.cpp)


#添加一个可执行程序
#语法的：add_executable (程序名 源代码文件）
add_executable(usehello usehello.cpp)

add_executable(libhelloslam libhelloslam.cpp)

#target_link_libraries(usehello libhelloslam)


