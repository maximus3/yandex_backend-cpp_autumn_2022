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

include_directories(schemas)
link_directories(schemas)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
        server
        database
        ${CONAN_LIBS})
