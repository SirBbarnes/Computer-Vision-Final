cmake_minimum_required(VERSION 3.16)
project(OpenCV_Demo)
find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 14)

add_executable(OpenCV_Demo main.cpp OpenCV_Final.cpp)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(OpenCV_Demo ${OpenCV_LIBS})

