#ifndef MEANSHIFT_MEANSHIFT_H
#define MEANSHIFT_MEANSHIFT_H

#include <utility>
#include <vector>
#include <string>


typedef std::vector<double> Point;


std::vector<Point> getPointsFromCsv(std::string fileName);


double euclideanDistance(Point p1, Point p2);


class Cluster {
public:
    explicit Cluster(Point centroid)
    {
        this->centroid = std::move(centroid);
    }

    Point getCentroid();

    bool operator==(const Cluster &c2) const
    {
        return this->centroid == c2.centroid;
    }

    void addPoint(Point point);

    long getSize();

    std::vector<Point> getPoints();

    double getSse();

private:
    std::vector<Point> points;
    Point centroid;
};


class ClustersBuilder {
public:
    explicit ClustersBuilder(const std::vector<Point> &originalPoints)
    {
        this->originalPoints = originalPoints;
        shiftedPoints = originalPoints;
    }

    Point &operator[](const long index)
    {
        return shiftedPoints[index];
    }

    const Point &operator[](const long index) const
    {
        return shiftedPoints[index];
    }

    std::vector<Cluster> buildClusters();

private:
    std::vector<Point> originalPoints;
    std::vector<Point> shiftedPoints;
};


std::vector<Cluster> meanShift(std::vector<Point> points, double r, long maxIterations);


#endif //MEANSHIFT_MEANSHIFT_H
