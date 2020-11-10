cmake_minimum_required(VERSION 3.16)

project(case_3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(TEST_SRC
    server_provider.cpp
    test.cpp
   )

add_executable(case_3 ${TEST_SRC})
target_link_libraries(case_3 PRIVATE Threads::Threads)
