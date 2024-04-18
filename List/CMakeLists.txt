cmake_minimum_required(VERSION 2.8)

project(test)

set(CMAKE_CXX_STANDARD 11)

set(SRC_LIST test.cpp)

set(CMAKE_BUILD_TYPE DEBUG)

add_compile_options(-Wunused -fno-elide-constructors)

add_executable(test ${SRC_LIST})
