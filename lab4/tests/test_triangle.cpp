#include <gtest/gtest.h>
#include <cmath>
#include <sstream>
#include <stdexcept>

#include "triangle.hpp"

TEST(TriangleTest, DefaultConstructor) {
    Triangle t;
    EXPECT_DOUBLE_EQ(t.metric(), 0.5);
    EXPECT_FALSE(t.isEquilateral());
}

TEST(TriangleTest, AreaAndCenter) {
    Triangle t({0, 0}, {4, 0}, {2, 3});
    EXPECT_DOUBLE_EQ(t.metric(), 6.0);
    Point c = t.center();
    EXPECT_DOUBLE_EQ(c.x, 2.0);
    EXPECT_DOUBLE_EQ(c.y, 1.0);
}

TEST(TriangleTest, EquilateralTriangle) {
    Triangle t({0, 0}, {2, 0}, {1, std::sqrt(3.0)});
    EXPECT_TRUE(t.isEquilateral());
    EXPECT_NEAR(t.metric(), std::sqrt(3.0), 1e-6);
}

TEST(TriangleTest, DegenerateTriangle) {
    EXPECT_THROW(
        (Triangle({0, 0}, {1, 1}, {2, 2})),
        std::invalid_argument
    );
}

TEST(TriangleTest, DuplicateVertices) {
    EXPECT_THROW(
        (Triangle({0, 0}, {0, 0}, {1, 1})),
        std::invalid_argument
    );
}

TEST(TriangleTest, StreamInputOutput) {
    Triangle original({0, 0}, {4, 0}, {2, 3});
    std::stringstream stream;
    stream << original;
    Triangle restored;
    stream >> restored;
    EXPECT_DOUBLE_EQ(restored.metric(), original.metric());
    Point a = original.center();
    Point b = restored.center();
    EXPECT_DOUBLE_EQ(a.x, b.x);
    EXPECT_DOUBLE_EQ(a.y, b.y);
}