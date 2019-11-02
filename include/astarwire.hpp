#pragma once

#include <base.hpp>
#include <global.hpp>

#include <set>
#include <map>
#include <vector>
#include <functional>
#include <cassert>


using std::vector; 
using std::set;
using std::pair;
using std::map; 
using std::function;
using base::Track;
using base::P3;
using base::R3;

struct Vertex {
    const Track * track;
    const P3 origin;

    void neighbors(function<void(const Vertex&)> f) const {
        const R3 & seg = track->segment;
        base::router().adjacentTracks(track, [&seg,f](const Track * tv){

            Vertex v{tv, base::crossing(tv->segment, seg)};
            f(v);
            return true;
        });
    }

    friend bool operator<(const Vertex & v1, const Vertex & v2) {
        if(v1.track < v2.track) return true;
        return v1.origin < v2.origin;
    }

};

const int INF = 1e9;

uint32_t distance(const Vertex & v1, const Vertex & v2) {
    return base::distance(v1.origin, v2.origin);
}

struct AStarWire {
    
    using Link = pair<int, Vertex>;
    
    vector<base::P3> dijkstra(const Vertex s, const Vertex t) {
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
                    parent.erase(v);
                    parent.emplace(v,u);
                }
                return true;
            });                
        }

        vector<P3> path;
        path.push_back(t.origin);
        const Vertex * e = &t;
        while(parent.find(*e) != parent.end()) {
            e = &parent.find(*e)->second;
            path.push_back(e->origin);
        }
        return path;
    }

    // vector<vector<Vertex>> globalRoute() {
    //     vector<vector<Vertex>> result;
    //     vector<pair<Vertex, Vertex>> buses;

    //     // TODO build the vertices for the buses


    //     for(auto [s, t] : buses) {
    //         result.push_back(dijkstra(s, t));
    //     }
    //     return result;
    // }

};