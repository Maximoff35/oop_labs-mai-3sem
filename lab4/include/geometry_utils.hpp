#pragma once
#include "point.hpp"
#include <vector>

namespace geometry {

bool pointOnSegment(Point p, Point a, Point b, double eps);
bool segmentsIntersect(Point a, Point b, Point c, Point d, double eps);
double polygonArea(const std::vector<Point>& vertices);

}