#pragma once

#include <ast.hpp>
#include <base.hpp>

#include <RTree.h>

#include <map>
#include <vector>

using std::map, std::vector, std::pair;

namespace base {

struct Track {
    R3 segment; // the rectangle for this track;
    int width;
    vector<pair<int, Track*>> crossings; // the tracks that cross this track in the upper or lower layer
};

struct Layer {
    bool horizontal;
    uint32_t spacing;
    vector<Track> tracks;
};

struct Router {
    // parameters should be variables here
    ast::Parameters parameters;
    R2 boundary;

    vector<Layer> layers;

    rtree::RTree<Track*, uint32_t, 3, double> track_index;
    rtree::RTree<R3*, uint32_t, 3, double> obstacle_index;

    map<std::string, int> number_layer;
    void init_number_layer(const ast::Input & input);
    void init_tracks(const ast::Input & input);
    void init_obstacles(const ast::Input & input);

    void build(const ast::Input & input);

    R3 fromRoutedShape(const ast::RoutedShape & r) ;
};

static Router& router()
{ 
    static Router r; // initialized once due to being static
    return r;
}

}