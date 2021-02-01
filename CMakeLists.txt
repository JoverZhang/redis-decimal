cmake_minimum_required(VERSION 3.16)
project(decimal_module)

set(CMAKE_CXX_STANDARD 14)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/.test)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_subdirectory(./src)
add_executable(test
               ./test/test.cc
               ./test/test_utils.cc)
