#pragma once
#include "polygon.hpp"


class Triangle : public Polygon {
public:
    Triangle();
    Triangle(Point a, Point b, Point c);
    void print(std::ostream& out) const override;
    void read(std::istream& in) override;
    bool isEquilateral() const;
    Polygon* clone() const override;
};