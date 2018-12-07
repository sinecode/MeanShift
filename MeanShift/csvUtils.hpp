#ifndef MEANSHIFT_CSVUTILS_HPP
#define MEANSHIFT_CSVUTILS_HPP

#include <vector>
#include <string>

#include "Point.hpp"
#include "Cluster.hpp"

std::vector<Point> getPointsFromCsv(std::string fileName);

void writeClustersToCsv(std::vector<Cluster> &clusters, std::string fileName);


#endif //MEANSHIFT_CSVUTILS_HPP
