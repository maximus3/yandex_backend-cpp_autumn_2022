cmake_minimum_required(VERSION 2.8.12)
project(database)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME} pg_connection.h pg_connection.cpp pg_backend.h pg_backend.cpp)
