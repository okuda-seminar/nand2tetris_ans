cmake_minimum_required(VERSION 3.13)
project(unittest)
find_package(GTest)

add_executable(parser_test parser_test.cpp)
target_link_libraries(parser_test ${GTEST_BOTH_LIBRARIES} pthread assembler)
target_include_directories(parser_test PUBLIC ${GTEST_INCLUDE_DIRS}, ../src)