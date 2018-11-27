#include <algorithm>
#include <vector>

#include "Point.h"
#include "Cluster.h"
#include "ClustersBuilder.h"


ClustersBuilder::ClustersBuilder(const std::vector<Point> &originalPoints)
{
    this->originalPoints = originalPoints;
    shiftedPoints = originalPoints;
}

Point &ClustersBuilder::operator[](const long index)
{
    return shiftedPoints[index];
}

const Point &ClustersBuilder::operator[](const long index) const
{
    return shiftedPoints[index];
}

std::vector<Point>::iterator ClustersBuilder::begin() {
    return shiftedPoints.begin();
}

std::vector<Point>::iterator ClustersBuilder::end() {
    return shiftedPoints.end();
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