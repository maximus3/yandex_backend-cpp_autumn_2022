cmake_minimum_required(VERSION 3.23)
project(E)

set(CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

add_executable(E E.cpp)
