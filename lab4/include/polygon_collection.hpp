#pragma once
#include "polygon.hpp"
#include <cstddef>

class PolygonCollection final {
private:
    Polygon** data_ = nullptr;
    std::size_t size_ = 0;
    std::size_t capacity_ = 0;
    void reserve(std::size_t new_capacity);
public:
    PolygonCollection() = default;
    ~PolygonCollection();
    PolygonCollection(const PolygonCollection& other);
    PolygonCollection& operator=(const PolygonCollection& other);
    PolygonCollection(PolygonCollection&& other) noexcept;
    PolygonCollection& operator=(PolygonCollection&& other) noexcept;
    void add(const Polygon& polygon);
    void remove(std::size_t index);
    void clear() noexcept;
    std::size_t size() const noexcept;
    Polygon& at(std::size_t index);
    const Polygon& at(std::size_t index) const;
    double totalMetric() const;
};