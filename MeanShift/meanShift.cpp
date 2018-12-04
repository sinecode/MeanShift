#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <cmath>

#include "Point.hpp"
#include "Cluster.hpp"
#include "ClustersBuilder.hpp"
#include "meanShift.hpp"


std::vector<Point> getPointsFromCsv(std::string fileName)
{
    std::vector<Point> points;

    std::ifstream data(fileName);
    std::string line;
    while (std::getline(data, line)) {
        std::stringstream lineStream(line);
        std::string cell;
        std::vector<double> point;
        while (std::getline(lineStream, cell, ','))
            point.push_back(stod(cell));
        points.emplace_back(Point(point));
    }

    return points;
}


void writeClustersToCsv(std::vector<Cluster> &clusters)
{
    std::ofstream outputFile("out.csv");
    int clusterId = 0;
    for (auto &cluster : clusters) {
        for (auto &point : cluster) {
            for (auto &value : point) {
                outputFile << value << ",";
            }
            outputFile << clusterId << "\n";
        }
        ++clusterId;
    }
}


std::vector<Cluster> meanShift(std::vector<Point> points, double bandwidth, int threads)
{
    ClustersBuilder builder = ClustersBuilder(points, 0.4);
    long j = 0;
    long dimensions = points[0].dimensions();
    double radius = bandwidth * 3;
    while (!builder.stopShiftingAll() && j < MAX_ITERATIONS) {
#pragma omp parallel for default(none) shared(j, points, dimensions, builder, bandwidth, radius) num_threads(threads)
        for (long i = 0; i < points.size(); ++i) {
            if (builder.stopShifting(i))
                continue;

            Point newPosition(std::vector<double>(dimensions, 0));
            double totalWeight = 0.0;
            for (auto &point : points) {
                double distance = builder.getShiftedPoint(i).euclideanDistance(point);
                if (distance <= radius) {
                    double gaussian = std::exp(-(distance * distance) / (2 * bandwidth * bandwidth));
                    newPosition += point * gaussian;
                    totalWeight += gaussian;
                }
            }

            // the new position of the point is the weighted average of its neighbors
            newPosition /= totalWeight;
#pragma omp critical
            builder.shiftPoint(i, newPosition);
        }
        ++j;
    }
    if (j == MAX_ITERATIONS)
        std::cout << "WARNING: reached the maximum number of iterations" << std::endl;
    return builder.buildClusters();
}

