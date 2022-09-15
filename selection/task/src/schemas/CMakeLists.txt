cmake_minimum_required(VERSION 2.8.12)
project(schemas)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME}
        base_schema.h
        error_schema.h
        system_item_type.h
        system_item_schema.h system_item_schema.cpp
        system_item_import_schema.h system_item_import_schema.cpp
        system_item_import_request.h system_item_import_request.cpp
        )
target_link_libraries(${PROJECT_NAME} utils)
