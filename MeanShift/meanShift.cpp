#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

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
