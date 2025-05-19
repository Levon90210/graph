#include <gtest/gtest.h>
#include "graph.h"

TEST(GraphTest, SmallGraph) {
    const Matrix<int, int> m = {
        {0, {{1, 7}, {2, 5}, {4, 10}}},
        {1, {{0, 7},{3, 3}, {5, 2}}},
        {2, {{0, 5}, {3, 4}, {4, 8}}},
        {3, {{1, 3}, {2, 4}, {5, 10}}},
        {4, {{0, 10}, {2, 8}, {5, 9}}},
        {5, {{1, 2}, {3, 10}, {4, 9}}}
    };

    Graph<int, int> g(m);

    const auto mst = g.mstKruskal();

    EXPECT_EQ(mst.size(), 5);
    EXPECT_EQ(mst[0].first, 1);
    EXPECT_EQ(mst[0].second, 5);
    EXPECT_EQ(mst[1].first, 1);
    EXPECT_EQ(mst[1].second, 3);
    EXPECT_EQ(mst[2].first, 2);
    EXPECT_EQ(mst[2].second, 3);
    EXPECT_EQ(mst[3].first, 0);
    EXPECT_EQ(mst[3].second, 2);
    EXPECT_EQ(mst[4].first, 2);
    EXPECT_EQ(mst[4].second, 4);
}

TEST(GraphTest, BigGraph) {
    const Matrix<std::string, int> m = {
        {"v0", {{"v1", 4}, {"v3", 17}, {"v4", 8}, {"v5", 10}, {"v8", 12}, {"v9", 9}}},
        {"v1", {{"v0", 4}, {"v2", 3}, {"v5", 6}, {"v6", 2}}},
        {"v2", {{"v1", 3}, {"v4", 15}, {"v3", 16}}},
        {"v3", {{"v0", 17}, {"v4", 8}, {"v2", 16}}},
        {"v4", {{"v0", 8}, {"v3", 8}, {"v2", 15}, {"v5", 11}}},
        {"v5", {{"v0", 10}, {"v1", 6}, {"v4", 11}, {"v6", 1}, {"v7", 6}, {"v8", 5}}},
        {"v6", {{"v1", 2}, {"v5", 1}, {"v7", 7}}},
        {"v7", {{"v5", 6}, {"v6", 7}, {"v8", 14}}},
        {"v8", {{"v0", 12}, {"v5", 5}, {"v7", 14}, {"v9", 13}}},
        {"v9", {{"v0", 9}, {"v8", 13}}}
    };

    Graph<std::string, int> g(m);

    const auto mst = g.mstKruskal();

    EXPECT_EQ(mst.size(), 9);
    EXPECT_EQ(mst[0].first, "v6");
    EXPECT_EQ(mst[0].second, "v5");
    EXPECT_EQ(mst[1].first, "v1");
    EXPECT_EQ(mst[1].second, "v6");
    EXPECT_EQ(mst[2].first, "v2");
    EXPECT_EQ(mst[2].second, "v1");
    EXPECT_EQ(mst[3].first, "v1");
    EXPECT_EQ(mst[3].second, "v0");
    EXPECT_EQ(mst[4].first, "v5");
    EXPECT_EQ(mst[4].second, "v8");
}