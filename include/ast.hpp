#pragma once

#include <vector>
#include <string>

namespace ast {
    struct Point {
        int x, y;
    };
    // using point = std::vector<int>;
    struct Layer {
        std::string name;
        std::vector<Point> points;
    };

    struct Path {
        int size;
        std::vector<Layer> layers;
    };

    struct Bit {
        int width;
        Path path;
    };

    struct Bus {
        std::string name;
        std::vector<Bit> bits;
    };
}
