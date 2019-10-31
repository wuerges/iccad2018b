#pragma once

#include <base.hpp>

#include <set>
#include <vector>
#include <functional>
#include <cassert>


using std::vector, std::set, std::pair;

// For horizontal layers, Front -> East, Back -> West
// For vertical layers Front -> South, Back -> North
enum class Direction {
    Neutral,
    Front, 
    Back
};

struct Vertex {
    using Front = Direction::Front;
    using Back = Direction::Back;
    using Neutral = Direction::Neutral;
    
    // The direction of this vertex.
    const Direction direction;
    // The layer of this vertex.
    const int layer;
    // The indexes of this vertex.
    vector<int> points;

    Vertex(const Direction d, const int l, const vector<int> pts): 
        direction(d), layer(l), points(pts) {}

    void neighbors(function<void(const Vertex&)>&f ) {        
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
        assert(direction != Neutral);
        if(direction == Front) {
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
    }

    vector<Vertex> move1() const {
        vector<Vertex> res;
        for(int p = 0; p < points.size()-1; ++p) {
            if(ahead(points[p+1], points[p]) {
                res.push_back(*this);
                step(res.back().points[p]);
            }
        }
        res.push_back(*this);
        step(res.back().points.back());
    }

    bool valid() const {
        // Check if position is valid.
        // p >=0 and p < ortogonal_tracks.size();
        return true;
    }

};

struct AStar {

    using Vertex = 

    vector<ii> adjList[MAXN];
    
    int dijkstra(int s, int t, int n, int dist[]) {
        for(int i = 1; i <= n; i++) dist[i] = INF;
        set<ii> pq;
        dist[s] = 0;
        pq.insert(ii(0, s));
        while(!pq.empty()) {
            int u = pq.begin()->second;
            pq.erase(pq.begin());
            for(int i=0; i<(int)adjList[u].size(); i++) {
                int v = adjList[u][i].second;
                int w = adjList[u][i].first;
                if (dist[v] > dist[u] + w) {
                    pq.erase(ii(dist[v], v));
                    dist[v] = dist[u] + w;
                    pq.insert(ii(dist[v], v));
                }
            }
        }
        return dist[t];
    }

};