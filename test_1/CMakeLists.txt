cmake_minimum_required(VERSION 3.8)
project(test_1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp node.h node.cpp node_map.h node_map.cpp num_set.h num_set.cpp)
add_executable(test_1 ${SOURCE_FILES})