#include "pentagon.hpp"
#include "geometry_utils.hpp"
#include <vector>
#include <cmath>
#include <stdexcept>
#include <array>
#include <sstream>
#include <string>
#include <iomanip>
#include <limits>

namespace {

bool isValidPentagon(const std::vector<Point>& vertices) {
    constexpr std::size_t n = 5;
    if (vertices.size() != n) {
        return false;
    }
    std::array<double, 5> sides;
    for (std::size_t i = 0; i < n; ++i) {
        const Point& a = vertices[i];
        const Point& b = vertices[(i + 1) % n];
        if ((!std::isfinite(a.x)) || (!std::isfinite(a.y))) {
            return false;
        }
        sides[i] = std::hypot(b.x - a.x, b.y - a.y);
        if ((!std::isfinite(sides[i])) || (sides[i] <= Polygon::EPS)) {
            return false;
        }
    }
    double area = geometry::polygonArea(vertices);
    if ((!std::isfinite(area)) || (area <= Polygon::EPS)) {
        return false;
    }
    for (std::size_t i = 0; i < n; ++i) {
        const Point& a = vertices[i];
        const Point& b = vertices[(i + 1) % n];
        const Point& c = vertices[(i + 2) % n];
        double ux = (b.x - a.x) / sides[i];
        double uy = (b.y - a.y) / sides[i];
        double vx = (c.x - b.x) / sides[(i + 1) % n];
        double vy = (c.y - b.y) / sides[(i + 1) % n];
        double cross = ux * vy - uy * vx;
        double dot = ux * vx + uy * vy;
        if ((!std::isfinite(cross)) || (!std::isfinite(dot))) {
            return false;
        }
        if ((std::abs(cross) <= Polygon::EPS) && (dot < 0)) {
            return false;
        }
    }
    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = i + 1; j < n; ++j) {
            if ((j == i + 1) || ((i == 0) && (j == n - 1))) {
                continue;
            }
            const Point& a = vertices[i];
            const Point& b = vertices[(i + 1) % n];
            const Point& c = vertices[j];
            const Point& d = vertices[(j + 1) % n];
            if (geometry::segmentsIntersect(a, b, c, d, Polygon::EPS)) {
                return false;
            }
        }
    }
    return true;
}

}

Pentagon::Pentagon()
    : Polygon(5) {
    vertices_[0] = {0, 0};
    vertices_[1] = {1, 0};
    vertices_[2] = {2, 1};
    vertices_[3] = {2, 2};
    vertices_[4] = {0, 1};
}

Pentagon::Pentagon(Point a, Point b, Point c, Point d, Point e)
    : Polygon(5) {
    vertices_[0] = a;
    vertices_[1] = b;
    vertices_[2] = c;
    vertices_[3] = d;
    vertices_[4] = e;
    if (!isValidPentagon(vertices_)) {
        throw std::invalid_argument("Invalid pentagon");
    }
}

void Pentagon::print(std::ostream& out) const {
    auto old_precision = out.precision();
    out << std::setprecision(std::numeric_limits<double>::max_digits10);
    out << "Pentagon ";
    for (const Point& vertex: vertices_) {
        out << vertex.x << ' ' << vertex.y << ' ';
    }
    Point c = center();
    out << "Center " << c.x << ' ' << c.y << ' ';
    out << "Area " << metric();
    out.precision(old_precision);
}

void Pentagon::read(std::istream& in) {
    std::string line;
    if (!std::getline(in >> std::ws, line)) {
        return;
    }
    std::istringstream data(line);
    std::string name;
    if (!(data >> name) || (name != "Pentagon")) {
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
    if (!isValidPentagon(new_vertices)) {
        in.setstate(std::ios::failbit);
        return;
    }
    vertices_ = new_vertices;
}

bool Pentagon::isRegular() const {
    constexpr std::size_t n = 5;
    std::array<double, 5> sides;
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
    double reference_cross = 0.0;
    double reference_dot = 0.0;
    for (std::size_t i = 0; i < n; ++i) {
        const Point& a = vertices_[i];
        const Point& b = vertices_[(i + 1) % n];
        const Point& c = vertices_[(i + 2) % n];
        double ux = (b.x - a.x) / sides[i];
        double uy = (b.y - a.y) / sides[i];
        double vx = (c.x - b.x) / sides[(i + 1) % n];
        double vy = (c.y - b.y) / sides[(i + 1) % n];
        double cross = ux * vy - uy * vx;
        double dot = ux * vx + uy * vy;
        if (i == 0) {
            reference_cross = cross;
            reference_dot = dot;
        } else if ((std::abs(cross - reference_cross) >= EPS) || (std::abs(dot - reference_dot) >= EPS)) {
            return false;
        }
    }
    return true;
}

Polygon* Pentagon::clone() const {
    return new Pentagon(*this);
}