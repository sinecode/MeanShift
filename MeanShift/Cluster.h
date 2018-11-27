#ifndef MEANSHIFT_CLUSTER_H
#define MEANSHIFT_CLUSTER_H

#include <vector>

#include "Point.h"


class Cluster {
public:
    explicit Cluster(Point centroid);

    Point getCentroid() const;

    bool operator==(const Cluster &c) const;

    bool operator!=(const Cluster &c) const;

    void addPoint(Point point);

    long getSize() const;

    std::vector<Point>::iterator begin();

    std::vector<Point>::iterator end();

    double getSse() const;

private:
    std::vector<Point> points;
    Point centroid;
};


#endif //MEANSHIFT_CLUSTER_H
