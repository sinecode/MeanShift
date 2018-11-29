#include <gtest/gtest.h>

#include "../Point.h"
#include "../meanShift.h"


TEST(MeanShiftTest, getPointsFromCsvTest)
{
    std::vector<Point> points = getPointsFromCsv("../../test/empty.csv");
    ASSERT_EQ(points.size(), 0);

    points = getPointsFromCsv("../../test/test.csv");
    ASSERT_EQ(points, std::vector<Point>({{1.1, 1.2}, {2.1, 2.2}, {3.1, 3.2}}));
}


TEST(MeanShiftTest, meanShiftTest)
{
    std::vector<Point> points = {{1, 1}, {0.5, 0.5}, {1.5, 1.5}, {2, 2}, {1.5, 2}, {2, 1.5}, {0.5, 1}, {1, 0.5},
            {0.0, 0.5}, {1.5, 1}, {11, 11}, {10.5, 10.5}, {11.5, 11.5}, {12, 12}, {11.5, 12}, {12, 11.5}, {10.5, 11},
            {11, 10.5}, {10.0, 10.5}, {11.5, 11}};

    // two clusters
    std::vector<Cluster> clusters = meanShift(points, 4);
    ASSERT_EQ(clusters.size(), 2);
    std::vector<Point> expectedFirstCluster = {{1, 1}, {0.5, 0.5}, {1.5, 1.5}, {2, 2}, {1.5, 2}, {2, 1.5}, {0.5, 1},
            {1, 0.5}, {0.0, 0.5}, {1.5, 1}};
    std::vector<Point> actualFirstCluster = std::vector<Point>(clusters[0].begin(), clusters[0].end());
    ASSERT_EQ(actualFirstCluster, expectedFirstCluster);
    std::vector<Point> expectedSecondCluster = {{11, 11}, {10.5, 10.5}, {11.5, 11.5}, {12, 12}, {11.5, 12},
            {12, 11.5}, {10.5, 11}, {11, 10.5}, {10.0, 10.5}, {11.5, 11}};
    std::vector<Point> actualSecondCluster = std::vector<Point>(clusters[1].begin(), clusters[1].end());
    ASSERT_EQ(actualSecondCluster, expectedSecondCluster);

    // one cluster with all the points
    clusters = meanShift(points, 20);
    ASSERT_EQ(clusters.size(), 1);
    std::vector<Point> actualCluster = std::vector<Point>(clusters[0].begin(), clusters[0].end());
    ASSERT_EQ(actualCluster, points);

    // each point is a separated cluster
    clusters = meanShift(points, 0.1);
    ASSERT_EQ(clusters.size(), points.size());
    for (auto &cluster : clusters)
        ASSERT_EQ(cluster.getSse(), 0);
}