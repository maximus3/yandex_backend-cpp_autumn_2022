cmake_minimum_required(VERSION 2.8.12)
project(utils)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME} dt_utils.cpp dt_utils.h validators.cpp validators.h)