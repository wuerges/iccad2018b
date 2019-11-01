#pragma once

#include <ast.hpp>
#include <base.hpp>

#include <RTree.h>

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
    vector<Track> tracks;

    rtree::RTree<Track*, uint32_t, 3, double> track_index;
    rtree::RTree<R3*, uint32_t, 3, double> obstacle_index;

};

Router router;

void build(const ast::Input & input);

}