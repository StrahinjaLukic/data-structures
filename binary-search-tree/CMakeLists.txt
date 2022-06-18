cmake_minimum_required(VERSION 3.20)
project(binary_search_tree)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME} INTERFACE
)

target_include_directories(${PROJECT_NAME} INTERFACE
    include/
)

enable_testing()
add_subdirectory(test)
