#ifndef MEANSHIFT_MEANSHIFT_H
#define MEANSHIFT_MEANSHIFT_H

#include <vector>
#include <string>


typedef std::vector<double> Point;


std::vector<Point> getPointsFromCsv(std::string fileName);


double euclideanDistance(Point p1, Point p2);


class Cluster {
public:
    Cluster(Point centroid)
    {
        this->centroid = centroid;
    }

    Point getCentroid();

    void addPoint(Point point);

    double getSse();

private:
    std::vector<Point> points;
    Point centroid;
};


class ClustersBuilder {
public:
    ClustersBuilder(std::vector<Point> originalPoints)
    {
        this->originalPoints = originalPoints;
        shiftedPoints = originalPoints;
    }

    void shiftPoint(int index, Point newPosition);

    std::vector<Cluster> buildClusters();

private:
    std::vector<Point> originalPoints;
    std::vector<Point> shiftedPoints;
};


std::vector<Cluster> cluster(std::vector<Point> points);


#endif //MEANSHIFT_MEANSHIFT_H
