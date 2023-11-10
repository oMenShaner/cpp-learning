cmake_minimum_required(VERSION 3.2)

project(wangrui)

set(CMAKE_CXX_STANDARD 11)

set(SRC_LIST test.cpp)

add_compile_options(-g -Wunused -fno-elide-constructors)

add_executable(wangrui ${SRC_LIST})
