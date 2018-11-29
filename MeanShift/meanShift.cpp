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


std::vector<Cluster> meanShift(std::vector<Point> points, double r, long long maxIterations)
{
    ClustersBuilder builder = ClustersBuilder(points);
    std::vector<bool> stopShifting(points.size(), false);
    long j = 0;
    long pointsCompleted = 0;
    while (pointsCompleted < points.size() && j < maxIterations) {
        for (long i = 0; i < points.size(); ++i) {
            if (stopShifting[i])
                continue;
            std::vector<Point> neighbors;
            for (auto &point : points) {
                if (builder[i].euclideanDistance(point) <= r)
                    neighbors.emplace_back(point);
            }
            // calculate the new position of the point
            std::vector<double> newpos;
            for (long h = 0; h < points[0].dimensions(); ++h) {
                double sum = 0;
                for (Point neighbor : neighbors)
                    sum += neighbor[h];
                newpos.emplace_back(sum / neighbors.size());
            }
            Point newPosition(newpos);
            if (builder[i] == newPosition) {
                stopShifting[i] = true;
                ++pointsCompleted;
            } else
                builder[i] = newPosition;
        }
        ++j;
    }
    if (j == maxIterations)
        std::cout << "WARNING: reached the maximum number of iterations" << std::endl;
    return builder.buildClusters();
}

