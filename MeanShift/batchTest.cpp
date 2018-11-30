#include <iostream>
#include <string>
#include <omp.h>

#include "meanShift.h"


int main(int argc, char **argv)
{
    if (argc < 3 || argc % 2 == 0) {
        std::cout << "Usage: batchtest csvfile bandwidth [csvfile bandwith ...]" << std::endl;
        return -1;
    }
    double totalElapsedTime = 0.0;
    for (int i = 1; i < argc; i += 2) {
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "File: " << argv[i] << std::endl;
        std::vector<Point> points = getPointsFromCsv(argv[i]);
        std::cout << "Number of points: " << points.size() << std::endl;
        std::cout << "Number of dimensions: " << points[0].dimensions() << std::endl;
        double startTime = omp_get_wtime();
        std::vector<Cluster> clusters = meanShift(points, std::stol(argv[i+1], nullptr, 10));
        double elapsedTime = omp_get_wtime() - startTime;
        totalElapsedTime += elapsedTime;
        std::cout << "Number of clusters: " << clusters.size() << std::endl;
        std::cout << "Elapsed time: " << elapsedTime << " s" << std::endl;
    }
    std::cout << "===================================================" << std::endl;
    std::cout << "Clustering operations performed: " << (argc-1)/2 << std::endl;
    std::cout << "Total elapsed time: " << totalElapsedTime << "s" << std::endl;
    return 0;
}

