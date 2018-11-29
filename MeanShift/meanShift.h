#ifndef MEANSHIFT_MEANSHIFT_H
#define MEANSHIFT_MEANSHIFT_H

#include <vector>
#include <string>

#include "Point.h"
#include "Cluster.h"


#define MAX_IT 100000000000


std::vector<Point> getPointsFromCsv(std::string fileName);


void writeClustersToCsv(std::vector<Cluster> &clusters);


std::vector<Cluster> meanShift(std::vector<Point> points, double r, long long maxIterations = MAX_IT);


#endif //MEANSHIFT_MEANSHIFT_H
