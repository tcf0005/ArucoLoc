
cmake_minimum_required(VERSION 2.8)
project( Aruco.cpp )                                 #replace test
find_package( OpenCV REQUIRED )
add_executable( Aruco Aruco.cpp )                 #replace test and test.cpp
target_link_libraries( Aruco ${OpenCV_LIBS} )    #replace test