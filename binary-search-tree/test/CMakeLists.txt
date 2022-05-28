add_executable(${PROJECT_NAME}_unittest
    node_insertion_test.cpp
    node_search_test.cpp
    test_helpers.hpp
)

find_package(GTest CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME}_unittest PRIVATE GTest::gtest_main ${PROJECT_NAME})

add_test(
    NAME ${PROJECT_NAME}_unittest
    COMMAND ${PROJECT_NAME}_unittest
)

set_tests_properties(${PROJECT_NAME}_unittest PROPERTIES TIMEOUT 60)
