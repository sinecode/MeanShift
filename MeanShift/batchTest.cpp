#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <fstream>

#include "meanShift.h"


#define SEQUENTIAL_TIME 104


int main(int argc, char **argv)
{
    if (argc < 3 || argc % 2 == 0) {
        std::cout << "Usage: batchtest csvfile bandwidth [csvfile bandwith ...]" << std::endl;
        return -1;
    }

    // create log file with name "date time.log"
    std::time_t now = std::time(nullptr);
    std::tm *currentTime = std::localtime(&now);
    char buffer[50];
    std::strftime(buffer, 50, "%c", currentTime);
    std::string logFileName(buffer);
    std::ofstream logFile(logFileName + ".log");

    double totalElapsedTime = 0.0;

    for (int i = 1; i < argc; i += 2) {
        logFile << "---------------------------------------------------" << std::endl;
        logFile << "File: " << argv[i] << std::endl;
        std::vector<Point> points = getPointsFromCsv(argv[i]);
        logFile << "Number of points: " << points.size() << std::endl;
        logFile << "Number of dimensions: " << points[0].dimensions() << std::endl;

        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

        std::vector<Cluster> clusters = meanShift(points, std::stol(argv[i + 1], nullptr, 10));

        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        double elapsedTime = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

        totalElapsedTime += elapsedTime;

        logFile << "Number of clusters: " << clusters.size() << std::endl;
        logFile << "Elapsed time: " << elapsedTime << " s" << std::endl;
    }
    logFile << "===================================================" << std::endl;
    logFile << "Clustering operations performed: " << (argc - 1) / 2 << std::endl;
    logFile << "Total elapsed time: " << totalElapsedTime << "s" << std::endl;
#ifdef _OPENMP
    logFile << "Speedup: " << SEQUENTIAL_TIME / totalElapsedTime << std::endl;
#endif
    return 0;
}

