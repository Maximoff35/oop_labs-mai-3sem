#include "polygon.hpp"
#include "geometry_utils.hpp"
#include <stdexcept>
#include <cmath>

Polygon::Polygon(std::size_t vertex_count) 
    : vertices_(vertex_count) {
    if (vertex_count < 3) {
        throw std::invalid_argument("Polygon");
    }
}

Point Polygon::center() const {
    Point result;
    for (const Point& vertex : vertices_) {
        result.x += vertex.x;
        result.y += vertex.y;
    }
    result.x /= vertices_.size();
    result.y /= vertices_.size();
    return result;
}

Polygon::operator double() const {
    return metric();
}

bool Polygon::operator==(const Polygon& other) const {
    return std::abs(metric() - other.metric()) < EPS;
}

std::ostream& operator<<(std::ostream& out, const Polygon& polygon) {
    polygon.print(out);
    return out;
}

std::istream& operator>>(std::istream& in, Polygon& polygon) {
    polygon.read(in);
    return in;
}

bool Polygon::containsPoint(Point point) const {
    bool inside = false;
    std::size_t n = vertices_.size();
    for (std::size_t i = 0; i < n; ++i) {
        const Point& a = vertices_[i];
        const Point& b = vertices_[(i + 1) % n];
        if (geometry::pointOnSegment(point, a, b, Polygon::EPS)) {
            return true;
        }
        bool crosses = (a.y > point.y) != (b.y > point.y);
        if (crosses) {
            double x_intersection = a.x + (point.y - a.y) * (b.x - a.x) / (b.y - a.y);
            if (x_intersection > point.x) {
                inside = !inside;
            }
        }
    }
    return inside;
}

double Polygon::metric() const {
    return geometry::polygonArea(vertices_);
}