cmake_minimum_required(VERSION 3.14)
project(Graph)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

enable_testing()
add_subdirectory(external/googletest)

add_subdirectory(tests)