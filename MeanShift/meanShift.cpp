#include <utility>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
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


std::vector<Cluster> meanShift(std::vector<Point> points, double bandwidth, int num_threads)
{
    ClustersBuilder builder = ClustersBuilder(points);
    // vector of booleans such that the element in position i is true if the i-th point
    // has stopped to shift
    std::vector<bool> stopShifting(points.size(), false);
    long j = 0;
    long pointsCompleted = 0;
    long dimensions = points[0].dimensions();
    double radius = bandwidth * 3;
    while (pointsCompleted < points.size() && j < MAX_ITERATIONS) {
#pragma omp parallel for default(none) \
shared(j, pointsCompleted, dimensions, points, stopShifting, builder, bandwidth, radius) \
num_threads(num_threads)
        for (long i = 0; i < points.size(); ++i) {
            if (stopShifting[i])
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

            if (builder.getShiftedPoint(i).euclideanDistance(newPosition) < CLUSTER_EPS / 10) {
                stopShifting[i] = true;
#pragma omp atomic
                ++pointsCompleted;
            } else
                builder.shiftPoint(i, newPosition);
        }
#pragma omp atomic
        ++j;
    }
    if (j == MAX_ITERATIONS)
        std::cout << "WARNING: reached the maximum number of iterations" << std::endl;
    return builder.buildClusters();
}

