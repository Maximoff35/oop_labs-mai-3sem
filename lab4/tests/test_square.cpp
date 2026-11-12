#include <gtest/gtest.h>
#include <cmath>
#include <sstream>
#include <stdexcept>

#include "square.hpp"

TEST(SquareTest, DefaultConstructor) {
    Square s;
    EXPECT_DOUBLE_EQ(s.side(), 1.0);
    EXPECT_DOUBLE_EQ(s.metric(), 1.0);
}

TEST(SquareTest, SideAreaAndCenter) {
    Square s({0, 0}, {2, 0}, {2, 2}, {0, 2});
    EXPECT_DOUBLE_EQ(s.side(), 2.0);
    EXPECT_DOUBLE_EQ(s.metric(), 4.0);
    Point c = s.center();
    EXPECT_DOUBLE_EQ(c.x, 1.0);
    EXPECT_DOUBLE_EQ(c.y, 1.0);
}

TEST(SquareTest, RotatedSquare) {
    Square s({0, 1}, {1, 2}, {2, 1}, {1, 0});
    EXPECT_NEAR(s.side(), std::sqrt(2.0), 1e-6);
    EXPECT_NEAR(s.metric(), 2.0, 1e-6);
}

TEST(SquareTest, RectangleIsNotSquare) {
    EXPECT_THROW(
        (Square({0, 0}, {4, 0}, {4, 2}, {0, 2})),
        std::invalid_argument
    );
}

TEST(SquareTest, DegenerateSquare) {
    EXPECT_THROW(
        (Square({0, 0}, {0, 0}, {0, 0}, {0, 0})),
        std::invalid_argument
    );
}

TEST(SquareTest, StreamInputOutput) {
    Square original({0, 0}, {3, 0}, {3, 3}, {0, 3});
    std::stringstream stream;
    stream << original;
    Square restored;
    stream >> restored;
    EXPECT_DOUBLE_EQ(restored.side(), 3.0);
    EXPECT_DOUBLE_EQ(restored.metric(), 9.0);
}