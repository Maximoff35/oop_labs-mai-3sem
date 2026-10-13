#pragma once

#include <cstddef>
#include <iosfwd>

class Matrix {
private:
    std::size_t rows_ = 0;
    std::size_t cols_ = 0;
    double* data_ = nullptr;

public:
    Matrix(std::size_t rows, std::size_t cols, double value);
    ~Matrix();
    Matrix(const Matrix& other);
    Matrix(Matrix&& other) noexcept;
    void swap(Matrix& other) noexcept;
    Matrix& operator=(Matrix other);
    std::size_t rows() const;
    std::size_t cols() const;
    double get(std::size_t r, std::size_t c) const;
    void set(std::size_t r, std::size_t c, double value);
    double sum() const;
    void add(const Matrix& other);
    void mul(const Matrix& other);
    void print(std::ostream& out) const;
};

