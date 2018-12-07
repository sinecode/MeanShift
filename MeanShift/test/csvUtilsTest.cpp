#include <gtest/gtest.h>
#include <fstream>
#include <string>

#include "../Point.hpp"
#include "../csvUtils.hpp"


TEST(csvUtilsTest, getPointsFromEmptyCsv)
{
    std::vector<Point> points = getPointsFromCsv("../../test/resources/empty.csv");
    ASSERT_EQ(points.size(), 0);
}


TEST(csvUtilsTest, getPointsFromNotEmptyCsv)
{
    std::vector<Point> points = getPointsFromCsv("../../test/resources/test.csv");
    ASSERT_EQ(points, std::vector<Point>({{1.1, 1.2}, {2.1, 2.2}, {3.1, 3.2}}));
}


TEST(csvUtilsTest, writeClustersToCsv)
{
    // build two clusters with two points each
    Cluster c1({1, 2});
    c1.addPoint({1, 2});
    c1.addPoint({2, 2});
    Cluster c2({5, 6});
    c2.addPoint({5, 6});
    c2.addPoint({6, 6});
    std::vector<Cluster> clusters{c1, c2};
    writeClustersToCsv(clusters, "../../test/resources/out");

    std::string expectedFileContent = "1,2,0\n2,2,0\n5,6,1\n6,6,1\n";
    std::ifstream ifs("../../test/resources/out.csv");
    std::string actualFileContent((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    EXPECT_EQ(expectedFileContent, actualFileContent);
}
