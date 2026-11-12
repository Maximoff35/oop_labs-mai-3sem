#pragma once
#include "polygon.hpp"

class Pentagon : public Polygon {
public:
    Pentagon();
    Pentagon(Point a, Point b, Point c, Point d, Point e);
    void print(std::ostream& out) const override;
    void read(std::istream& in) override;
    bool isRegular() const;
    Polygon* clone() const override;
};
