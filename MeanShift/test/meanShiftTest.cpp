#include <gtest/gtest.h>
#include "../meanShift.h"


TEST(MeanShiftTest, TestPoint)
{
    Point point = {3.4, 5.6, 3.2};
    ASSERT_EQ(point.size(), 3);
}


TEST(MeanShiftTest, CsvTest)
{
    std::vector<Point> points = getPointsFromCsv("../../test/empty.csv");
    ASSERT_EQ(points.size(), 0);

    points = getPointsFromCsv("../../test/test.csv");
    double expectedPoints[3][2] = {{1.1, 1.2}, {2.1, 2.2}, {3.1, 3.2}};
    int i = 0;
    do {
        ASSERT_EQ(points[0][0], expectedPoints[0][0]);
        ASSERT_EQ(points[0][1], expectedPoints[0][1]);
        ++i;
    } while (i < points.size());
}


TEST(MeanShiftTest, EuclideanDistanceTest)
{
    // points of different sizes
    ASSERT_DEATH(euclideanDistance({1}, {3, 4}), "size");

    // empty points
    ASSERT_DEATH(euclideanDistance({}, {}), "size");

    ASSERT_NEAR(euclideanDistance({0, 0}, {0, 0}), 0, 0.0000000001);
    ASSERT_NEAR(euclideanDistance({8, 6}, {5, 2}), 5, 0.0000000001);
    ASSERT_NEAR(euclideanDistance({2, 2, 20}, {2, 2, 50}), 30, 0.0000000001);
}


TEST(MeanShiftTest, ClusterTest)
{
    std::vector<Point> points = {{0, 0}, {1, 1}, {2, 2}};
    Point expectedCentroid = {1, 1};
    Cluster cluster = Cluster(expectedCentroid);
    for (Point p : points)
        cluster.addPoint(p);

    Point actualCentroid = cluster.getCentroid();
    ASSERT_EQ(actualCentroid[0], expectedCentroid[0]);
    ASSERT_EQ(actualCentroid[1], expectedCentroid[1]);

    ASSERT_NEAR(cluster.getSse(), 4, 0.00000000001);
}


TEST(MeanShiftTest, ClustersBuilderTest)
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
    ASSERT_EQ(clusters[0].getCentroid()[0], 1);
    ASSERT_EQ(clusters[0].getCentroid()[1], 1);
    ASSERT_EQ(clusters[1].getCentroid()[0], 9);
    ASSERT_EQ(clusters[1].getCentroid()[1], 9);
}