cmake_minimum_required(VERSION 3.23)
project(contest)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(A)
add_subdirectory(B)
add_subdirectory(C)
add_subdirectory(D)
add_subdirectory(E)

add_executable(contest main.cpp)
