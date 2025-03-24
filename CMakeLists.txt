cmake_minimum_required(VERSION 3.20)
project(M3AP)

set(CMAKE_CXX_STANDARD 20)
include_directories(.)

add_executable(M3AP main.cpp AVLTREE.cpp)


