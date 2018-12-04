#include <cassert>
#include <cmath>
#include <vector>
#include <initializer_list>

#include "Point.hpp"


Point::Point(std::vector<double> values)
{
    this->values = std::move(values);
}

Point::Point(std::initializer_list<double> values)
{
    this->values.assign(values);
}

bool Point::operator==(const Point &p) const
{
    return this->values == p.values;
}

bool Point::operator!=(const Point &p) const
{
    return this->values != p.values;
}

Point Point::operator+(const Point &p)
{
    Point point(this->values);
    return point += p;
}

Point &Point::operator+=(const Point &p)
{
    assert(p.dimensions() == dimensions());

    for (long i = 0; i < p.dimensions(); ++i)
        this->values[i] += p[i];
    return *this;
}

Point Point::operator-(const Point &p)
{
    Point point(this->values);
    return point -= p;
}

Point &Point::operator-=(const Point &p)
{
    assert(p.dimensions() == dimensions());

    for (long i = 0; i < p.dimensions(); ++i)
        this->values[i] -= p[i];
    return *this;
}

Point Point::operator*(const double d)
{
    Point point(this->values);
    return point *= d;
}

Point &Point::operator*=(const double d)
{
    for (long i = 0; i < dimensions(); ++i)
        this->values[i] *= d;
    return *this;
}

Point Point::operator/(const double d)
{
    Point point(this->values);
    return point /= d;
}

Point &Point::operator/=(const double d)
{
    for (long i = 0; i < dimensions(); ++i)
        this->values[i] /= d;
    return *this;
}

double &Point::operator[](const long index)
{
    return values[index];
}

const double &Point::operator[](const long index) const
{
    return values[index];
}

long Point::dimensions() const
{
    return values.size();
}

std::vector<double>::iterator Point::begin()
{
    return values.begin();
}

std::vector<double>::iterator Point::end()
{
    return values.end();
}

double Point::euclideanDistance(const Point &p) const
{
    assert(p.dimensions() == dimensions());

    double sum = 0.0;
    for (int i = 0; i < p.dimensions(); ++i)
        sum += std::pow(this->values[i] - p.values[i], 2);
    return std::sqrt(sum);
}

