cmake_minimum_required(VERSION 2.8)
project( l4 )
find_package( OpenCV REQUIRED )
add_executable( l4 l4.cpp )
target_link_libraries( l4 ${OpenCV_LIBS} )

