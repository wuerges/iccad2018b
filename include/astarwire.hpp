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
        std::cout << seg << std::endl;
        base::router().adjacentTracks(track, [&seg,f](const Track * tv){
            std::cout << "adjacent!!!!!" << std::endl;
            std::cout << tv->segment << std::endl;

            Vertex v{tv, base::crossing(tv->segment, seg)};
            f(v);
            return true;
        });
    }

    friend bool operator<(const Vertex & v1, const Vertex & v2) {
        if(v1.track < v2.track) return true;
        return v1.origin < v2.origin;
    }

    friend std::ostream & operator<<(std::ostream & out, const Vertex & v) {
        out << "Vertex(track=" << v.track->segment << ",origin=" << v.origin << ")";
        return out;
    }

};

const int INF = 1e9;

int distance(const Vertex & v1, const Vertex & v2) {
    return base::distance(v1.origin, v2.origin);
}

struct AStarWire {
    
    using Link = pair<int, Vertex>;
    
    vector<base::P3> dijkstra(const Vertex s, const Vertex t) {
        std::cout << "Dikstra for " << s << " " << t << std::endl;

        map<Vertex, int> dist;
        map<Vertex, Vertex> parent;
        
        set<Link> pq;
        dist[s] = 0;
        std::cout << "Insert into pq: " << s << std::endl;
        pq.insert(Link(0, s));
        bool found = false;

        while(!pq.empty()) {
            const Vertex u = pq.begin()->second;
            pq.erase(pq.begin());

            std::cout<< "taking from pq: " << u << std::endl;
            std::cout << "pq.size() " << pq.size() << std::endl;

            if(distance(t.track->segment, u.track->segment) == 0) {
                std::cout << "Found!" << std::endl;
                std::cout << t << std::endl;
                std::cout << u << std::endl;
                std::cout << "distance=" << distance(t.track->segment, u.track->segment) << std::endl;
                parent.emplace(t, u);
                found = true;
                break;
            }
            std::cout << "\nNeighbors" << std::endl;
            u.neighbors([&dist, &pq, &parent, u](auto & v) {
                std::cout << "n[u]: v = " << v << std::endl;
                
                int w = distance(u, v);
                int du = dist[u];
                if(dist.find(v) == dist.end()) {
                    dist[v] = INF;
                }
                int & dv = dist[v];

                if(dv > du + w) {
                    std::cout << "adding to pq = " << v << std::endl;
                    pq.erase(Link(dv, v));
                    dv = du + w;
                    pq.insert(Link(dv, v));
                    parent.erase(v);
                    parent.emplace(v,u);
                }
                return true;
            });                
        }

        vector<P3> path;
        if(found) {
            path.push_back(t.origin);
            const Vertex * e = &t;
            while(parent.find(*e) != parent.end()) {
                e = &parent.find(*e)->second;
                path.push_back(e->origin);
            }
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