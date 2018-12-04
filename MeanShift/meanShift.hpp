#ifndef MEANSHIFT_MEANSHIFT_H
#define MEANSHIFT_MEANSHIFT_H

#include <vector>
#include <string>

#include "Point.hpp"
#include "Cluster.hpp"


#define MAX_ITERATIONS 10000


std::vector<Point> getPointsFromCsv(std::string fileName);


void writeClustersToCsv(std::vector<Cluster> &clusters);


std::vector<Cluster> meanShift(std::vector<Point> points, double bandwidth, int num_threads = 1);


#endif //MEANSHIFT_MEANSHIFT_H
