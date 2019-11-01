#pragma once

#include <ast.hpp>
#include <base.hpp>

#include <map>
#include <vector>

using std::map, std::vector, std::pair;

namespace base{

struct Track {
    R2 segment; // the rectangle for this track;
    vector<pair<int, Track*>> crossings; // the tracks that cross this track in the upper or lower layer
};

struct Layer {
    bool horizontal;
    vector<Track> tracks;
};

struct Router {
    // parameters should be variables here
    ast::Parameters parameters;
    R2 boundary;

    vector<Layer> layers;

};

Router router;

}