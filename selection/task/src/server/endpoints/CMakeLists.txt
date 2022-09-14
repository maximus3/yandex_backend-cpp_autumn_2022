cmake_minimum_required(VERSION 2.8.12)
project(endpoints)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME} nodes.h nodes.cpp imports.cpp imports.h delete.cpp delete.h)
target_link_libraries(${PROJECT_NAME} utils schemas)