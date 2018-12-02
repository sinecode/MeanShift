#include <utility>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>

#include "Point.h"
#include "Cluster.h"
#include "ClustersBuilder.h"
#include "meanShift.h"


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


std::vector<Cluster> meanShift(std::vector<Point> points, double bandWidth, long long maxIterations)
{
    ClustersBuilder builder = ClustersBuilder(points);
    // vector of booleans such that the element in position i is true if the i-th point
    // has stopped to shift
    std::vector<bool> stopShifting(points.size(), false);
    long j = 0;
    long pointsCompleted = 0;
    long dimensions = points[0].dimensions();
    while (pointsCompleted < points.size() && j < maxIterations) {
#pragma omp parallel for default(none) \
shared(j, pointsCompleted, dimensions, points, stopShifting, builder, bandWidth)
        for (long i = 0; i < points.size(); ++i) {
            if (stopShifting[i])
                continue;

            Point newPosition(std::vector<double>(dimensions, 0));
            long neighbors = 0;
            for (auto &point : points) {
                if (builder[i].euclideanDistance(point) <= bandWidth) {
                    newPosition += point;
                    ++neighbors;
                }
            }

            // the new position of the point is the average of its neighbors
            newPosition /= neighbors;
            if (builder[i] == newPosition) {
                stopShifting[i] = true;
#pragma omp atomic
                ++pointsCompleted;
            } else
                builder[i] = newPosition;
        }
#pragma omp atomic
        ++j;
    }
    if (j == maxIterations)
        std::cout << "WARNING: reached the maximum number of iterations" << std::endl;
    return builder.buildClusters();
}

