file(GLOB SRC1 "shortest_paths_test.cpp" "../src/*.cpp")
file(GLOB SRC2 "floyd_warshall_test.cpp" "../src/*.cpp")
file(GLOB SRC3 "mst_kruskal_test.cpp" "../src/*.cpp")

add_executable(ShortestPathsTest ${SRC1})
target_link_libraries(ShortestPathsTest gtest gtest_main)

add_executable(FloydWarshallTest ${SRC2})
target_link_libraries(FloydWarshallTest gtest gtest_main)

add_executable(MSTKruskalTest ${SRC3})
target_link_libraries(MSTKruskalTest gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(ShortestPathsTest)
gtest_discover_tests(FloydWarshallTest)
gtest_discover_tests(MSTKruskalTest)