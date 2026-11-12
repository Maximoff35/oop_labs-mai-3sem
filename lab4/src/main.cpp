
#include <iostream>
#include <utility>

#include "triangle.hpp"
#include "square.hpp"
#include "pentagon.hpp"
#include "polygon_collection.hpp"

int main() {
    PolygonCollection collection;

    Triangle triangle({0, 0}, {4, 0}, {2, 3});
    Square square({0, 0}, {2, 0}, {2, 2}, {0, 2});
    Pentagon pentagon;

    collection.add(triangle);
    collection.add(square);
    collection.add(pentagon);

    std::cout << "Original size: "
              << collection.size() << '\n';

    std::cout << "Original total area: "
              << collection.totalMetric() << '\n';


    for (std::size_t i = 0; i < collection.size(); ++i) {
        std::cout << collection.at(i) << '\n';
    }


    Triangle* t = dynamic_cast<Triangle*>(&collection.at(0));

    if (t != nullptr) {
        std::cout << "Triangle found, equilateral: "
                  << t->isEquilateral() << '\n';
    }


    PolygonCollection copy(collection);
    copy.remove(0);

    std::cout << "Original after copy removal: "
              << collection.size() << '\n';

    std::cout << "Copy after removal: "
              << copy.size() << '\n';


    PolygonCollection moved(std::move(copy));

    std::cout << "Moved size: "
              << moved.size() << '\n';

    std::cout << "Old copy size: "
              << copy.size() << '\n';

    return 0;
}
