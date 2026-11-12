#include "geometry_utils.hpp"
#include <cmath>

namespace geometry {

bool pointOnSegment(Point p, Point a, Point b, double eps) {
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    double px = p.x - a.x;
    double py = p.y - a.y;
    double length = std::hypot(dx, dy);
    if (length <= eps) {
        return std::hypot(px, py) <= eps;
    }
    double cross = dx * py - dy * px;
    if (std::abs(cross) > eps * length) {
        return false;
    }
    double dot = px * dx + py * dy;
    return (dot >= -eps * length) && (dot <= length * length + eps * length);
}

namespace {

int orientation(Point a, Point b, Point p, double eps) {
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    double cross = dx * (p.y - a.y) - dy * (p.x - a.x);
    double tolerance = eps * std::hypot(dx, dy);
    if (cross > tolerance) {
        return 1;
    }
    if (cross < -tolerance) {
        return -1;
    }
    return 0;
}

}

bool segmentsIntersect(Point a, Point b, Point c, Point d, double eps) {
    int o1 = orientation(a, b, c, eps);
    int o2 = orientation(a, b, d, eps);
    int o3 = orientation(c, d, a, eps);
    int o4 = orientation(c, d, b, eps);
    if (((o1 == 0) && (pointOnSegment(c, a, b, eps))) ||
        ((o2 == 0) && (pointOnSegment(d, a, b, eps))) ||
        ((o3 == 0) && (pointOnSegment(a, c, d, eps))) ||
        ((o4 == 0) && (pointOnSegment(b, c, d, eps)))) {
        return true;
    }
    return (o1 * o2 < 0) && (o3 * o4 < 0);
}

double polygonArea(const std::vector<Point>& vertices) {
    double sum = 0.0;
    std::size_t n = vertices.size();
    for (std::size_t i = 0; i < n; ++i) {
        sum += vertices[i].x * vertices[(i + 1) % n].y - vertices[(i + 1) % n].x * vertices[i].y;
    }
    return std::abs(sum) / 2.0;
}

}