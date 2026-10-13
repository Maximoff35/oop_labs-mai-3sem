#include <iostream>
#include <utility>
#include "matrix.h"

int main() {
    Matrix a = Matrix(2, 2, 0.0);
    a.set(0, 0, 1.0);
    a.set(0, 1, 2.0);
    a.set(1, 0, 3.0);
    a.set(1, 1, 4.0);

    Matrix b(a);
    b.set(0, 0, 100.0);

    std::cout << a.rows() << '\n';
    std::cout << a.cols() << '\n';
    std::cout << a.get(1, 0) << '\n';
    std::cout << a.get(0, 0) << ' ' << b.get(0, 0) << '\n';
    std::cout << a.sum() << ' ' << b.sum() << "\n\n";

    Matrix c(std::move(a));
    std::cout << c.rows() << ' ' << c.cols() << ' ' << c.sum() << '\n';
    std::cout << a.rows() << ' ' << a.cols() << ' ' << a.sum() << '\n';

    Matrix d(a);
    std::cout << d.rows() << ' ' << d.cols() << ' ' << d.sum() << '\n';
    
    a = b;
    a.set(0, 0, 5.0);
    std::cout << a.get(0, 0) << ' ' << b.get(0, 0) << '\n';
    b = b;
    std::cout << b.sum() << "\n\n";
    c = std::move(b);
    std::cout << b.rows() << ' ' << b.cols() << ' ' << b.sum() << '\n';
    std::cout << c.rows() << ' ' << c.cols() << ' ' << c.sum() << '\n';

    Matrix first(2, 2, 1.0);
    Matrix second(2, 2, 2.0);

    first.add(second);
    first.print(std::cout);

    std::cout << '\n';

    first.mul(second);
    first.print(std::cout);

    return 0;
}