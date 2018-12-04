#include <algorithm>
#include <vector>

#include "Point.hpp"
#include "Cluster.hpp"
#include "ClustersBuilder.hpp"


ClustersBuilder::ClustersBuilder(const std::vector<Point> &originalPoints)
{
    this->clusterEps = clusterEps;
    this->originalPoints = originalPoints;
    shiftedPoints = originalPoints;
}

Point &ClustersBuilder::getShiftedPoint(long index)
{
    return shiftedPoints[index];
}

void ClustersBuilder::shiftPoint(const long index, const Point &newPosition)
{
    shiftedPoints[index] = newPosition;
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