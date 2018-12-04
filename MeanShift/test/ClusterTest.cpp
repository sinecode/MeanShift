#include <gtest/gtest.h>

#include "../Cluster.hpp"
#include "../Point.hpp"


#define ABS_ERROR 0.00000000001


TEST(ClusterTest, centroidTest)
{
    Point expectedCentroid{1, 1};
    Cluster cluster = Cluster(expectedCentroid);
    ASSERT_EQ(cluster.getCentroid(), expectedCentroid);
}


TEST(ClusterTest, equalityTest)
{
    Cluster c1({1, 1});
    Cluster c2({0.999999, 1.111111});
    ASSERT_EQ(c1, c2);

    c2 = Cluster({0, 1});
    ASSERT_NE(c1, c2);
}


TEST(ClusterTest, sizeTest)
{
    Cluster cluster = Cluster({1, 1});
    std::vector<Point> points = {{0, 0}, {1, 1}, {2, 2}};
    for (auto &p : points)
        cluster.addPoint(p);
    ASSERT_EQ(cluster.getSize(), 3);
}


TEST(ClusterTest, iteratorTest)
{
    Cluster cluster = Cluster(Point({1, 1}));
    std::vector<Point> points = {Point({5, 5}), Point({5, 5}), Point({5, 5})};
    for (auto &p : points)
        cluster.addPoint(p);

    for (auto &p : cluster)
        ASSERT_EQ(p, Point({5, 5}));
}


TEST(ClusterTest, sseTest)
{
    std::vector<Point> points = {Point({0, 0}), Point({1, 1}), Point({2, 2})};
    Cluster cluster = Cluster(Point({1, 1}));
    for (auto &p : points)
        cluster.addPoint(p);

    ASSERT_NEAR(cluster.getSse(), 4, ABS_ERROR);
}