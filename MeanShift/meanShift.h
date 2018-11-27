#ifndef MEANSHIFT_MEANSHIFT_H
#define MEANSHIFT_MEANSHIFT_H

#include <vector>
#include <string>

#include "Point.h"
#include "Cluster.h"


std::vector<Point> getPointsFromCsv(std::string fileName);


std::vector<Cluster> meanShift(std::vector<Point> points, double r, long long maxIterations);


#endif //MEANSHIFT_MEANSHIFT_H
