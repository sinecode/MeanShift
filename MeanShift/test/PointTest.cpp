#include <gtest/gtest.h>

#include "../Point.hpp"


#define ABS_ERROR 0.0000000001


TEST(PointTest, equalOperatorTest) {
    Point p1{3, 4, 5};
    Point p2{3, 4, 5};
    ASSERT_EQ(p1, p2);

    p2 = {5, 4, 3};
    ASSERT_NE(p1, p2);
}


TEST(PointTest, plusOperatorTest) {
    Point p1{2, 3, 4};
    Point p2{1, 2, 1};
    Point expected{3, 5, 5};
    ASSERT_EQ(p1 + p2, expected);

    p1 += p2;
    ASSERT_EQ(p1, expected);
}


TEST(PointTest, minusOperatorTest) {
    Point p1{2, 3, 4};
    Point p2{1, 2, 1};
    Point expected{1, 1, 3};
    ASSERT_EQ(p1 - p2, expected);

    p1 -= p2;
    ASSERT_EQ(p1, expected);
}


TEST(PointTest, productOperatorTest) {
    Point point{2, 3, 4};
    double d = 3;
    Point expected{6, 9, 12};
    ASSERT_EQ(point * d, expected);

    point *= d;
    ASSERT_EQ(point, expected);
}


TEST(PointTest, divisionOperatorTest) {
    Point point{3, 6, 12};
    double d = 3;
    Point expected{1, 2, 4};
    ASSERT_EQ(point / d, expected);

    point /= d;
    ASSERT_EQ(point, expected);
}


TEST(PointTest, subscriptOperatorTest) {
    Point p{2, 3, 4};
    ASSERT_EQ(p[0], 2);
    ASSERT_EQ(p[1], 3);
    ASSERT_EQ(p[2], 4);

    p[1] = 100;
    ASSERT_EQ(p[0], 2);
    ASSERT_EQ(p[1], 100);
    ASSERT_EQ(p[2], 4);
}


TEST(PointTest, dimensionsTest) {
    Point point{3.4, 5.6, 3.2};
    ASSERT_EQ(point.dimensions(), 3);
}


TEST(PointTest, iteratorTest) {
    Point point{5, 5, 5};
    for (auto value : point)
        ASSERT_EQ(value, 5);
}


TEST(PointTest, euclideanDistanceTest) {
    Point p{0, 0};
    ASSERT_NEAR(p.euclideanDistance({0, 0}), 0, ABS_ERROR);

    p = {8, 6};
    ASSERT_NEAR(p.euclideanDistance({5, 2}), 5, ABS_ERROR);

    p = {2, 2, 20};
    ASSERT_NEAR(p.euclideanDistance({2, 2, 50}), 30, ABS_ERROR);

    Point p1{3, 5, 6};
    Point p2{5, 43, 33};
    ASSERT_NEAR(p1.euclideanDistance(p2), p2.euclideanDistance(p1), ABS_ERROR);
}

