#pragma once

#include <global.hpp>
#include <geometry.hpp>
#include <rtree_queue.hpp>

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
using geometry::P3;
using geometry::R3;
using geometry::RTreeQueueFilter;

// namespace {


R3 extrude( const R3 & r) {
    R3 copy = r;
    copy.p1.coords[2]--;
    copy.p2.coords[2]++;
    return copy;
}

struct Vertex {

    const Track * track;
    const P3 origin;
    const R3 target;
    geometry::RTreeQueueFilter<3, Track> queue;

    Vertex(const Track * track, const P3 & origin, const R3 & target)
    : track(track)
    , origin(origin)
    , target(target)
    , queue(extrude(track->segment), target, base::router().track_index) {}

    bool horizontal() const {
        return track->segment.p1[0] == track->segment.p2[0];
    }

    bool empty() const {
        return queue.empty();
    }

    Vertex next_neighbor() {
        auto v = queue.pop();
        auto c = crossing(track->segment, v->segment);
        c.coords[2] = v->segment.p1[2];
        return Vertex(v, c, target);
    }

    friend bool operator<(const Vertex & v1, const Vertex & v2) {
        if(v1.origin != v2.origin) {
            return v1.origin < v2.origin;
        }
        return *v1.track < *v2.track;
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

// }

struct AStarWireRTQ {
    
    vector<base::P3> dijkstra(const Vertex s, const R3 t) {
        // std::cout << "Dikstra for " << s << " " << t << std::endl;

        map<Vertex, int> dist;
        map<const R3, const R3> parent;
        
        multimap<int, Vertex> pq;
        dist[s] = 0;
        // std::cout << "Insert into pq: " << s << std::endl;
        pq.emplace(0, s);
        bool found = false;


        while(!pq.empty()) {
            Vertex & u = pq.begin()->second;

            // std::cout<< "taking from pq: " << u << std::endl;
            // std::cout << "pq.size() " << pq.size() << std::endl;
            std::cout << "distance=" << distance(t, u.track->segment) << std::endl;

            if(distance(t, u.track->segment) == 0) {
                std::cout << "Found!" << std::endl;
                // std::cout << "t=" << t << std::endl;
                // std::cout << "u=" << u << std::endl;

                parent.insert(std::make_pair(t, u.track->segment));                
                found = true;
                break;
            }
            
            if(u.empty()){
                pq.erase(pq.begin());
                continue;
            }

            Vertex v = u.next_neighbor();

            int du = dist[u];
            if(dist.find(v) == dist.end()) {
                dist[v] = INF;
            }
            int & dv = dist[v];
            
            int w = distance(u, v);

            if(dv > du + w) {

                int h = distance(v.origin, t);

                // std::cout << "adding to pq = " << v << std::endl;
                // pq.erase(Link(dv+h, v));
                dv = du + w;
                pq.emplace(dv+h, v);
                parent.erase(v.track->segment);
                parent.emplace(v.track->segment,u.track->segment);
            }
        }

        vector<P3> path;

        path.push_back(t.p1);
        R3 e = t;
        // std::cout << "E=" << *e << std::endl;
            
        while(parent.count(e) > 0) {
            auto it = parent.find(e);
            // const R3 & seg = it->first.track->segment;

            if(it->first == it->second) {
                break;
            }
            auto p = base::crossing(
                it->first,
                it->second);
            path.push_back(p);


            e = it->second;

            
            // std::cout << "E=" << *e << std::endl;
        }
        path.push_back(e.p1);

        
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