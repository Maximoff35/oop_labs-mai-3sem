#include <gtest/gtest.h>
#include "matrix.h"
#include <stdexcept>
#include <utility>

TEST(MatrixTest, Constructor) {
    Matrix a(2, 2, 0.0);
    EXPECT_EQ(a.rows(), 2);
    EXPECT_EQ(a.cols(), 2);
    for (std::size_t r = 0; r < a.rows(); r++) {
        for (std::size_t c = 0; c < a.cols(); c++) {
            EXPECT_DOUBLE_EQ(a.get(r, c), 0.0);
        }
    }
}

TEST(MatrixTest, SingleElem) {
    Matrix a(1, 1, 2.0);
    EXPECT_EQ(a.rows(), 1);
    EXPECT_EQ(a.cols(), 1);
    EXPECT_DOUBLE_EQ(a.get(0, 0), 2.0);
    EXPECT_DOUBLE_EQ(a.sum(), 2.0);
}

TEST(MatrixTest, EmptyMatrix) {
    Matrix a(0, 0, 10.0);
    EXPECT_EQ(a.rows(), 0);
    EXPECT_EQ(a.cols(), 0);
    EXPECT_DOUBLE_EQ(a.sum(), 0.0);
}

TEST(MatrixTest, ZeroRows) {
    Matrix a(0, 3, 10.0);
    EXPECT_EQ(a.rows(), 0);
    EXPECT_EQ(a.cols(), 3);
    EXPECT_DOUBLE_EQ(a.sum(), 0.0);
}


TEST(MatrixReadAndWriteTest, GetSet) {
    Matrix a(2, 2, 0.0);
    a.set(0, 0, 1.0);
    a.set(0, 1, 2.0);
    a.set(1, 0, 3.0);
    a.set(1, 1, 4.0);

    EXPECT_DOUBLE_EQ(a.get(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(a.get(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(a.get(1, 0), 3.0);
    EXPECT_DOUBLE_EQ(a.get(1, 1), 4.0);
}

TEST(MatrixReadAndWriteTest, GetInvalid) {
    Matrix a(2, 3, 0.0);
    EXPECT_THROW(a.get(2, 0), std::out_of_range);
    EXPECT_THROW(a.get(100, 0), std::out_of_range);
    EXPECT_THROW(a.get(0, 3), std::out_of_range);
    EXPECT_THROW(a.get(0, 100), std::out_of_range);
    EXPECT_THROW(a.get(100, 100), std::out_of_range);
}

TEST(MatrixReadAndWriteTest, SetInvalid) {
    Matrix a(2, 3, 0.0);
    EXPECT_THROW(a.set(2, 0, 10.0), std::out_of_range);
    EXPECT_THROW(a.set(10, 0, 10.0), std::out_of_range);
    EXPECT_THROW(a.set(0, 3, 10.0), std::out_of_range);
    EXPECT_THROW(a.set(0, 10, 10.0), std::out_of_range);
    EXPECT_THROW(a.set(10, 10, 10.0), std::out_of_range);
}

TEST(MatrixSumTest, Sum) {
    Matrix a(2, 3, 0.0);
    double value = 1.0;
    for (std::size_t r = 0; r < a.rows(); r++) {
        for (std::size_t c = 0; c < a.cols(); c++) {
            a.set(r, c, value);
            value *= 2.0;
        }
    }
    EXPECT_DOUBLE_EQ(a.sum(), 63.0);
}

TEST(MatrixSumTest, SumNegative) {
    Matrix a(2, 3, 0.0);
    double value = 1.0;
    for (std::size_t r = 0; r < a.rows(); r++) {
        for (std::size_t c = 0; c < a.cols(); c++) {
            a.set(r, c, value);
            value *= -2.5;
        }
    }
    EXPECT_DOUBLE_EQ(a.sum(), -69.46875);
}

TEST(MatrixSumTest, SumEmpty) {
    Matrix a(0, 0, 5.0);
    EXPECT_DOUBLE_EQ(a.sum(), 0.0);
}

TEST(MatrixDeepCopyTest, CopyConstructor) {
    Matrix a(2, 4, 6.0);
    Matrix b(a);
    b.set(0, 0, 50.4);
    EXPECT_DOUBLE_EQ(a.get(0, 0), 6.0);
    EXPECT_DOUBLE_EQ(b.get(0, 0), 50.4);
    EXPECT_DOUBLE_EQ(a.sum(), 48.0);
    EXPECT_DOUBLE_EQ(b.sum(), 92.4);
}

TEST(MatrixDeepCopyTest, CopyEmpty) {
    Matrix a(0, 0, 8.0);
    Matrix b(a);
    EXPECT_EQ(b.cols(), 0);
    EXPECT_EQ(b.rows(), 0);
    EXPECT_DOUBLE_EQ(b.sum(), 0.0);
}

TEST(MatrixMoveTest, MoveConstructor) {
    Matrix a(2, 4, 6.0);
    Matrix b(std::move(a));
    EXPECT_EQ(b.rows(), 2);
    EXPECT_EQ(b.cols(), 4);
    EXPECT_DOUBLE_EQ(b.sum(), 48.0);
    EXPECT_EQ(a.rows(), 0);
    EXPECT_EQ(a.cols(), 0);
    EXPECT_DOUBLE_EQ(a.sum(), 0.0);
}

TEST(MatrixCopyAndSwapTest, CopyAssignment) {
    Matrix a(2, 2, 4.0);
    Matrix b(2, 2, 10.0);

    a = b;
    a.set(0, 0, 100.0);
    EXPECT_DOUBLE_EQ(a.get(0, 0), 100.0);
    EXPECT_DOUBLE_EQ(b.get(0, 0), 10.0);
}

TEST(MatrixCopyAndSwapTest, AssignmentDifferentSize) {
    Matrix a(2, 2, 4.0);
    Matrix b(5, 4, 10.0);

    a = b;
    EXPECT_EQ(a.rows(), 5);
    EXPECT_EQ(a.cols(), 4);
    EXPECT_DOUBLE_EQ(a.sum(), 200.0);
}

TEST(MatrixCopyAndSwapTest, SelfAssignment) {
    Matrix a(2, 2, 5.0);
    a = a;
    EXPECT_EQ(a.rows(), 2);
    EXPECT_EQ(a.cols(), 2);
    for (std::size_t r = 0; r < a.rows(); r++) {
        for (std::size_t c = 0; c < a.cols(); c++) {
            EXPECT_DOUBLE_EQ(a.get(r, c), 5.0);
        }
    }
}

TEST(MatrixCopyAndSwapTest, MoveAssignment) {
    Matrix a(2, 4, 6.0);
    Matrix b(5, 8, -42.4);
    b = std::move(a);
    EXPECT_EQ(b.rows(), 2);
    EXPECT_EQ(b.cols(), 4);
    EXPECT_DOUBLE_EQ(b.sum(), 48.0);
    EXPECT_EQ(a.rows(), 0);
    EXPECT_EQ(a.cols(), 0);
    EXPECT_DOUBLE_EQ(a.sum(), 0.0);
}

TEST(MatrixSwapTest, Swap) {
    Matrix a(2, 4, 6.0);
    Matrix b(5, 8, -42.4);
    a.swap(b);
    EXPECT_EQ(b.rows(), 2);
    EXPECT_EQ(b.cols(), 4);
    EXPECT_DOUBLE_EQ(b.sum(), 48.0);
    EXPECT_EQ(a.rows(), 5);
    EXPECT_EQ(a.cols(), 8);
    EXPECT_NEAR(a.sum(), -1696.0, 1e-9);
}
