#pragma once

#include <vector>
#include <string>
#include <limits>

namespace ast {
    struct Point {
        uint32_t x, y;
    };

    struct Rectangle {
        Point p1, p2;
    };

    struct Layer {
        std::string name;
        bool horizontal;
        int spacing;
    };

    struct RoutedShape {
        std::string layer;
        Rectangle rect;
    };

    struct Bit {
        std::string name;
        std::vector<RoutedShape> shapes;
    };

    struct Bus {
        std::string name;
        std::vector<int> width_constraints;
        std::vector<Bit> bits;
    };

    struct Track {
        RoutedShape line;
        int width;
    };

    struct Parameters {
        int runtime, alpha, beta, gamma, delta, epsilon;
    };

    struct Input {
        Parameters parameters;
        Rectangle boundary;
        std::vector<Layer> layers;
        std::vector<Track> tracks;
        std::vector<Bus> buses;
        std::vector<RoutedShape> obstacles;
    };
}
