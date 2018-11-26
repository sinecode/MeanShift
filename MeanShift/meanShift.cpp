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

double Cluster::getSse()
{
    double sum = 0.0;
    for (const Point &p : points)
        sum += std::pow(euclideanDistance(p, centroid), 2);
    return sum;
}


void ClustersBuilder::shiftPoint(int index, Point newPosition)
{
    shiftedPoints[index] = std::move(newPosition);
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

