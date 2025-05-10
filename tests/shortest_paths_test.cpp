#include <gtest/gtest.h>
#include "graph.h"

TEST(GraphTest, SmallGraph) {
    const Matrix<int, int> m = {
        {0, {{1, 1}, {2, 3}}},
        {1, {{2, 1}, {3, 2}}},
    };
    Graph<int, int> g(m);

    auto paths = g.getShortestPaths(0);

    EXPECT_EQ(paths[0], (std::vector<int>{0}));
    EXPECT_EQ(paths[1], (std::vector<int>{0, 1}));
    EXPECT_EQ(paths[2], (std::vector<int>{0, 1, 2}));
    EXPECT_EQ(paths[3], (std::vector<int>{0, 1, 3}));
}

TEST(GraphTest, BigGraph) {
    const Matrix<char, int> m = {
        { 'A', { {'B', 5}, {'C', 2} } },
        { 'B', { {'D', 3}, {'E', 7} } },
        { 'C', { {'B', 2}, {'G', 9} } },
        { 'D', { {'C', 3}, {'E', 2}, {'G', 6} } },
        { 'E', { {'G', 5}, {'H', 7}, {'F', 8} } },
        { 'F', { {'I', 4} } },
        { 'G', { {'H', 2} } },
        { 'H', { {'F', 3} } }
    };

    Graph<char, int> g(m);

    auto paths = g.getShortestPaths('A');

    EXPECT_EQ(paths['A'], (std::vector<char>{'A'}));
    EXPECT_EQ(paths['B'], (std::vector<char>{'A', 'C', 'B'}));
    EXPECT_EQ(paths['C'], (std::vector<char>{'A', 'C'}));
    EXPECT_EQ(paths['D'], (std::vector<char>{'A', 'C', 'B', 'D'}));
    EXPECT_EQ(paths['E'], (std::vector<char>{'A', 'C', 'B', 'D', 'E'}));
    EXPECT_EQ(paths['F'], (std::vector<char>{'A', 'C', 'G', 'H', 'F'}));
    EXPECT_EQ(paths['G'], (std::vector<char>{'A', 'C', 'G'}));
    EXPECT_EQ(paths['H'], (std::vector<char>{'A', 'C', 'G', 'H'}));
    EXPECT_EQ(paths['I'], (std::vector<char>{'A', 'C', 'G', 'H', 'F', 'I'}));
}
