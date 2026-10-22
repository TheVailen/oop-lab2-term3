cmake_minimum_required(VERSION 3.16)
project(OOP_Lab2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")

find_package(GTest REQUIRED)

add_executable(main_app main.cpp my_string.cpp)

add_executable(test_app test_string.cpp my_string.cpp)
target_link_libraries(test_app GTest::gtest_main)

include(CTest)
add_test(NAME StringTests COMMAND test_app)
