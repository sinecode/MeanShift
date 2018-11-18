#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>
#include <cassert>

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
    assert(p1.size() == p2.size());
    assert(p1.size() > 0 && p2.size() > 0);

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
    points.push_back(point);
}

double Cluster::getSse()
{
    double sum = 0.0;
    for (Point p : points)
        sum += std::pow(euclideanDistance(p, centroid), 2);
    return sum;
}


void ClustersBuilder::shiftPoint(int index, Point newPosition)
{
    shiftedPoints[index] = newPosition;
}

std::vector<Cluster> ClustersBuilder::buildClusters()
{
    std::vector<Cluster> clusters;

    for (int i = 0; i < shiftedPoints.size(); ++i) {
        Point centroid = shiftedPoints[i];
        bool found = false;
        int j = 0;
        while (!found && j < clusters.size()) {
            if (clusters[j].getCentroid() == centroid)
                found = true;
            else
                ++j;
        }
        if (found)
            clusters[j].addPoint(originalPoints[i]);
        else
            clusters.push_back(Cluster(centroid));
    }
    return clusters;
}

