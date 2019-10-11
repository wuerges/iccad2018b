#pragma once

#include <vector>
#include <string>

namespace ast {
    struct Point {
        int x, y;
    };

    struct Rectangle {
        Point p1, p2;
    };

    struct RoutedShape {
        std::string layer;
        Rectangle rect;
    };

    struct Bit {
        int name;
        std::vector<RoutedShape> layers;
    };

    struct Width {
        std::vector<int> constraints;
    };

    struct Bus {
        std::string name;
        Width width;
        std::vector<Bit> bits;
    };
}
