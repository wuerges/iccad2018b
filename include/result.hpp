#pragma once

#include <ast.hpp>
#include <geometry.hpp>

#include <iostream>
#include <vector>

using std::ostream;


struct ResultShape {
    int layer;
    base::Rectangle<2> rect;

    friend std::ostream & operator<<(std::ostream &, const ResultShape &);
};

struct Result {

    using Path = std::pair<std::string, std::vector<ResultShape>>;
    using Bit = std::pair<std::string, Path>;
    using Bus = std::pair<std::string, std::vector<Bit>>;
    


    std::vector<Bus> buses;

    friend ostream & operator<<(ostream &, const Result &);

};
