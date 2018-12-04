#include <gtest/gtest.h>

#include "../Point.hpp"
#include "../ClustersBuilder.hpp"


TEST(ClustersBuilderTest, subscriptOperatorTest)
{
    std::vector<Point> originalPoints = {{1, 2}, {3, 4}};
    ClustersBuilder builder(originalPoints);
    ASSERT_EQ(builder.getShiftedPoint(0), Point({1, 2}));
    ASSERT_EQ(builder.getShiftedPoint(1), Point({3, 4}));

    builder.shiftPoint(0, {5, 5});
    ASSERT_EQ(builder.getShiftedPoint(0), Point({5, 5}));
}


TEST(ClustersBuilderTest, buildClustersTest)
{
    std::vector<Point> originalPoints = {{0, 0}, {1, 1}, {2, 2}, {8, 8}, {9, 9}, {10, 10}};
    ClustersBuilder builder = ClustersBuilder(originalPoints);

    std::vector<Cluster> clusters = builder.buildClusters();
    ASSERT_EQ(clusters.size(), originalPoints.size());

    builder.shiftPoint(0, {1, 1});
    builder.shiftPoint(2, {1, 1});
    builder.shiftPoint(3, {9, 9});
    builder.shiftPoint(5, {9, 9});
    clusters = builder.buildClusters();
    ASSERT_EQ(clusters.size(), 2);

    ASSERT_EQ(clusters[0].getCentroid(), Point({1, 1}));
    ASSERT_EQ(clusters[0].getSize(), 3);

    ASSERT_EQ(clusters[1].getCentroid(), Point({9, 9}));
    ASSERT_EQ(clusters[1].getSize(), 3);
}

