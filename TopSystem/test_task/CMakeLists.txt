cmake_minimum_required(VERSION 3.16)

project(test_task LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(simple_2D_lib)

find_package(SDL2 REQUIRED)

set(DEMO_APP_SRC
    main.cpp
    )

add_executable(demo_app ${DEMO_APP_SRC})
target_link_libraries(demo_app PRIVATE simple_2D_lib)
target_include_directories(demo_app PRIVATE simple_2D_lib/includes)
target_link_libraries(demo_app PRIVATE ${SDL2_LIBRARIES})