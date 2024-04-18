cmake_minimum_required(VERSION 3.2)

set(CMAKE_C_COMPILER /opt/rh/devtoolset-11/root/usr/bin/gcc)
set(CMAKE_CXX_COMPILER /opt/rh/devtoolset-11/root/usr/bin/g++)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
project(test)

set(CMAKE_CXX_STANDARD 11)

set(SRC_LIST test.cpp)

set(CMAKE_BUILD_TYPE DEBUG)

add_compile_options(-Wunused -fno-elide-constructors)

add_executable(test ${SRC_LIST})
