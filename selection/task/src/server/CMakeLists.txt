cmake_minimum_required(VERSION 2.8.12)
project(server)

set(CMAKE_CXX_STANDARD 20)

include_directories(endpoints)
link_directories(endpoints)
add_subdirectory(endpoints)

add_library(${PROJECT_NAME} server.h server.cpp json.hpp)
target_link_libraries(${PROJECT_NAME} endpoints)
