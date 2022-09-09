cmake_minimum_required(VERSION 2.8.12)
project(disk_rest_api)
set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(disk_rest_api main.cpp)
target_link_libraries(disk_rest_api ${CONAN_LIBS})