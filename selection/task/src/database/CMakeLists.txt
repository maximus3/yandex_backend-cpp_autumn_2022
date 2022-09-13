cmake_minimum_required(VERSION 2.8.12)
project(database)

set(CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

add_library(database database.h database.cpp database_creator.h databse_creator.cpp)
