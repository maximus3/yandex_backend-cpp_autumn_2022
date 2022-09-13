cmake_minimum_required(VERSION 2.8.12)
project(server)

set(CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

add_library(server server.h server.cpp)
