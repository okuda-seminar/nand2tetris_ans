cmake_minimum_required(VERSION 3.13)
project(unittest)
find_package(GTest)

add_executable(parser_test parser_test.cpp)
add_executable(code_writer_test code_writer_test.cpp)

foreach(target parser_test code_writer_test)
  target_link_libraries(${target} ${GTEST_BOTH_LIBRARIES} pthread vm_translator)
  target_include_directories(${target} PUBLIC ${GTEST_INCLUDE_DIRS}, ../src)
endforeach()
