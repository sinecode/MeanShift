#ifndef MEANSHIFT_POINT_H
#define MEANSHIFT_POINT_H

#include <vector>
#include <initializer_list>

class Point {

public:
    explicit Point(std::vector<double> values);

    Point(std::initializer_list<double> values);

    Point() = default;

    bool operator==(const Point &p) const;

    bool operator!=(const Point &p) const;

    Point operator+(const Point &p);

    Point &operator+=(const Point &p);

    Point operator-(const Point &p);

    Point &operator-=(const Point &p);

    Point operator*(double d);

    Point &operator*=(double d);

    Point operator/(double d);

    Point &operator/=(double d);

    double &operator[](long index);

    const double &operator[](long index) const;

    long dimensions() const;

    std::vector<double>::iterator begin();

    std::vector<double>::iterator end();

    double euclideanDistance(const Point &p) const;

private:
    std::vector<double> values;
};

#endif //MEANSHIFT_POINT_H
