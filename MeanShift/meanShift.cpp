#include <vector>
#include <iostream>
#include <cmath>

#include "Point.hpp"
#include "Cluster.hpp"
#include "ClustersBuilder.hpp"
#include "meanShift.hpp"


std::vector<Cluster> meanShift(std::vector<Point> points, double bandwidth)
{
    ClustersBuilder builder = ClustersBuilder(points, 0.4);
    long j = 0;
    unsigned long dimensions = (unsigned) points[0].dimensions();
    double radius = bandwidth * 3;
    while (!builder.stopShiftingAll() && j < MAX_ITERATIONS) {

#pragma omp parallel for \
default(none) shared(j, points, dimensions, builder, bandwidth, radius) \
schedule(dynamic)

        for (long i = 0; i < points.size(); ++i) {
            if (builder.stopShifting(i))
                continue;

            Point newPosition(std::vector<double>(dimensions, 0));
            double totalWeight = 0.0;
            for (auto &point : points) {
                double distance = builder.getShiftedPoint(i).euclideanDistance(point);
                if (distance <= radius) {
                    double gaussian = std::exp(-(distance * distance) / (2 * bandwidth * bandwidth));
                    newPosition += point * gaussian;
                    totalWeight += gaussian;
                }
            }

            // the new position of the point is the weighted average of its neighbors
            newPosition /= totalWeight;
#pragma omp critical
            builder.shiftPoint(i, newPosition);
        }
        ++j;
    }
    if (j == MAX_ITERATIONS)
        std::cout << "WARNING: reached the maximum number of iterations" << std::endl;
    return builder.buildClusters();
}

