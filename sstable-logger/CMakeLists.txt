project(sstable_logger)

add_library(${PROJECT_NAME} INTERFACE
)

target_include_directories(${PROJECT_NAME} INTERFACE
    include/
)

target_link_libraries(${PROJECT_NAME} INTERFACE binary_search_tree)

add_subdirectory(test)
