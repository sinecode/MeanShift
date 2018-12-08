#include <string>
#include <vector>
#include <cstring>
#include <sstream>
#include <fstream>

#include "Point.hpp"
#include "Cluster.hpp"
#include "csvUtils.hpp"


std::vector<Point> getPointsFromCsv(std::string fileName)
{
    std::vector<Point> points;

    std::ifstream data(fileName);
    std::string line;
    while (std::getline(data, line)) {
        std::stringstream lineStream(line);
        std::string cell;
        std::vector<float> point;
        while (std::getline(lineStream, cell, ','))
            point.push_back(stod(cell));
        points.emplace_back(Point(point));
    }

    return points;
}


void writeClustersToCsv(std::vector<Cluster> &clusters, std::string fileName)
{
    std::ofstream outputFile(fileName + ".csv");
    int clusterId = 0;
    for (auto &cluster : clusters) {
        for (auto &point : cluster) {
            for (auto &value : point) {
                outputFile << value << ",";
            }
            outputFile << clusterId << "\n";
        }
        ++clusterId;
    }
}

