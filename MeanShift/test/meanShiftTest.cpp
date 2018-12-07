#include <gtest/gtest.h>

#include "../meanShift.hpp"


class MeanShiftTest : public ::testing::Test {
protected:
    std::vector<Point> points = {{1, 1}, {0.5, 0.5}, {1.5, 1.5}, {2, 2}, {1.5, 2}, {2, 1.5}, {0.5, 1}, {1, 0.5},
            {0.0, 0.5}, {1.5, 1}, {11, 11}, {10.5, 10.5}, {11.5, 11.5}, {12, 12}, {11.5, 12}, {12, 11.5},
            {10.5, 11}, {11, 10.5}, {10.0, 10.5}, {11.5, 11}};
};

TEST_F(MeanShiftTest, twoClusters)
{
    std::vector<Cluster> clusters = meanShift(points, 1.0);
    ASSERT_EQ(clusters.size(), 2);
    std::vector<Point> expectedFirstCluster = {{1, 1}, {0.5, 0.5}, {1.5, 1.5}, {2, 2}, {1.5, 2}, {2, 1.5}, {0.5, 1},
            {1, 0.5}, {0.0, 0.5}, {1.5, 1}};
    std::vector<Point> actualFirstCluster = std::vector<Point>(clusters[0].begin(), clusters[0].end());
    ASSERT_EQ(actualFirstCluster, expectedFirstCluster);
    std::vector<Point> expectedSecondCluster = {{11, 11}, {10.5, 10.5}, {11.5, 11.5}, {12, 12}, {11.5, 12},
            {12, 11.5}, {10.5, 11}, {11, 10.5}, {10.0, 10.5}, {11.5, 11}};
    std::vector<Point> actualSecondCluster = std::vector<Point>(clusters[1].begin(), clusters[1].end());
    ASSERT_EQ(actualSecondCluster, expectedSecondCluster);
}


TEST_F(MeanShiftTest, oneCluster)
{
    std::vector<Cluster> clusters = meanShift(points, 10.0);
    ASSERT_EQ(clusters.size(), 1);
    std::vector<Point> actualCluster = std::vector<Point>(clusters[0].begin(), clusters[0].end());
    ASSERT_EQ(actualCluster, points);
}


TEST_F(MeanShiftTest, eachPointIsACluster)
{
    std::vector<Cluster> clusters = meanShift(points, 0.00001);
    ASSERT_EQ(clusters.size(), points.size());
    for (auto &cluster : clusters)
        ASSERT_EQ(cluster.getSse(), 0);
}


