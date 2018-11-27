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
            for (long h = 0; h < points.size(); ++h) {
                if (builder[i].euclideanDistance(points[h]) <= r)
                    neighbors.emplace_back(points[h]);
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
    return builder.buildClusters();
}

