#include <gtest/gtest.h>

#include "../Point.h"
#include "../ClustersBuilder.h"


TEST(ClustersBuilderTest, subscriptOperatorTest)
{
    std::vector<Point> originalPoints = {{1, 2}, {3, 4}};
    ClustersBuilder builder(originalPoints);
    ASSERT_EQ(builder[0], Point({1, 2}));
    ASSERT_EQ(builder[1], Point({3, 4}));

    builder[0] = {5, 5};
    ASSERT_EQ(builder[0], Point({5, 5}));
}


TEST(ClustersBuilderTest, buildClustersTest)
{
    std::vector<Point> originalPoints = {{0, 0}, {1, 1}, {2, 2}, {8, 8}, {9, 9}, {10, 10}};
    ClustersBuilder builder = ClustersBuilder(originalPoints);

    std::vector<Cluster> clusters = builder.buildClusters();
    ASSERT_EQ(clusters.size(), originalPoints.size());

    builder[0] = {1, 1};
    builder[2] = {1, 1};
    builder[3] = {9, 9};
    builder[5] = {9, 9};
    clusters = builder.buildClusters();
    ASSERT_EQ(clusters.size(), 2);

    ASSERT_EQ(clusters[0].getCentroid(), Point({1, 1}));
    ASSERT_EQ(clusters[0].getSize(), 3);

    ASSERT_EQ(clusters[1].getCentroid(), Point({9, 9}));
    ASSERT_EQ(clusters[1].getSize(), 3);
}

