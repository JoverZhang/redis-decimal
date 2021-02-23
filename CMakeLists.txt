cmake_minimum_required(VERSION 3.10)
project(decimal_module)

set(CMAKE_CXX_STANDARD 14)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/.tests)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_subdirectory(./src)
add_executable(tests
               ./test/test.cc
               ./test/test_utils.cc)

target_link_libraries(tests decimal)
