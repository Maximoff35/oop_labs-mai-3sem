#include "matrix.h"
#include <stdexcept>
#include <limits>
#include <ostream>

Matrix::Matrix(std::size_t rows, std::size_t cols, double value) 
    : rows_(rows), cols_(cols)
{   
    const std::size_t max_elements = std::numeric_limits<std::size_t>::max() / sizeof(double);
    if ((cols_ != 0) && (rows_ > max_elements / cols_)) {
        throw std::length_error("Matrix size overflow");
    }
    data_ = new double[rows_ * cols_];
    for (std::size_t i = 0; i < rows_ * cols_; i++) {
        data_[i] = value;
    }
}

Matrix::~Matrix() {
    delete[] data_;
}

Matrix::Matrix(const Matrix& other) 
    : rows_(other.rows_), cols_(other.cols_)
{
    data_ = new double[rows_ * cols_];

    for (std::size_t i = 0; i < rows_ * cols_; i++) {
        data_[i] = other.data_[i];
    }
}

Matrix::Matrix(Matrix&& other) noexcept 
    : rows_(other.rows_), cols_(other.cols_), data_(other.data_)
{
    other.rows_ = 0;
    other.cols_ = 0;
    other.data_ = nullptr;
}

void Matrix::swap(Matrix& other) noexcept {
    std::size_t tmp_rows = rows_;
    rows_ = other.rows_;
    other.rows_ = tmp_rows;

    std::size_t tmp_cols = cols_;
    cols_ = other.cols_;
    other.cols_ = tmp_cols;

    double* tmp_data = data_;
    data_ = other.data_;
    other.data_ = tmp_data;
}

Matrix& Matrix::operator=(Matrix other) {
    swap(other);
    return *this;
}

std::size_t Matrix::rows() const {
    return rows_;
}

std::size_t Matrix::cols() const {
    return cols_;
}

double Matrix::get(std::size_t r, std::size_t c) const {
    if ((r >= rows_) || (c >= cols_)) {
        throw std::out_of_range("Matrix index out of range");
    }
    return data_[r * cols_ + c];
}

void Matrix::set(std::size_t r, std::size_t c, double value) {
    if ((r >= rows_) || (c >= cols_)) {
        throw std::out_of_range("Matrix index out of range");
    }
    data_[r * cols_ + c] = value;
}

double Matrix::sum() const {
    double res = 0.0;
    for (std::size_t i = 0; i < rows_ * cols_; i++) {
        res += data_[i];
    }
    return res;
}

void Matrix::add(const Matrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Matrix dimensions mismatch");
    }

    for (std::size_t i = 0; i < rows_ * cols_; ++i) {
        data_[i] += other.data_[i];
    }
}

void Matrix::mul(const Matrix& other) {
    if (cols_ != other.rows_) {
        throw std::invalid_argument("Matrix dimensions mismatch");
    }

    Matrix result(rows_, other.cols_, 0.0);

    for (std::size_t i = 0; i < rows_; ++i) {
        for (std::size_t j = 0; j < other.cols_; ++j) {
            for (std::size_t k = 0; k < cols_; ++k) {
                result.data_[i * result.cols_ + j] +=
                    data_[i * cols_ + k] *
                    other.data_[k * other.cols_ + j];
            }
        }
    }

    swap(result);
}

void Matrix::print(std::ostream& out) const {
    for (std::size_t r = 0; r < rows_; ++r) {
        for (std::size_t c = 0; c < cols_; ++c) {
            if (c > 0) {
                out << ' ';
            }
            out << data_[r * cols_ + c];
        }
        out << '\n';
    }
}