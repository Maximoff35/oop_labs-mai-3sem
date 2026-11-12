
#include <gtest/gtest.h>
#include <cmath>
#include <sstream>
#include <stdexcept>

#include "pentagon.hpp"

TEST(PentagonTest, DefaultConstructor) {
    Pentagon p;
    EXPECT_DOUBLE_EQ(p.metric(), 2.5);
    EXPECT_FALSE(p.isRegular());
}

TEST(PentagonTest, DefaultCenter) {
    Pentagon p;
    Point c = p.center();
    EXPECT_DOUBLE_EQ(c.x, 1.0);
    EXPECT_NEAR(c.y, 0.8, 1e-6);
}

TEST(PentagonTest, RegularPentagon) {
    const double pi = std::acos(-1.0);
    const double step = 2.0 * pi / 5.0;
    auto vertex = [step](int i) {
        double angle = step * i;
        return Point{2.0 * std::cos(angle),
                     2.0 * std::sin(angle)};
    };
    Pentagon p(vertex(0), vertex(1), vertex(2), vertex(3), vertex(4));
    EXPECT_TRUE(p.isRegular());
    EXPECT_GT(p.metric(), 0.0);
}

TEST(PentagonTest, DuplicateVertices) {
    EXPECT_THROW(
        (Pentagon({0, 0}, {0, 0}, {2, 0}, {2, 2}, {0, 2})),
        std::invalid_argument
    );
}

TEST(PentagonTest, SelfIntersection) {
    EXPECT_THROW(
        (Pentagon({0, 0}, {2, 2}, {0, 2}, {2, 0}, {1, -1})),
        std::invalid_argument
    );
}

TEST(PentagonTest, StreamInputOutput) {
    Pentagon original;
    std::stringstream stream;
    stream << original;
    Pentagon restored;
    stream >> restored;
    EXPECT_DOUBLE_EQ(restored.metric(), original.metric());
    EXPECT_EQ(restored.isRegular(), original.isRegular());
}
