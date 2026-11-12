#include "triangle.hpp"
#include <cstddef>
#include <cmath>
#include <vector>
#include <sstream>
#include <string>
#include <iomanip>
#include <limits>
#include <stdexcept>

namespace {

bool isValidTriangle(const std::vector<Point>& vertices) {
    if (vertices.size() != 3) {
        return false;
    }
    for (const Point& p : vertices) {
        if ((!std::isfinite(p.x)) || (!std::isfinite(p.y))) {
            return false;
        }
    }
    const Point& a = vertices[0];
    const Point& b = vertices[1];
    const Point& c = vertices[2];
    double cross = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (!std::isfinite(cross)) {
        return false;
    }
    return std::abs(cross) / 2.0 > Polygon::EPS;
}
    
}

Triangle::Triangle() 
    : Polygon(3) {
    vertices_[0] = {0, 0};
    vertices_[1] = {1, 0};
    vertices_[2] = {0, 1};
}

Triangle::Triangle(Point a, Point b, Point c) 
    : Polygon(3) {
    vertices_[0] = a;
    vertices_[1] = b;
    vertices_[2] = c;
    if (!isValidTriangle(vertices_)) {
        throw std::invalid_argument("Invalid triangle");
    }
}

bool Triangle::isEquilateral() const {
    std::size_t n = vertices_.size();
    std::vector<double> sides(n);
    for (std::size_t i = 0; i < n; ++i) {
        sides[i] = std::hypot(vertices_[(i + 1) % n].x - vertices_[i].x, vertices_[(i + 1) % n].y - vertices_[i].y);
    }
    if (sides[0] <= EPS) {
        return false;
    }
    for (std::size_t i = 0; i < n; ++i) {
        if (std::abs(sides[i] - sides[(i + 1) % n]) >= EPS) {
            return false;
        }
    }
    return true;
}

void Triangle::print(std::ostream& out) const {
    auto old_precision = out.precision();
    out << std::setprecision(std::numeric_limits<double>::max_digits10);
    out << "Triangle ";
    for (const Point& vertex: vertices_) {
        out << vertex.x << ' ' << vertex.y << ' ';
    }
    Point c = center();
    out << "Center " << c.x << ' ' << c.y << ' ';
    out << "Area " << metric();
    out.precision(old_precision);
}

void Triangle::read(std::istream& in) {
    std::string line;
    if (!std::getline(in >> std::ws, line)) {
        return;
    }
    std::istringstream data(line);
    std::string name;
    if (!(data >> name) || (name != "Triangle")) {
        in.setstate(std::ios::failbit);
        return;
    }
    std::size_t n = vertices_.size();
    std::vector<Point> new_vertices(n);
    for (std::size_t i = 0; i < n; ++i) {
        if (!(data >> new_vertices[i].x >> new_vertices[i].y)) {
            in.setstate(std::ios::failbit);
            return;
        }
    }
    if (!isValidTriangle(new_vertices)) {
        in.setstate(std::ios::failbit);
        return;
    }
    vertices_ = new_vertices;
}

Polygon* Triangle::clone() const {
    return new Triangle(*this);
}