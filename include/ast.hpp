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

    //struct Path {
    //    int size;
    //    std::vector<Layer> layers;
    //};

    //struct Bit {
    //    int width;
    //    Path path;
    //};

    //struct Bus {
    //    std::string name;
    //    std::vector<Bit> bits;
    //};
}
