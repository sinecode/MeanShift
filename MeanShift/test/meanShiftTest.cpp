#include <gtest/gtest.h>
#include "../meanShift.h"


TEST(MeanShiftTest, TestPoint)
{
    Point point = {3.4, 5.6, 3.2};
    ASSERT_EQ(point.size(), 3);
}


TEST(MeanShiftTest, EmptyCsvTest)
{
    std::vector<Point> points = getPointsFromCsv("../../test/empty.csv");
    ASSERT_EQ(points.size(), 0);
}


TEST(MeanShiftTest, NotEmptyCsvTest)
{
    std::vector<Point> points = getPointsFromCsv("../../test/test.csv");
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
