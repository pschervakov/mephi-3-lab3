cmake_minimum_required(VERSION 3.17)
project(mephi_3_lab3)

set(CMAKE_CXX_STANDARD 14)

add_executable(mephi_3_lab3 main.cpp )

project(mephi_3_lab3_test)
add_executable(mephi_3_lab3_test tests.cpp)
target_link_libraries(mephi_3_lab3_test gtest gtest_main)