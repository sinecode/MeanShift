#include <iostream>
#include <string>

#include "meanShift.h"


int main(int argc, char **argv)
{
    if (argc < 3) {
        std::cout << "Usage: meanshift csvfile bandwidth" << std::endl;
        return -1;
    }
    std::vector<Point> points = getPointsFromCsv(argv[1]);
    std::vector<Cluster> clusters = meanShift(points, std::stol(argv[2], nullptr, 10));
    writeClustersToCsv(clusters);
    return 0;
}
