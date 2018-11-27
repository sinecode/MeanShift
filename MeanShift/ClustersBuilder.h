#ifndef MEANSHIFT_CLUSTERBUILDER_H
#define MEANSHIFT_CLUSTERBUILDER_H

#include <vector>

#include "Point.h"
#include "Cluster.h"

class ClustersBuilder {
public:
    explicit ClustersBuilder(const std::vector<Point> &originalPoints);

    Point &operator[](long index);

    const Point &operator[](long index) const;

    std::vector<Point>::iterator begin();

    std::vector<Point>::iterator end();

    std::vector<Cluster> buildClusters();

private:
    std::vector<Point> originalPoints;
    std::vector<Point> shiftedPoints;
};


#endif //MEANSHIFT_CLUSTERBUILDER_H
