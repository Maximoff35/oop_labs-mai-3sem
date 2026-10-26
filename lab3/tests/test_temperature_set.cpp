#include <gtest/gtest.h>
#include "temperature_set.hpp"
#include <sstream>
#include <utility>

namespace {

Temperature C(double value) {
    return Temperature(value, TemperatureUnit::Celsius);
}

Temperature F(double value) {
    return Temperature(value, TemperatureUnit::Fahrenheit);
}

Temperature K(double value) {
    return Temperature(value, TemperatureUnit::Kelvin);
}

TEST(TemperatureSetTest, DefaultConstructor) {
    TemperatureSet s;
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0u);
    EXPECT_FALSE(s.contains(C(20)));
}

TEST(TemperatureSetTest, AddElements) {
    TemperatureSet s;
    EXPECT_TRUE(s.add(C(10)));
    EXPECT_TRUE(s.add(C(20)));
    EXPECT_TRUE(s.add(C(30)));
    EXPECT_EQ(s.size(), 3u);
    EXPECT_FALSE(s.empty());
}

TEST(TemperatureSetTest, CanonicalDuplicates) {
    TemperatureSet s;
    EXPECT_TRUE(s.add(C(25)));
    EXPECT_FALSE(s.add(F(77)));
    EXPECT_FALSE(s.add(K(298.15)));
    EXPECT_EQ(s.size(), 1u);
}

TEST(TemperatureSetTest, ContainsAndCallOperator) {
    TemperatureSet s;
    s.add(C(0));
    s.add(C(100));
    EXPECT_TRUE(s.contains(F(32)));
    EXPECT_TRUE(s(F(212)));
    EXPECT_FALSE(s.contains(C(50)));
    EXPECT_FALSE(s(C(50)));
}

TEST(TemperatureSetTest, RemoveElements) {
    TemperatureSet s;
    s.add(C(10));
    s.add(C(20));
    EXPECT_TRUE(s.remove(C(10)));
    EXPECT_FALSE(s.remove(C(10)));
    EXPECT_EQ(s.size(), 1u);
    EXPECT_FALSE(s.contains(C(10)));
    EXPECT_TRUE(s.contains(C(20)));
}

TEST(TemperatureSetTest, RemoveEquivalentTemperature) {
    TemperatureSet s;
    s.add(C(0));
    EXPECT_TRUE(s.remove(F(32)));
    EXPECT_TRUE(s.empty());
}

TEST(TemperatureSetTest, RemovePreservesOrder) {
    TemperatureSet s;
    for (int i = 1; i <= 5; i++) {
        s.add(C(i * 10));
    }
    EXPECT_TRUE(s.remove(C(10)));
    EXPECT_TRUE(s.remove(C(30)));
    EXPECT_TRUE(s.remove(C(50)));
    std::ostringstream os;
    os << s;
    EXPECT_EQ(os.str(), "{ 20 C, 40 C }");
    EXPECT_EQ(s.size(), 2u);
}

TEST(TemperatureSetTest, ReAddAfterRemoval) {
    TemperatureSet s;
    s.add(C(10));
    s.add(C(20));
    s.add(C(30));
    s.remove(C(20));
    EXPECT_TRUE(s.add(C(20)));
    std::ostringstream os;
    os << s;
    EXPECT_EQ(os.str(), "{ 10 C, 30 C, 20 C }");
}

TEST(TemperatureSetTest, PlusMinusAssignment) {
    TemperatureSet s;
    (s += C(10)) += C(20);
    s += F(50);
    EXPECT_EQ(s.size(), 2u);
    (s -= C(10)) -= C(30);
    EXPECT_EQ(s.size(), 1u);
    EXPECT_TRUE(s.contains(C(20)));
}

TEST(TemperatureSetTest, CopyConstructor) {
    TemperatureSet a;
    a.add(C(10));
    a.add(C(20));
    TemperatureSet b(a);
    EXPECT_TRUE(a == b);
    b.add(C(30));
    b.remove(C(10));
    EXPECT_EQ(a.size(), 2u);
    EXPECT_TRUE(a.contains(C(10)));
    EXPECT_FALSE(a.contains(C(30)));
}

TEST(TemperatureSetTest, CopyAssignment) {
    TemperatureSet a;
    a.add(C(10));
    a.add(C(20));
    TemperatureSet b;
    b.add(C(100));
    b = a;
    EXPECT_TRUE(a == b);
    a.add(C(30));
    EXPECT_FALSE(b.contains(C(30)));
    b = b;
    EXPECT_EQ(b.size(), 2u);
    EXPECT_TRUE(b.contains(C(10)));
    EXPECT_TRUE(b.contains(C(20)));
}

TEST(TemperatureSetTest, MoveConstructor) {
    TemperatureSet a;
    a.add(C(10));
    a.add(C(20));
    TemperatureSet b(std::move(a));
    EXPECT_EQ(b.size(), 2u);
    EXPECT_TRUE(b.contains(C(10)));
    EXPECT_TRUE(b.contains(C(20)));
    EXPECT_TRUE(a.empty());
    EXPECT_TRUE(a.add(C(30)));
    EXPECT_EQ(a.size(), 1u);
}

TEST(TemperatureSetTest, MoveAssignment) {
    TemperatureSet a;
    a.add(C(10));
    a.add(C(20));
    TemperatureSet b;
    b.add(C(100));
    b = std::move(a);
    EXPECT_EQ(b.size(), 2u);
    EXPECT_TRUE(b.contains(C(10)));
    EXPECT_TRUE(b.contains(C(20)));
    EXPECT_FALSE(b.contains(C(100)));
    EXPECT_TRUE(a.empty());
    EXPECT_TRUE(a.add(C(30)));
}

TEST(TemperatureSetTest, SelfMoveAssignment) {
    TemperatureSet s;
    s.add(C(10));
    s.add(C(20));
    s = std::move(s);
    EXPECT_EQ(s.size(), 2u);
    EXPECT_TRUE(s.contains(C(10)));
    EXPECT_TRUE(s.contains(C(20)));
}

TEST(TemperatureSetTest, Union) {
    TemperatureSet a;
    a.add(C(0));
    a.add(C(10));
    TemperatureSet b;
    b.add(F(50));
    b.add(C(25));
    b.add(C(40));
    TemperatureSet result = a | b;
    EXPECT_EQ(result.size(), 4u);
    std::ostringstream os;
    os << result;
    EXPECT_EQ(os.str(), "{ 0 C, 10 C, 25 C, 40 C }");
    EXPECT_EQ(a.size(), 2u);
    EXPECT_EQ(b.size(), 3u);
}

TEST(TemperatureSetTest, Intersection) {
    TemperatureSet a;
    a.add(C(0));
    a.add(C(10));
    a.add(C(20));
    TemperatureSet b;
    b.add(F(68));
    b.add(F(32));
    b.add(C(50));
    TemperatureSet result = a & b;
    EXPECT_EQ(result.size(), 2u);
    EXPECT_TRUE(result.contains(C(0)));
    EXPECT_TRUE(result.contains(C(20)));
    EXPECT_FALSE(result.contains(C(10)));
    EXPECT_EQ(a.size(), 3u);
    EXPECT_EQ(b.size(), 3u);
}

TEST(TemperatureSetTest, Difference) {
    TemperatureSet a;
    a.add(C(0));
    a.add(C(10));
    a.add(C(20));
    TemperatureSet b;
    b.add(F(32));
    b.add(F(68));
    TemperatureSet result = a - b;
    EXPECT_EQ(result.size(), 1u);
    EXPECT_TRUE(result.contains(C(10)));
    EXPECT_TRUE((a - a).empty());
    EXPECT_EQ((a - TemperatureSet{}), a);
}

TEST(TemperatureSetTest, Equality) {
    TemperatureSet a;
    a.add(C(0));
    a.add(C(10));
    a.add(C(20));
    TemperatureSet b;
    b.add(F(68));
    b.add(F(32));
    b.add(F(50));
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
    TemperatureSet c;
    c.add(C(0));
    c.add(C(10));
    c.add(C(21));
    EXPECT_FALSE(a == c);
    EXPECT_TRUE(a != c);
    TemperatureSet d;
    EXPECT_TRUE(d == TemperatureSet{});
}

TEST(TemperatureSetTest, OutputOperator) {
    TemperatureSet s;
    std::ostringstream empty_os;
    empty_os << s;
    EXPECT_EQ(empty_os.str(), "{}");
    s.add(C(25));
    std::ostringstream single_os;
    single_os << s;
    EXPECT_EQ(single_os.str(), "{ 25 C }");
    s.add(F(32));
    s.add(K(300));
    std::ostringstream multiple_os;
    multiple_os << s;
    EXPECT_EQ(
        multiple_os.str(),
        "{ 25 C, 32 F, 300 K }"
    );
}

TEST(TemperatureSetTest, Stress1000) {
    TemperatureSet s;
    for (int i = 0; i < 1000; i++) {
        ASSERT_TRUE(s.add(C(i)));
    }
    EXPECT_EQ(s.size(), 1000u);
    for (int i = 0; i < 1000; i++) {
        double fahrenheit = 32.0 + i * 9.0 / 5.0;
        EXPECT_FALSE(s.add(F(fahrenheit)));
    }
    EXPECT_EQ(s.size(), 1000u);
    for (int i = 0; i < 1000; i++) {
        EXPECT_TRUE(s.contains(C(i)));
    }
    EXPECT_TRUE(s.remove(C(0)));
    EXPECT_TRUE(s.remove(C(500)));
    EXPECT_TRUE(s.remove(C(999)));
    EXPECT_EQ(s.size(), 997u);
    EXPECT_FALSE(s.contains(C(500)));
    EXPECT_TRUE(s.contains(C(501)));
}

}