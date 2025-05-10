cmake_minimum_required(VERSION 3.14)
project(Graph)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

enable_testing()
add_subdirectory(external/googletest)

file(GLOB SRC1 "tests/shortest_paths_test.cpp" "src/*.cpp")
file(GLOB SRC2 "tests/floyd_warshall_test.cpp" "src/*.cpp")

add_executable(ShortestPathsTest ${SRC1})
target_link_libraries(ShortestPathsTest gtest gtest_main)

add_executable(FloydWarshallTest ${SRC2})
target_link_libraries(FloydWarshallTest gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(ShortestPathsTest)
gtest_discover_tests(FloydWarshallTest)