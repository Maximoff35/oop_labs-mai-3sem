#include "square.hpp"
#include <vector>
#include <array>
#include <cmath>
#include <stdexcept>
#include <sstream>
#include <string>
#include <iomanip>
#include <limits>

namespace {

bool isValidSquare(const std::vector<Point>& vertices) {
    if (vertices.size() != 4) {
        return false;
    }
    std::array<double, 4> sides;
    for (std::size_t i = 0; i < 4; ++i) {
        const Point& a = vertices[i];
        const Point& b = vertices[(i + 1) % 4];
        if ((!std::isfinite(a.x)) || (!std::isfinite(a.y))) {
            return false;
        }
        sides[i] = std::hypot(b.x - a.x, b.y - a.y);
        if ((!std::isfinite(sides[i])) || (sides[i] <= Polygon::EPS)) {
            return false;
        }
    }

    for (std::size_t i = 0; i < 4; ++i) {
        if (std::abs(sides[i] - sides[0]) >= Polygon::EPS) {
            return false;
        }
        const Point& a = vertices[i];
        const Point& b = vertices[(i + 1) % 4];
        const Point& c = vertices[(i + 2) % 4];
        double ux = (b.x - a.x) / sides[i];
        double uy = (b.y - a.y) / sides[i];
        double vx = (c.x - b.x) / sides[(i + 1) % 4];
        double vy = (c.y - b.y) / sides[(i + 1) % 4];
        double dot = ux * vx + uy * vy;
        if ((!std::isfinite(dot)) || (std::abs(dot) >= Polygon::EPS)) {
            return false;
        }
    }
    return true;
}

}

Square::Square() 
    : Polygon(4) {
    vertices_[0] = {0, 0};
    vertices_[1] = {1, 0};
    vertices_[2] = {1, 1};
    vertices_[3] = {0, 1};
}

Square::Square(Point a, Point b, Point c, Point d) 
    : Polygon(4) {
    vertices_[0] = a;
    vertices_[1] = b;
    vertices_[2] = c;
    vertices_[3] = d;
    if (!isValidSquare(vertices_)) {
        throw std::invalid_argument("Invalid square");
    }
}

void Square::print(std::ostream& out) const {
    auto old_precision = out.precision();
    out << std::setprecision(std::numeric_limits<double>::max_digits10);
    out << "Square ";
    for (const Point& vertex: vertices_) {
        out << vertex.x << ' ' << vertex.y << ' ';
    }
    Point c = center();
    out << "Center " << c.x << ' ' << c.y << ' ';
    out << "Area " << metric();
    out.precision(old_precision);
}

void Square::read(std::istream& in) {
    std::string line;
    if (!std::getline(in >> std::ws, line)) {
        return;
    }
    std::istringstream data(line);
    std::string name;
    if (!(data >> name) || (name != "Square")) {
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
    if (!isValidSquare(new_vertices)) {
        in.setstate(std::ios::failbit);
        return;
    }
    vertices_ = new_vertices;
}

double Square::side() const {
    return std::hypot(vertices_[0].x - vertices_[1].x, vertices_[0].y - vertices_[1].y);
}

Polygon* Square::clone() const {
    return new Square(*this);
}