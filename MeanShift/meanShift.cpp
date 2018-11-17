#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>
#include <cassert>

#include "meanShift.h"


std::vector<Point> getPointsFromCsv(std::string fileName)
{
    std::vector<Point> points;

    std::ifstream data(fileName);
    std::string line;
    while (std::getline(data, line)) {
        std::stringstream lineStream(line);
        std::string cell;
        Point point;
        while (std::getline(lineStream, cell, ','))
            point.push_back(stod(cell));
        points.push_back(point);
    }

    return points;
}


double euclideanDistance(Point p1, Point p2)
{
    assert(p1.size() == p2.size());
    assert(p1.size() > 0 && p2.size() > 0);

    double sum = 0.0;
    for (int i = 0; i < p1.size(); ++i)
        sum += std::pow(p1[i] - p2[i], 2);
    return std::sqrt(sum);
}
