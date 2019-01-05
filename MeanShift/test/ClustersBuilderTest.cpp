#include <gtest/gtest.h>

#include "../Point.hpp"
#include "../ClustersBuilder.hpp"

TEST(ClustersBuilderTest, stopShiftingTest)
{
    std::vector<Point> points = {{1, 2}, {5, 5}};
    ClustersBuilder builder(points, 0);
    ASSERT_FALSE(builder.hasStoppedShifting(0));
    ASSERT_FALSE(builder.hasStoppedShifting(1));
    ASSERT_FALSE(builder.allPointsHaveStoppedShifting());

    builder.shiftPoint(0, {2, 2});
    ASSERT_FALSE(builder.hasStoppedShifting(0));
    ASSERT_FALSE(builder.hasStoppedShifting(1));
    ASSERT_FALSE(builder.allPointsHaveStoppedShifting());

    builder.shiftPoint(0, {2, 2});
    ASSERT_TRUE(builder.hasStoppedShifting(0));
    ASSERT_FALSE(builder.hasStoppedShifting(1));
    ASSERT_FALSE(builder.allPointsHaveStoppedShifting());

    builder.shiftPoint(1, {5, 5});
    ASSERT_TRUE(builder.hasStoppedShifting(0));
    ASSERT_TRUE(builder.hasStoppedShifting(1));
    ASSERT_TRUE(builder.allPointsHaveStoppedShifting());
}


TEST(ClustersBuilderTest, shiftPointTest)
{
    std::vector<Point> originalPoints = {{1, 2}, {3, 4}};
    ClustersBuilder builder(originalPoints, 0);
    ASSERT_EQ(builder.getShiftedPoint(0), Point({1, 2}));
    ASSERT_EQ(builder.getShiftedPoint(1), Point({3, 4}));

    builder.shiftPoint(0, {5, 5});
    ASSERT_EQ(builder.getShiftedPoint(0), Point({5, 5}));
}


TEST(ClustersBuilderTest, buildClustersTest)
{
    // each point is a cluster
    std::vector<Point> originalPoints = {{0, 0}, {1, 1}, {2, 2}, {8, 8}, {9, 9}, {10, 10}};
    ClustersBuilder builder = ClustersBuilder(originalPoints, 0);
    std::vector<Cluster> clusters = builder.buildClusters();
    ASSERT_EQ(clusters.size(), originalPoints.size());

    // find only one cluster
    builder = ClustersBuilder(originalPoints, 100);
    clusters = builder.buildClusters();
    ASSERT_EQ(clusters.size(), 1);

    // find two clusters
    builder = ClustersBuilder(originalPoints, 0);
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

