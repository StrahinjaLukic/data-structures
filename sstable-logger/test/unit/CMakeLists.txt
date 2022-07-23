add_executable(${PROJECT_NAME}_unittest
    simple_test.cpp
)

find_package(GTest CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME}_unittest PRIVATE GTest::gtest_main ${PROJECT_NAME})
