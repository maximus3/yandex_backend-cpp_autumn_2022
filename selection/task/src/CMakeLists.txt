cmake_minimum_required(VERSION 2.8.12)
project(disk_rest_api)
set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(database)
link_directories(database)
add_subdirectory(database)

include_directories(server)
link_directories(server)
add_subdirectory(server)

add_executable(disk_rest_api main.cpp)
target_link_libraries(disk_rest_api database)
target_link_libraries(disk_rest_api server)
target_link_libraries(disk_rest_api ${CONAN_LIBS})
