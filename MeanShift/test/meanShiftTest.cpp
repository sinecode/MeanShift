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
    ASSERT_EQ(points, std::vector<Point>({{1.1, 1.2}, {2.1, 2.2}, {3.1, 3.2}}));
}


TEST(MeanShiftTest, EuclideanDistanceTest)
{
    ASSERT_DEATH(euclideanDistance({1}, {3, 4}), "size");

    ASSERT_DEATH(euclideanDistance({}, {}), "empty");

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

    ASSERT_EQ(cluster.getCentroid(), expectedCentroid);
    ASSERT_EQ(cluster.getSize(), 3);
    ASSERT_EQ(cluster.getPoints(), points);
    ASSERT_NEAR(cluster.getSse(), 4, 0.00000000001);
}


TEST(MeanShiftTest, ClustersBuilderTest)
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


TEST(MeanShiftTest, MeanShiftClusteringTest)
{
    std::vector<Point> points = {{1, 1}, {0.5, 0.5}, {1.5, 1.5}, {2, 2}, {1.5, 2}, {2, 1.5}, {0.5, 1}, {1, 0.5},
            {0.0, 0.5}, {1.5, 1}, {11, 11}, {10.5, 10.5}, {11.5, 11.5}, {12, 12}, {11.5, 12}, {12, 11.5}, {10.5, 11},
            {11, 10.5}, {10.0, 10.5}, {11.5, 11}};

    std::vector<Cluster> clusters = meanShift(points, 4, 10000);
    ASSERT_EQ(clusters.size(), 2);
    std::vector<Point> firstCluster = {{1, 1}, {0.5, 0.5}, {1.5, 1.5}, {2, 2}, {1.5, 2}, {2, 1.5}, {0.5, 1}, {1, 0.5},
            {0.0, 0.5}, {1.5, 1}};
    ASSERT_EQ(clusters[0].getPoints(), firstCluster);
    std::vector<Point> secondCluster = {{11, 11}, {10.5, 10.5}, {11.5, 11.5}, {12, 12}, {11.5, 12}, {12, 11.5},
            {10.5, 11}, {11, 10.5}, {10.0, 10.5}, {11.5, 11}};
    ASSERT_EQ(clusters[1].getPoints(), secondCluster);

    clusters = meanShift(points, 20, 10000);
    ASSERT_EQ(clusters.size(), 1);
    ASSERT_EQ(clusters[0].getPoints(), points);

    clusters = meanShift(points, 0.1, 10000);
    ASSERT_EQ(clusters.size(), points.size());
}