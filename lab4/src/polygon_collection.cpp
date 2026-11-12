#include "polygon_collection.hpp"
#include <stdexcept>
#include <utility>

void PolygonCollection::clear() noexcept {
    for (std::size_t i = 0; i < size_; ++i) {
        delete data_[i];
    }
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
}

PolygonCollection::~PolygonCollection() {
    clear();
}

void PolygonCollection::reserve(std::size_t new_capacity) {
    if (new_capacity <= capacity_) {
        return;
    }
    Polygon** new_data = new Polygon*[new_capacity]{};
    for (std::size_t i = 0; i < size_; ++i) {
        new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
}

void PolygonCollection::add(const Polygon& polygon) {
    if (size_ == capacity_) {
        std::size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
        reserve(new_capacity);
    }
    Polygon* new_elem = polygon.clone();
    data_[size_] = new_elem;
    size_++;
}

void PolygonCollection::remove(std::size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Collection index out of range");
    }
    delete data_[index];
    for (std::size_t i = index; i < size_ - 1; ++i) {
        data_[i] = data_[i + 1];
    }
    size_--;
    data_[size_] = nullptr;
}

std::size_t PolygonCollection::size() const noexcept {
    return size_;
}

Polygon& PolygonCollection::at(std::size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Collection index out of range");
    }
    return *data_[index];
}

const Polygon& PolygonCollection::at(std::size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Collection index out of range");
    }
    const Polygon& res = *data_[index];
    return res;
}

double PolygonCollection::totalMetric() const {
    double res = 0.0;
    for (std::size_t i = 0; i < size_; ++i) {
        const Polygon& p = *data_[i];
        res += p.metric();
    }
    return res;
}

PolygonCollection::PolygonCollection(const PolygonCollection& other) {
    if (other.capacity_ == 0) {
        return;
    }
    data_ = new Polygon*[other.capacity_]{};
    capacity_ = other.capacity_;
    try {
        for (std::size_t i = 0; i < other.size_; ++i) {
            data_[i] = other.data_[i]->clone();
            ++size_;
        }
    } catch (...) {
        clear();
        throw;
    }
}

PolygonCollection::PolygonCollection(PolygonCollection&& other) noexcept 
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

PolygonCollection& PolygonCollection::operator=(const PolygonCollection& other) {
    if (this != &other) {
        PolygonCollection temp(other);
        std::swap(data_, temp.data_);
        std::swap(size_, temp.size_);
        std::swap(capacity_, temp.capacity_);
    }
    return *this;
}

PolygonCollection& PolygonCollection::operator=(PolygonCollection&& other) noexcept {
    if (this != &other) {
        clear();
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}