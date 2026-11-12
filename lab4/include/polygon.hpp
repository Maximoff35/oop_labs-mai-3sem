#pragma once
#include "point.hpp"
#include <vector>
#include <cstddef>
#include <ostream>
#include <istream>

class Polygon {
protected:
    std::vector<Point> vertices_;
    explicit Polygon(std::size_t vertex_count);
public:
    static constexpr double EPS = 1e-6;
    virtual ~Polygon() = default;
    virtual double metric() const;
    virtual void print(std::ostream& out) const = 0;
    virtual void read(std::istream& in) = 0;
    Point center() const;
    bool containsPoint(Point point) const;
    operator double() const;
    bool operator==(const Polygon& other) const;
    virtual Polygon* clone() const = 0;
};

std::ostream& operator<<(std::ostream& out, const Polygon& polygon);
std::istream& operator>>(std::istream& in, Polygon& polygon);

