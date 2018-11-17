#ifndef MEANSHIFT_MEANSHIFT_H
#define MEANSHIFT_MEANSHIFT_H

#include <vector>
#include <string>


typedef std::vector<double> Point;


std::vector<Point> getPointsFromCsv(std::string fileName);


double euclideanDistance(Point p1, Point p2);


#endif //MEANSHIFT_MEANSHIFT_H
