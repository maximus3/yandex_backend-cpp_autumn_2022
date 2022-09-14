cmake_minimum_required(VERSION 2.8.12)
project(disk_rest_api)
set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(database utils schemas server)
link_directories(database utils schemas server)
add_subdirectory(database)
add_subdirectory(utils)
add_subdirectory(server)
add_subdirectory(schemas)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
        schemas
        server
        database
        utils
        ${CONAN_LIBS})
