cmake_minimum_required(VERSION 3.16)

project(case_1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(Catch2 REQUIRED)

set(TEST_SRC
    example.cpp
    test.cpp
   )

add_executable(case_1 ${TEST_SRC})

