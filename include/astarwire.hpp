#pragma once

#include <global.hpp>
#include <geometry.hpp>

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

struct Vertex {
    const Track * track;
    const P3 origin;
    const P3 gcell;

    Vertex(const Track * track, const P3 & origin, const P3 & gcell)
    : track(track), origin(origin), gcell(gcell) {}

    bool horizontal() const {
        return track->segment.p1[0] == track->segment.p2[0];
    }

    std::optional<Vertex> move_gcell(int step) const {
        P3 gcell_up = gcell;
        P3 origin_up = origin;

        int c = horizontal() ? 1 : 0;
        gcell_up.coords[c] += step;
        origin_up.coords[c] += step;

        if(intersection(R3{origin_up, origin_up}, track->segment)) {
            return Vertex(track, origin_up, gcell_up);
        }
        return std::nullopt;
    }


    void neighbors(function<void(const Vertex&)> f) const {
        const R3 & seg = track->segment;
        // std::cout << seg << std::endl;
        // std::cout << "neighboors of " << track->segment << std::endl;
        // std::cout << "Address of router: " << &base::router() << std::endl;
        
        // R3 window = track->segment;

        // if horizontal
        auto up = move_gcell(-50);
        auto down = move_gcell(50);

        if(up) {
            f(*up);
        }
        if(down) {
            f(*down);
        }

        auto window = intersection(square_around(gcell), track->segment);
        // std::optional<R3> window = track->segment;
        if(window) {
            base::router().adjacentTracks(*window, [&seg,f,this](const Track * tv){
                // std::cout << "adjacent!!!!!" << std::endl;
                // std::cout << tv->segment << std::endl;


                int nz = tv->segment.p1[2];
                auto cp = base::crossing(tv->segment, seg);
                cp.coords[2] = nz;
                auto gc = gcell;
                gc.coords[2] = nz;
                Vertex v(tv, cp, gc);
                f(v);
                return true;
            });
        }
    }

    friend bool operator<(const Vertex & v1, const Vertex & v2) {
        if(v1.origin != v2.origin) {
            return v1.origin < v2.origin;
        }
        if(v1.gcell != v2.gcell) {
            return v1.gcell < v2.gcell;
        }
        return *v1.track < *v2.track;
    }

    friend std::ostream & operator<<(std::ostream & out, const Vertex & v) {
        out << "Vertex(track=" << v.track->segment << ",origin=" << v.origin << ",gcell="<<v.gcell<<")";
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
        // std::cout << "Dikstra for " << s << " " << t << std::endl;

        map<Vertex, int> dist;
        map<const Vertex, const Vertex> parent;
        
        set<Link> pq;
        dist[s] = 0;
        // std::cout << "Insert into pq: " << s << std::endl;
        pq.insert(Link(0, s));
        bool found = false;


        while(!pq.empty()) {
            const Vertex u = pq.begin()->second;
            pq.erase(pq.begin());

            // std::cout<< "taking from pq: " << u << std::endl;
            // std::cout << "pq.size() " << pq.size() << std::endl;

            if(distance(t.track->segment, u.track->segment) == 0) {
                // std::cout << "Found!" << std::endl;
                // std::cout << "t=" << t << std::endl;
                // std::cout << "u=" << u << std::endl;
                // std::cout << "distance=" << distance(t.track->segment, u.track->segment) << std::endl;

                parent.insert(std::make_pair(t, u));                
                found = true;
                break;
            }
            // std::cout << "\nNeighbors" << std::endl;
            u.neighbors([&dist, &pq, &parent, u, t](auto & v) {
                // std::cout << "n[u]: v = " << v << std::endl;
                
                int w = distance(u, v);
                int du = dist[u];
                if(dist.find(v) == dist.end()) {
                    dist[v] = INF;
                }
                int & dv = dist[v];

                if(dv > du + w) {

                    int h = distance(v, t);

                    // std::cout << "adding to pq = " << v << std::endl;
                    pq.erase(Link(dv+h, v));
                    dv = du + w;
                    pq.insert(Link(dv+h, v));
                    parent.erase(v);
                    parent.emplace(v,u);
                }
                return true;
            });                
        }

        vector<P3> path;

        path.push_back(t.origin);
        const Vertex * e = &t;        
        // std::cout << "E=" << *e << std::endl;
            
        while(parent.find(*e) != parent.end()) {
            auto it = parent.find(*e);
            // const R3 & seg = it->first.track->segment;

            if(it->first.track->segment != it->second.track->segment) {
                auto p = base::crossing(
                    it->first.track->segment,
                    it->second.track->segment);
                path.push_back(p);
                // std::cout<< "crossing A: " << it->first.track->segment  << std::endl;
                // std::cout<< "crossing B: " << it->second.track->segment  << std::endl;
                // std::cout<< "crossing X: " << p << std::endl;
            }


            e = &it->second;
            // std::cout << "E=" << *e << std::endl;
        }
        path.push_back(e->origin);

        
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