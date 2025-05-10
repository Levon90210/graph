#include <gtest/gtest.h>
#include "graph.h"

TEST(GraphTest, BigGraph) {
    const Matrix<char, int> m = {
        {'A', {{'B', 3}, {'C', 8}, {'E', -4}}},
        {'B', {{'D', 1}, {'E', 7}}},
        {'C', {{'B', 4}}},
        {'D', {{'C', -5}}},
        {'E', {{'D', 6}}}
    };
    Graph<char, int> g(m);

    auto distances = g.floydWarshall();
    EXPECT_EQ(distances['A']['B'], 1);
    EXPECT_EQ(distances['A']['C'], -3);
    EXPECT_EQ(distances['A']['D'], 2);
    EXPECT_EQ(distances['A']['E'], -4);
    EXPECT_EQ(distances['B']['C'], -4);
    EXPECT_EQ(distances['B']['D'], 1);
    EXPECT_EQ(distances['B']['E'], 7);
    EXPECT_EQ(distances['C']['B'], 4);
    EXPECT_EQ(distances['C']['D'], 5);
    EXPECT_EQ(distances['C']['E'], 11);
    EXPECT_EQ(distances['D']['C'], -5);
    EXPECT_EQ(distances['D']['B'], -1);
    EXPECT_EQ(distances['D']['E'], 6);
    EXPECT_EQ(distances['E']['B'], 5);
    EXPECT_EQ(distances['E']['C'], 1);
    EXPECT_EQ(distances['E']['D'], 6);
}