cmake_minimum_required(VERSION 3.16)

project(case_2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(TEST_SRC
    linear_size.cpp
    color.cpp
    surface.cpp
    pool_of_surfaces.cpp
    )

add_library(case_2 ${TEST_SRC})
target_link_libraries(case_2 PRIVATE Threads::Threads)
