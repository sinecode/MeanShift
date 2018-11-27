#include <iostream>

#include "meanShift.h"


int main(int argc, char **argv)
{
    std::vector<Point> points = getPointsFromCsv(argv[1]);
    std::cout << "Number of points: " << points.size() << std::endl;
    std::cout << "Number of dimensions: " << points[0].dimensions() << std::endl;
    std::vector<Cluster> clusters = meanShift(points, 30, 10000000000000);
    std::cout << "Number of cluster: " << clusters.size() << std::endl;
    return 0;
}
