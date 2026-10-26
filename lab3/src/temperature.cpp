#include "temperature.hpp"

#include <cmath>
#include <ostream>
#include <stdexcept>


Temperature::Temperature() noexcept 
    : value_(0.0), unit_(TemperatureUnit::Celsius) {}

Temperature::Temperature(double value, TemperatureUnit unit)
    : value_(value), unit_(unit) {
    if (!std::isfinite(value_)) {
        throw std::invalid_argument("Temperature must bu finite");
    }
    switch (unit_) {
        case TemperatureUnit::Celsius:
            if (value_ < -273.15) {
                throw std::invalid_argument("Below absolute zero");
            }
            break;
        case TemperatureUnit::Fahrenheit:
            if (value_ < -459.67) {
                throw std::invalid_argument("Below absolute zero");
            }
            break;
        case TemperatureUnit::Kelvin:
            if (value_ < 0.0) {
                throw std::invalid_argument("Below absolute zero");
            }
            break;
        default:
            throw std::invalid_argument("Invalid temperature unit");
    }
}

double Temperature::value() const noexcept {
    return value_;
}

TemperatureUnit Temperature::unit() const noexcept {
    return unit_;
}

double Temperature::to_celsius() const noexcept {
    switch (unit_) {
        case TemperatureUnit::Celsius:
            return value_;
        case TemperatureUnit::Fahrenheit:
            return (value_ - 32.0) * 5.0 / 9.0;
        case TemperatureUnit::Kelvin:
            return value_ - 273.15;
    }
    return value_;
}

bool Temperature::operator==(const Temperature& other) const noexcept {
    constexpr double scale = 1'000'000.0;
    return std::round(to_celsius() * scale) == std::round(other.to_celsius() * scale);
}

std::ostream& operator<<(std::ostream& os, const Temperature& temperature) {
    os << temperature.value_;
    switch (temperature.unit_) {
        case TemperatureUnit::Celsius:
            os << " C";
            break;
        case TemperatureUnit::Fahrenheit:
            os << " F";
            break;
        case TemperatureUnit::Kelvin:
            os << " K";
            break;
    }
    return os;
}