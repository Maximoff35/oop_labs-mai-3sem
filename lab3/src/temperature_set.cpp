#include "temperature_set.hpp"
#include <ostream>

TemperatureSet::TemperatureSet(const TemperatureSet& other) 
    : size_(other.size_), capacity_(other.capacity_) {
    if (capacity_ > 0) {
        data_ = new Temperature[capacity_];
        for (std::size_t i = 0; i < size_; i++) {
            data_[i] = other.data_[i];
        }
    }
}

TemperatureSet::TemperatureSet(TemperatureSet&& other) noexcept 
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

void TemperatureSet::swap(TemperatureSet& other) noexcept {
    std::size_t tmp_size = size_;
    size_ = other.size_;
    other.size_ = tmp_size;

    std::size_t tmp_capacity = capacity_;
    capacity_ = other.capacity_;
    other.capacity_ = tmp_capacity;

    Temperature* tmp_data = data_;
    data_ = other.data_;
    other.data_ = tmp_data;
}

TemperatureSet& TemperatureSet::operator=(const TemperatureSet& other) {
    if (this != &other) {
        TemperatureSet tmp(other);
        swap(tmp);
    }
    return *this;
}

TemperatureSet& TemperatureSet::operator=(TemperatureSet&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

TemperatureSet::~TemperatureSet() {
    delete[] data_;
}

void TemperatureSet::grow() {
    std::size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
    Temperature* new_data = new Temperature[new_capacity];
    for (std::size_t i = 0; i < size_; i++) {
        new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
}

std::size_t TemperatureSet::size() const noexcept {
    return size_;
}

std::size_t TemperatureSet::index_of(const Temperature& temperature) const noexcept {
    for (std::size_t i = 0; i < size_; i++) {
        if (data_[i] == temperature) {
            return i;
        }
    }
    return size_;
}

bool TemperatureSet::empty() const noexcept {
    return size_ == 0;
}

bool TemperatureSet::contains(const Temperature& temperature) const {
    return index_of(temperature) != size_;
}

bool TemperatureSet::add(const Temperature& temperature) {
    if (contains(temperature)) {
        return false;
    }
    if (size_ == capacity_) {
        grow();
    }
    data_[size_] = temperature;
    size_++;
    return true;
}

bool TemperatureSet::remove(const Temperature& temperature) {
    std::size_t index = index_of(temperature);
    if (index == size_) {
        return false;
    }
    for (std::size_t i = index; i + 1 < size_; i++) {
        data_[i] = data_[i + 1];
    }
    size_--;
    return true;
}

bool TemperatureSet::operator()(const Temperature& temperature) const {
    return contains(temperature);
}

TemperatureSet& TemperatureSet::operator+=(const Temperature& temperature) {
    add(temperature);
    return *this;
}

TemperatureSet& TemperatureSet::operator-=(const Temperature& temperature) {
    remove(temperature);
    return *this;
}

TemperatureSet TemperatureSet::operator|(const TemperatureSet& other) const {
    TemperatureSet res(*this);
    for (std::size_t i = 0; i < other.size_; i++) {
        res += other.data_[i];
    }
    return res;
}

TemperatureSet TemperatureSet::operator&(const TemperatureSet& other) const {
    TemperatureSet res;
    for (std::size_t i = 0; i < size_; i++) {
        if (other.contains(data_[i])) {
            res += data_[i];
        }
    }
    return res;
}

TemperatureSet TemperatureSet::operator-(const TemperatureSet& other) const {
    TemperatureSet res;
    for (std::size_t i = 0; i < size_; i++) {
        if (!other.contains(data_[i])) {
            res += data_[i];
        }
    }
    return res;
}

bool TemperatureSet::operator==(const TemperatureSet& other) const {
    if (this == &other) {
        return true;
    }
    if (size_ != other.size_) {
        return false;
    }
    for (std::size_t i = 0; i < size_; i++) {
        if (!other.contains(data_[i])) {
            return false;
        }
    }
    return true;
}

bool TemperatureSet::operator!=(const TemperatureSet& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const TemperatureSet& set) {
    os << "{";
    if (!set.empty()) {
        os << " ";
    }
    for (std::size_t i = 0; i < set.size_; i++) {
        os << set.data_[i];
        if (i + 1 < set.size_) {
            os << ", ";
        }
    }
    if (!set.empty()) {
        os << " ";
    }
    os << "}";
    return os;
}