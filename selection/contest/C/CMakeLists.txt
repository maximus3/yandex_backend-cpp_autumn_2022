cmake_minimum_required(VERSION 3.23)
project(C)

set(CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

add_executable(C C.cpp json.hpp)
