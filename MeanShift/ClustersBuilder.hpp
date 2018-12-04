#ifndef MEANSHIFT_CLUSTERBUILDER_H
#define MEANSHIFT_CLUSTERBUILDER_H

#include <vector>

#include "Point.hpp"
#include "Cluster.hpp"

class ClustersBuilder {
public:
    explicit ClustersBuilder(const std::vector<Point> &originalPoints);

    Point &getShiftedPoint(long index);

    void shiftPoint(long index, const Point &newPosition);

    std::vector<Point>::iterator begin();

    std::vector<Point>::iterator end();

    std::vector<Cluster> buildClusters();

private:
    std::vector<Point> originalPoints;
    std::vector<Point> shiftedPoints;
    double clusterEps;
};


#endif //MEANSHIFT_CLUSTERBUILDER_H
