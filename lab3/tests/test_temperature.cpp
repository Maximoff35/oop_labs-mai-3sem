#include <gtest/gtest.h>
#include <sstream>
#include "temperature.hpp"

TEST(TemperatureTest, DefaultConstructor) {
    Temperature t;
    EXPECT_DOUBLE_EQ(t.value(), 0.0);
    EXPECT_EQ(t.unit(), TemperatureUnit::Celsius);
}

TEST(TemperatureTest, ParametrizedConstructor) {
    Temperature t(56.0, TemperatureUnit::Fahrenheit);
    EXPECT_DOUBLE_EQ(t.value(), 56.0);
    EXPECT_EQ(t.unit(), TemperatureUnit::Fahrenheit);
}

TEST(TemperatureTest, EqualCelsius) {
    Temperature a(30.0, TemperatureUnit::Celsius);
    Temperature b(30.0, TemperatureUnit::Celsius);
    EXPECT_TRUE(a == b);
}

TEST(TemperatureTest, CelsiusFahrenheitEquality) {
    Temperature a(0.0, TemperatureUnit::Celsius);
    Temperature b(32.0, TemperatureUnit::Fahrenheit);
    EXPECT_TRUE(a == b);
    EXPECT_TRUE(b == a);
}

TEST(TemperatureTest, AllUnitsEquality) {
    Temperature a(25.0, TemperatureUnit::Celsius);
    Temperature b(77.0, TemperatureUnit::Fahrenheit);
    Temperature c(298.15, TemperatureUnit::Kelvin);
    EXPECT_TRUE(a == b);
    EXPECT_TRUE(b == c);
    EXPECT_TRUE(a == c);
}

TEST(TemperatureTest, NegativeTemperature) {
    Temperature a(-40.0, TemperatureUnit::Celsius);
    Temperature b(-40.0, TemperatureUnit::Fahrenheit);
    EXPECT_TRUE(a == b);
}

TEST(TemperatureTest, DifferentTemperatures) {
    Temperature a(20.0, TemperatureUnit::Celsius);
    Temperature b(21.0, TemperatureUnit::Celsius);
    Temperature c(68.0, TemperatureUnit::Fahrenheit);
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a == c);
}

TEST(TemperatureTest, Precision) {
    Temperature a(25.0, TemperatureUnit::Celsius);
    Temperature b(25.0000001, TemperatureUnit::Celsius);
    Temperature c(25.000002, TemperatureUnit::Celsius);
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
}

TEST(TemperatureTest, OutputOperator) {
    Temperature a(25.0, TemperatureUnit::Celsius);
    Temperature b(77.0, TemperatureUnit::Fahrenheit);
    Temperature c(298.15, TemperatureUnit::Kelvin);
    std::ostringstream os;
    os << a << " | " << b << " | " << c;
    EXPECT_EQ(os.str(), "25 C | 77 F | 298.15 K");
}

TEST(TemperatureTest, BelowAbsoluteZero) {
    EXPECT_THROW(
        Temperature(-1.0, TemperatureUnit::Kelvin),
        std::invalid_argument
    );
    EXPECT_THROW(
        Temperature(-300.0, TemperatureUnit::Celsius),
        std::invalid_argument
    );
}

TEST(TemperatureTest, InvalidUnit) {
    EXPECT_THROW(
        Temperature(20.0, static_cast<TemperatureUnit>(100)),
        std::invalid_argument
    );
}