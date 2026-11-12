#pragma once
#include "polygon.hpp"

class Square : public Polygon {
public:
    Square();
    Square(Point a, Point b, Point c, Point d);
    void print(std::ostream& out) const override;
    void read(std::istream& in) override;
    double side() const;
    Polygon* clone() const override;
};