add_executable(${PROJECT_NAME}_unittest
    node_deletion_test.cpp
    node_insertion_test.cpp
    node_search_test.cpp
    iterator_test.cpp
)

find_package(GTest CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME}_unittest PRIVATE GTest::gtest_main ${PROJECT_NAME} ${PROJECT_NAME}_test_utils)
