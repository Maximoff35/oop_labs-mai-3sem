#pragma once

#include <cstddef>
#include <iosfwd>
#include "temperature.hpp"

class TemperatureSet final {
private:
    Temperature* data_ = nullptr;
    std::size_t size_ = 0;
    std::size_t capacity_ = 0;

    std::size_t index_of(const Temperature& temperature) const noexcept;
    void grow();
    void swap(TemperatureSet& other) noexcept;

public:
    TemperatureSet() noexcept = default;
    TemperatureSet(const TemperatureSet& other);
    TemperatureSet(TemperatureSet&& other) noexcept;
    TemperatureSet& operator=(const TemperatureSet& other);
    TemperatureSet& operator=(TemperatureSet&& other) noexcept;
    ~TemperatureSet();

    bool add(const Temperature& temperature);
    bool remove(const Temperature& temperature);
    bool contains(const Temperature& temperature) const;
    bool operator()(const Temperature& temperature) const;
    std::size_t size() const noexcept;
    bool empty() const noexcept;

    TemperatureSet& operator+=(const Temperature& temperature);
    TemperatureSet& operator-=(const Temperature& temperature);

    TemperatureSet operator|(const TemperatureSet& other) const;
    TemperatureSet operator&(const TemperatureSet& other) const;
    TemperatureSet operator-(const TemperatureSet& other) const;

    bool operator==(const TemperatureSet& other) const;
    bool operator!=(const TemperatureSet& other) const;

    friend std::ostream& operator<<(std::ostream& os, const TemperatureSet& set);
};