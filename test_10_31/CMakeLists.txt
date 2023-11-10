cmake_minimum_required(VERSION 3.2)


project(test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_BUILD_TYPE Debug)

set(SRC_LIST test.cpp Date.cpp)

include_directories(${CMAKE_SOURCE_DIR}/build)

add_executable(test ${SRC_LIST})
