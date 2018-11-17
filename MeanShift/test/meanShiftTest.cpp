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
    double expectedPoints[3][2] = {{1.1, 1.2},
                                   {2.1, 2.2},
                                   {3.1, 3.2}};
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

    ASSERT_EQ(euclideanDistance({0, 0}, {0, 0}), 0);
    ASSERT_EQ(euclideanDistance({8, 6}, {5, 2}), 5);
    ASSERT_EQ(euclideanDistance({2, 2, 20}, {2, 2, 50}), 30);
}
