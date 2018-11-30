#include <iostream>
#include <string>
#include <omp.h>

#include "meanShift.h"


int main(int argc, char **argv)
{
    if (argc < 3) {
        std::cout << "Usage: meanshift csvfile bandwidth" << std::endl;
        return -1;
    }
    std::cout << "File: " << argv[1] << std::endl;
    std::vector<Point> points = getPointsFromCsv(argv[1]);
    std::cout << "Number of points: " << points.size() << std::endl;
    std::cout << "Number of dimensions: " << points[0].dimensions() << std::endl;
    double startTime = omp_get_wtime();
    std::vector<Cluster> clusters = meanShift(points, std::stol(argv[2], nullptr, 10));
    double elapsedTime = omp_get_wtime() - startTime;
    std::cout << "Number of clusters: " << clusters.size() << std::endl;
    std::cout << "Elapsed time: " << elapsedTime << " s" << std::endl;
    writeClustersToCsv(clusters);
    return 0;
}
