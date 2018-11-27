#ifndef MEANSHIFT_POINT_H
#define MEANSHIFT_POINT_H

#include <vector>
#include <initializer_list>

class Point {

public:
    explicit Point(std::vector<double> values);

    Point(std::initializer_list<double> values);

    Point() = default;

    double &operator[](long index);

    const double &operator[](long index) const;

    bool operator==(const Point &p) const;

    bool operator!=(const Point &p) const;

    long dimensions() const;

    std::vector<double>::iterator begin();

    std::vector<double>::iterator end();

    double euclideanDistance(const Point &p) const;

private:
    std::vector<double> values;
};

#endif //MEANSHIFT_POINT_H
