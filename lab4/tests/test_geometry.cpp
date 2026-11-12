
#include <gtest/gtest.h>
#include <vector>

#include "geometry_utils.hpp"
#include "triangle.hpp"
#include "square.hpp"
#include "pentagon.hpp"

TEST(GeometryTest, PolygonArea) {
    std::vector<Point> vertices = {{0, 0}, {4, 0}, {4, 2}, {0, 2}};
    EXPECT_DOUBLE_EQ(geometry::polygonArea(vertices), 8.0);
}

TEST(GeometryTest, AreaIndependentOfVertexOrder) {
    std::vector<Point> vertices = {{0, 0}, {0, 2}, {4, 2}, {4, 0}};
    EXPECT_DOUBLE_EQ(geometry::polygonArea(vertices), 8.0);
}

TEST(GeometryTest, PointOnSegment) {
    EXPECT_TRUE(geometry::pointOnSegment({1, 1}, {0, 0}, {2, 2}, 1e-6));
    EXPECT_TRUE(geometry::pointOnSegment({0, 0}, {0, 0}, {2, 2}, 1e-6));
}

TEST(GeometryTest, PointOutsideSegment) {
    EXPECT_FALSE(geometry::pointOnSegment({3, 3}, {0, 0}, {2, 2}, 1e-6));
    EXPECT_FALSE(geometry::pointOnSegment({1, 1.1}, {0, 0}, {2, 2}, 1e-6));
}

TEST(GeometryTest, PointInsideTriangle) {
    Triangle t({0, 0}, {4, 0}, {0, 4});
    EXPECT_TRUE(t.containsPoint({1, 1}));
    EXPECT_FALSE(t.containsPoint({3, 3}));
}

TEST(GeometryTest, PointOnTriangleBoundary) {
    Triangle t({0, 0}, {4, 0}, {0, 4});
    EXPECT_TRUE(t.containsPoint({2, 0}));
    EXPECT_TRUE(t.containsPoint({0, 0}));
}

TEST(GeometryTest, PointInsideSquare) {
    Square s({0, 0}, {2, 0}, {2, 2}, {0, 2});
    EXPECT_TRUE(s.containsPoint({1, 1}));
    EXPECT_TRUE(s.containsPoint({0, 1}));
    EXPECT_FALSE(s.containsPoint({3, 1}));
}

TEST(GeometryTest, PointInsidePentagon) {
    Pentagon p;
    EXPECT_TRUE(p.containsPoint({1, 0.5}));
    EXPECT_FALSE(p.containsPoint({3, 3}));
}
