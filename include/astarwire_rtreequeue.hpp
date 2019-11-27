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

    vector<base::P3> detailed_route(const R3 & s, const R3 & t) {
        Track * from;
        base::router().track_index.Search(s.p1.coords.begin(), s.p2.coords.begin(), [&from](auto t){
            from = t;
            return false;
        });

        // TODO need to improve this, to select exterior point.
        auto origin_rect = intersection(s, from->segment);

        Vertex source(from, origin_rect->p1, t);

        // std::cout << "FROM1:" << from->segment << std::endl;
        // std::cout << "FROM2:" << s << std::endl;
        // std::cout << "FROM3:" << *origin_rect << std::endl;
        return dijkstra(source, t);
    }
    
    vector<base::P3> dijkstra(const Vertex s, const R3 t) {
        // std::cout << "Dikstra for " << s << " " << t << std::endl;
        double tiebreak = 1.2;

        map<Vertex, int> dist;
        map<const P3, const P3> parent;
        
        multimap<int, Vertex> pq;
        dist[s] = 0;
        // std::cout << "Insert into pq: " << s << std::endl;
        pq.emplace(distance(s.track->segment, t)*tiebreak, s);
        bool found = false;

        P3 p_dest;
        R3 r_dest;

        while(!pq.empty()) {
            // std::cout << "while pq.empty()?" << std::endl;
            Vertex & u = pq.begin()->second;

            // std::cout<< "taking from pq: " << u << std::endl;
            // std::cout << "pq.size() " << pq.size() << std::endl;
            // std::cout << "distance=" << distance(t, u.track->segment) << std::endl;

            if(collides(t, u.track->segment)) {
                p_dest = u.origin;
                r_dest = u.track->segment;
                // std::cout << "Found!" << std::endl;
                // std::cout << "u.track->segment" << u.track->segment << std::endl;
                // std::cout << "parent? " << parent.count(u.track->segment) << std::endl;
                // std::cout << "t=" << t << std::endl;
                // std::cout << "u=" << u << std::endl;

                // parent.emplace(t, u.track->segment);
                found = true;
                break;
            }
            
            if(u.empty()){
                pq.erase(pq.begin());
                continue;
            }

            Vertex v = u.next_neighbor();
            if(v.track == u.track) {
                continue;
            }
            // std::cout << "next neighboor?" <<std::endl;

            int du = dist[u];
            if(dist.find(v) == dist.end()) {
                dist[v] = INF;
            }
            int & dv = dist[v];
            
            int w = distance(u, v);

            if(dv > du + w) {

                int h = distance(v.origin, t);
                h *= tiebreak;

                // std::cout << "adding to pq = " << v << std::endl;
                // pq.erase(Link(dv+h, v));
                dv = du + w;
                pq.emplace(dv+h, v);
                parent.erase(v.origin);
                parent.emplace(v.origin, u.origin);
                // std::cout << "parent["<<v.track->segment<<"]=" << u.track->segment <<std::endl;
            }
        }

        vector<P3> path;
        if(!found) return path;

        // std::cout << "ORIGIN=" << s.origin << '\n';
        // std::cout << "TARGET=" << t << '\n';

        auto plast = intersection(r_dest, t);
        path.push_back(plast->p1);
        path.push_back(p_dest);
        
        P3 e = p_dest;
        // std::cout << "E=" << *e << std::endl;


        // std::cout << "Backtracking route" << std::endl;
        while(!collides(e, s.track->segment)) {
            auto it = parent.find(e);
            // std::cout << "Backstep:" << e << std::endl;
            // const R3 & seg = it->first.track->segment;

            if(it->first == it->second) {
                break;
            }
            // auto p1 = base::crossing(
            //     it->first,
            //     it->second);

            // auto p2 = p1;
            // p2.coords[2] = it->first.p1[2];
            // p1.coords[2] = it->second.p1[2];

            e = it->second;
            
            path.push_back(e);
            // path.push_back(p1);



            
            // std::cout << "E=" << *e << std::endl;
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