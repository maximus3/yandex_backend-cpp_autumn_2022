cmake_minimum_required(VERSION 3.23)
project(D)

set(CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

add_executable(D D.cpp)
