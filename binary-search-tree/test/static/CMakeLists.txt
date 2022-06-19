add_library(${PROJECT_NAME}_statictest STATIC
    bt_concepts_test.cpp
)

target_link_libraries(${PROJECT_NAME}_statictest PRIVATE ${PROJECT_NAME})
