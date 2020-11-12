cmake_minimum_required(VERSION 3.16)

project(test_task LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(glm REQUIRED)

set(LIB_SRC
    ${PROJECT_SOURCE_DIR}/sources/engine.cpp
    ${PROJECT_SOURCE_DIR}/sources/camera.cpp
    ${PROJECT_SOURCE_DIR}/sources/shape.cpp
    ${PROJECT_SOURCE_DIR}/sources/painter.cpp
    ${PROJECT_SOURCE_DIR}/sources/default_painter.cpp
    ${PROJECT_SOURCE_DIR}/sources/color.cpp
    ${PROJECT_SOURCE_DIR}/sources/vertex_shader.cpp
    
    ${PROJECT_SOURCE_DIR}/sources/default_shapes/line.cpp
    )

add_library(simple_2D_lib ${LIB_SRC})
target_include_directories(simple_2D_lib PRIVATE ${PROJECT_SOURCE_DIR}/includes)
target_link_libraries(simple_2D_lib PRIVATE ${GLM_LIBRARIES})
