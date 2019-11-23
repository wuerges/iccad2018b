#pragma once

#include <ast.hpp>
#include <geometry.hpp>

#include <RTree.h>

#include <map>
#include <vector>

using std::map;
using std::vector;
using std::pair;

namespace base {
    using namespace geometry;

struct Track {
    R3 segment; // the rectangle for this track;
    int width;
    friend bool operator<(const Track & t1, const Track & t2) {
        if (t1.width != t2.width) {
            return t1.width < t2.width;
        }
        return t1.segment < t2.segment;
    }
};

struct Layer {
    bool horizontal;
    int spacing;
    vector<Track> tracks;
};

struct Router {
    // parameters should be variables here
    ast::Parameters parameters;
    R2 boundary;

    vector<Layer> layers;

    rtree::RTree<Track*, int, 3, double> track_index;
    void adjacentTracks(const R3 &, std::function<bool(const Track*)>) const;

    rtree::RTree<R3*, int, 3, double> obstacle_index;

    map<std::string, int> number_layer;
    void init_number_layer(const ast::Input & input);
    void init_tracks(const ast::Input & input);
    
    vector<R3> obstacles;
    void init_obstacles(const ast::Input & input);

    void build(const ast::Input & input);

    R3 fromRoutedShape(const ast::RoutedShape & r) ;


    vector<vector<P3>> paths;
    void route(const Track* from, const Track* to);
    void global_routing(const ast::Input & input);

    static Router& router()
    { 
        static Router r; // initialized once due to being static
        return r;
    }
};

static Router & router() {
    return Router::router();
}

}