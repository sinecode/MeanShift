#include <utility>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>
#include <cassert>
#include <algorithm>

#include "meanShift.h"


std::vector<Point> getPointsFromCsv(std::string fileName)
{
    std::vector<Point> points;

    std::ifstream data(fileName);
    std::string line;
    while (std::getline(data, line)) {
        std::stringstream lineStream(line);
        std::string cell;
        Point point;
        while (std::getline(lineStream, cell, ','))
            point.push_back(stod(cell));
        points.push_back(point);
    }

    return points;
}


double euclideanDistance(Point p1, Point p2)
{
    assert(!p1.empty() || !p2.empty());
    assert(p1.size() == p2.size());

    double sum = 0.0;
    for (int i = 0; i < p1.size(); ++i)
        sum += std::pow(p1[i] - p2[i], 2);
    return std::sqrt(sum);
}


Point Cluster::getCentroid()
{
    return centroid;
}

void Cluster::addPoint(Point point)
{
    points.emplace_back(point);
}

long Cluster::getSize()
{
    return points.size();
}

std::vector<Point> Cluster::getPoints()
{
    return points;
}

double Cluster::getSse()
{
    double sum = 0.0;
    for (const Point &p : points)
        sum += std::pow(euclideanDistance(p, centroid), 2);
    return sum;
}


std::vector<Cluster> ClustersBuilder::buildClusters()
{
    std::vector<Cluster> clusters;

    for (int i = 0; i < shiftedPoints.size(); ++i) {
        Point centroid = shiftedPoints[i];
        auto it = std::find(clusters.begin(), clusters.end(), Cluster(centroid));
        if (it != clusters.end())
            it->addPoint(originalPoints[i]);
        else {
            Cluster cluster = Cluster(centroid);
            cluster.addPoint(originalPoints[i]);
            clusters.emplace_back(cluster);

        }
    }
    return clusters;
}


std::vector<Cluster> meanShift(std::vector<Point> points, double r, long maxIterations)
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
                if (euclideanDistance(points[i], points[h]) <= r)
                    neighbors.emplace_back(points[h]);
            }
            // calculate the new position of the point
            Point newPosition;
            for (long h = 0; h < points[0].size(); ++h) {
                double sum = 0;
                for (Point neighbor : neighbors)
                    sum += neighbor[h];
                newPosition.emplace_back(sum / neighbors.size());
            }
            if (builder[i] == newPosition) {
                stopShifting[i] = true;
                ++pointsCompleted;
            } else
                builder[i] = newPosition;
            ++j;
        }
    }
    return builder.buildClusters();
}

