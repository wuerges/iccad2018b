#pragma once

#include <base.hpp>
#include <global.hpp>

#include <set>
#include <map>
#include <vector>
#include <functional>
#include <cassert>


using std::vector, std::set, std::pair, std::map, std::function;

// For horizontal layers, Front -> East, Back -> West
// For vertical layers Front -> South, Back -> North
enum class Direction {
    Neutral,
    Front, 
    Back
};

struct Vertex {
    using D = Direction;
    
    // The direction of this vertex.
    D direction;
    // The layer of this vertex.
    int layer;
    // The indexes of this vertex.
    // each index represents a different wire.
    vector<int> points;

    Vertex() {}
    Vertex(const D d, const int l, const vector<int> pts): 
        direction(d), layer(l), points(pts) {}

    void neighbors(function<void(const Vertex&)> f) const {        
        // If a Vertex is neutral, it may either:
        // 1. change layer, and remain neutral.
        //    - must check if wire width constraint.
        // 2. choose a direction and move all.
        
        // If a Vertex is not neutral, it may either:        
        // 1. change layer and become neutral.
        //    - must check if wire width constraint.
        // 2. move one wire.
        //    - a wire can only move if the next wire is ahead.
    }

    void step(int & x) const {
        assert(direction != D::Neutral);
        if(direction == D::Front) {
            x++;
        }
        else {
            x--;
        }
    }

    Vertex moveAll() const {
        Vertex r(direction, layer, points);
        for(int & p: r.points) {
            step(p);
        }
        return r;
    }

    vector<Vertex> move1() const {
        vector<Vertex> res;
        for(int p = 0; p < points.size()-1; ++p) {
            if(points[p+1] > points[p]) {
                res.push_back(*this);
                step(res.back().points[p]);
            }
        }
        res.push_back(*this);
        step(res.back().points.back());
        return res;
    }

    bool valid() const {
        // Check if position is valid.
        // p >=0 and p < ortogonal_tracks.size();
        // TODO
        return true;
    }

    friend bool operator<(const Vertex & v1, const Vertex & v2) {
        return v1.direction < v2.direction
            || v1.layer < v2.layer
            || v1.points < v2.points;
    }

};

const int INF = 1e9;

int distance(const Vertex & v1, const Vertex & v2) {
    // TODO
    return INF;
}

struct AStar {

    using Link = pair<int, Vertex>;
    
    vector<Vertex> dijkstra(const Vertex s, const Vertex t) {
        map<Vertex, int> dist;

        map<Vertex, Vertex> parent;
        set<Link> pq;
        dist[s] = 0;
        pq.insert(Link(0, s));
        while(!pq.empty()) {
            const Vertex u = pq.begin()->second;
            pq.erase(pq.begin());
            u.neighbors([&dist, &pq, &parent, u](auto & v) {
                int w = distance(u, v);
                int du = dist[u];
                if(dist.find(v) == dist.end()) {
                    dist[v] = INF;
                }
                int & dv = dist[v];

                if(dv > du + w) {
                    pq.erase(Link(dv, v));
                    dv = du + w;
                    parent[v] = u;
                }
            });                
        }

        vector<Vertex> path;
        path.push_back(t);
        auto e = t;
        while(parent.find(e) != parent.end()) {
            e = parent[e];
            path.push_back(e);
        }
        return path;
    }

    vector<vector<Vertex>> globalRoute() {
        vector<vector<Vertex>> result;
        vector<pair<Vertex, Vertex>> buses;

        // TODO build the vertices for the buses


        for(auto [s, t] : buses) {
            result.push_back(dijkstra(s, t));
        }
        return result;
    }

};