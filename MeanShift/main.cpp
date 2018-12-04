#include <iostream>
#include <string>
#include <chrono>

#include "Point.hpp"
#include "meanShift.hpp"


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
    double bandwidth = std::stod(argv[2]);

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    std::vector<Cluster> clusters = meanShift(points, bandwidth);

    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    double elapsedTime = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
    std::cout << "Number of clusters: " << clusters.size() << std::endl;
    std::cout << "Elapsed time: " << elapsedTime << " s" << std::endl;

    writeClustersToCsv(clusters);
    return 0;
}
