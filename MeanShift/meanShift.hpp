#ifndef MEANSHIFT_MEANSHIFT_HPP
#define MEANSHIFT_MEANSHIFT_HPP

#include <vector>

#include "Point.hpp"
#include "Cluster.hpp"


#define MAX_ITERATIONS 1000


std::vector<Cluster> meanShift(std::vector<Point> points, float bandwidth);


#endif //MEANSHIFT_MEANSHIFT_HPP
