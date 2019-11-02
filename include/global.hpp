#pragma once

#include <ast.hpp>
#include <base.hpp>

#include <RTree.h>

#include <map>
#include <vector>

using std::map;
using std::vector;
using std::pair;

namespace base {

struct Track {
    R3 segment; // the rectangle for this track;
    int width;
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
    void adjacentTracks(const Track *, std::function<bool(const Track*)>) const;

    rtree::RTree<R3*, uint32_t, 3, double> obstacle_index;

    map<std::string, int> number_layer;
    void init_number_layer(const ast::Input & input);
    void init_tracks(const ast::Input & input);
    
    vector<R3> obstacles;
    void init_obstacles(const ast::Input & input);

    void build(const ast::Input & input);

    R3 fromRoutedShape(const ast::RoutedShape & r) ;


    vector<vector<P3>> paths;
    void route(const Track* from, const Track* to);
};

static Router& router()
{ 
    static Router r; // initialized once due to being static
    return r;
}

}