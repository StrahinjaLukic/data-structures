project(binary_search_tree)

add_library(${PROJECT_NAME} INTERFACE
)

target_include_directories(${PROJECT_NAME} INTERFACE
    include/
)

target_link_libraries(${PROJECT_NAME} INTERFACE ds_concepts)

add_subdirectory(test)
