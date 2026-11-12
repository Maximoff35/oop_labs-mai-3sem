
#include <gtest/gtest.h>
#include <memory>
#include <sstream>

#include "polygon.hpp"
#include "triangle.hpp"
#include "square.hpp"
#include "pentagon.hpp"
#include "polygon_collection.hpp"

TEST(PolymorphismTest, VirtualMetric) {
    Triangle t({0, 0}, {4, 0}, {2, 3});
    Square s({0, 0}, {2, 0}, {2, 2}, {0, 2});
    Pentagon p;
    const Polygon* figures[] = {&t, &s, &p};
    EXPECT_DOUBLE_EQ(figures[0]->metric(), 6.0);
    EXPECT_DOUBLE_EQ(figures[1]->metric(), 4.0);
    EXPECT_DOUBLE_EQ(figures[2]->metric(), 2.5);
}

TEST(PolymorphismTest, ClonePreservesType) {
    Square s({0, 0}, {2, 0}, {2, 2}, {0, 2});
    const Polygon& original = s;
    std::unique_ptr<Polygon> copy(original.clone());
    ASSERT_NE(copy, nullptr);
    EXPECT_NE(copy.get(), &original);
    EXPECT_NE(dynamic_cast<Square*>(copy.get()), nullptr);
    EXPECT_DOUBLE_EQ(copy->metric(), 4.0);
}

TEST(PolymorphismTest, DynamicCast) {
    Triangle t;
    Polygon* p = &t;
    EXPECT_NE(dynamic_cast<Triangle*>(p), nullptr);
    EXPECT_EQ(dynamic_cast<Square*>(p), nullptr);
    EXPECT_EQ(dynamic_cast<Pentagon*>(p), nullptr);
}

TEST(PolymorphismTest, ConversionToDouble) {
    Triangle t({0, 0}, {4, 0}, {2, 3});
    const Polygon& p = t;
    EXPECT_DOUBLE_EQ(static_cast<double>(p), 6.0);
}

TEST(PolymorphismTest, EqualityByArea) {
    Triangle t({0, 0}, {4, 0}, {0, 2});
    Square s({0, 0}, {2, 0}, {2, 2}, {0, 2});
    Pentagon p;
    const Polygon& a = t;
    const Polygon& b = s;
    const Polygon& c = p;
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
}

TEST(PolymorphismTest, VirtualStreamOutput) {
    Triangle t({0, 0}, {4, 0}, {2, 3});
    const Polygon& p = t;
    std::ostringstream out;
    out << p;
    EXPECT_EQ(out.str().find("Triangle"), 0u);
    EXPECT_NE(out.str().find("Area"), std::string::npos);
}

TEST(PolymorphismTest, SpecificMethodsThroughDynamicCast) {
    PolygonCollection collection;
    collection.add(Triangle());
    collection.add(Square());
    collection.add(Pentagon());
    auto* t = dynamic_cast<Triangle*>(&collection.at(0));
    auto* s = dynamic_cast<Square*>(&collection.at(1));
    auto* p = dynamic_cast<Pentagon*>(&collection.at(2));
    ASSERT_NE(t, nullptr);
    ASSERT_NE(s, nullptr);
    ASSERT_NE(p, nullptr);
    EXPECT_FALSE(t->isEquilateral());
    EXPECT_DOUBLE_EQ(s->side(), 1.0);
    EXPECT_FALSE(p->isRegular());
}