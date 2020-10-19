cmake_minimum_required(VERSION 3.16)

project(cpp_study LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# TODO: here
#set(Qt5_DIR "/Users/mtrisha/goinfre/QT/5.15.0/clang_64/lib/cmake/Qt5/")

#set(SDL2_DIR "/Users/mtrisha/goinfre/SDL2/lib/cmake/SDL2/")
#find_package(SDL2 REQUIRED)

#set(BOOST_ROOT "/Users/mtrisha/goinfre/boost_1_74_0/")
#find_package(Boost 1.74.0 REQUIRED)

set(GENERAL_FLAGS -Wall -Wextra -pedantic -pthread)
set(RELEASE_FLAGS -O3 -D_NDEBUG)
set(DEBUG_FLAGS -g3 -D_DEBUG)
add_compile_options(${GENERAL_FLAGS})

#set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)
#add_compile_definitions(AUTOUIC)
#
#find_package(Qt5 COMPONENTS Widgets REQUIRED)
#find_package(Threads REQUIRED)

set(SRC_DIR ${PROJECT_SOURCE_DIR}/)

include_directories(${SRC_DIR})

set(SRC
    ${SRC_DIR}hello.cpp
    )

# RELEASE build
# for develop exclude from default build!
add_executable(hello EXCLUDE_FROM_ALL ${SRC})
target_compile_options(hello PRIVATE ${RELEASE_FLAGS})
#target_link_libraries(cpp_study PRIVATE Qt5::Widgets)
#target_link_libraries(cpp_study PRIVATE Threads::Threads)

# DEBUG build
add_executable(hello_debug ${SRC})
target_compile_options(hello_debug PRIVATE ${DEBUG_FLAGS})
#target_link_libraries(3DEngine_debug PRIVATE Qt5::Widgets)
#target_link_libraries(3DEngine_debug PRIVATE Threads::Threads)
#target_link_libraries(3DEngine_debug PRIVATE SDL2)
#
#target_include_directories(3DEngine_debug PRIVATE ${SDL2_INCLUDE_DIRS})
#target_link_libraries(3DEngine_debug PRIVATE ${SDL2_LIBRARIES})
#
#target_include_directories(3DEngine_debug PRIVATE ${Boost_INCLUDE_DIRS})
#target_link_libraries(3DEngine_debug PRIVATE ${Boost_LIBRARIES})