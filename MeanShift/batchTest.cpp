#include <iostream>
#include <string>
#include <chrono>
#include <fstream>

#include "Point.hpp"
#include "Cluster.hpp"
#include "meanShift.hpp"


int main(int argc, char **argv)
{
    if (argc < 3 || argc % 2 == 1) {
        std::cout << "Usage: batchtest numthreads csvfile bandwidth [csvfile bandwith ...]" << std::endl;
        return -1;
    }

    double totalElapsedTime = 0.0;
    int num_threads = std::stoi(argv[1]);

    for (int i = 2; i < argc; i += 2) {
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "File: " << argv[i] << std::endl;
        std::vector<Point> points = getPointsFromCsv(argv[i]);
        std::cout << "Number of points: " << points.size() << std::endl;
        std::cout << "Number of dimensions: " << points[0].dimensions() << std::endl;
        double bandwidth = std::stod(argv[i + 1]);

        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

        std::vector<Cluster> clusters = meanShift(points, bandwidth, num_threads);

        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        double elapsedTime = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

        totalElapsedTime += elapsedTime;

        std::cout << "Number of clusters: " << clusters.size() << std::endl;
        std::cout << "Elapsed time: " << elapsedTime << " s" << std::endl;
    }
    std::cout << "===================================================" << std::endl;
    std::cout << "Clustering operations performed: " << (argc - 1) / 2 << std::endl;
    std::cout << "Total elapsed time: " << totalElapsedTime << " s" << std::endl;
    return 0;
}

