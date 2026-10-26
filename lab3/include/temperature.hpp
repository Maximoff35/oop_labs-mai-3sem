#pragma once

#include <iosfwd>

enum class TemperatureUnit {
    Celsius,
    Fahrenheit,
    Kelvin
};

class Temperature final {
private:
    double value_;
    TemperatureUnit unit_;
    double to_celsius() const noexcept;

public:
    Temperature() noexcept;
    Temperature(double value, TemperatureUnit unit);

    double value() const noexcept;
    TemperatureUnit unit() const noexcept;

    bool operator==(const Temperature& other) const noexcept;

    friend std::ostream& operator<<(std::ostream& os, const Temperature& temperature);
};