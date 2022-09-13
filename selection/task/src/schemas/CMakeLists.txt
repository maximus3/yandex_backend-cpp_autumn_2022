cmake_minimum_required(VERSION 2.8.12)
project(schemas)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME} base_schema.h error_schema.h)
