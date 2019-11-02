#include <global.hpp>
#include <astarwire.hpp>

namespace base {

void Router::init_number_layer(const ast::Input & input) {
    layers.resize(input.layers.size());
    for(uint32_t i = 0; i < input.layers.size(); ++i) {
        number_layer[input.layers[i].name] = i;
        layers[i].horizontal = input.layers[i].horizontal;
        layers[i].spacing = input.layers[i].spacing;
    }
}


R3 Router::fromRoutedShape(const ast::RoutedShape & r)  {
    R3 res;

    res.p1.coords[0] = std::min(r.rect.p1.x, r.rect.p2.x);
    res.p1.coords[1] = std::min(r.rect.p1.y, r.rect.p2.y);
    res.p1.coords[2] = number_layer[r.layer];

    res.p2.coords[0] = std::max(r.rect.p1.x, r.rect.p2.x);
    res.p2.coords[1] = std::max(r.rect.p1.y, r.rect.p2.y);
    res.p2.coords[2] = number_layer[r.layer];

    return res;
}

void Router::init_obstacles(const ast::Input & input) {
    for(auto & i_obstacle : input.obstacles) {
        obstacles.push_back(fromRoutedShape(i_obstacle));
        
        obstacle_index.Insert(
            obstacles.back().p1.coords.begin(), 
            obstacles.back().p2.coords.begin(), 
            &obstacles.back());

    }
}
void Router::init_tracks(const ast::Input & input) {
    std::cout << "Initializing tracks" << std::endl;

    for(int i = 0; i < input.tracks.size(); ++i) {
        auto & i_track = input.tracks[i];

        Track t;
        t.segment = fromRoutedShape(i_track.line);
        t.width = i_track.width;

        auto & lay = layers[t.segment.p1[2]];
        lay.tracks.push_back(t);

        track_index.Insert(
            t.segment.p1.coords.begin(), 
            t.segment.p2.coords.begin(), 
            &(lay.tracks.back()));
    }

    int max_collisions = 0;
    for(auto & layer : layers) {
        std::cout << "Initializing layer" << std::endl;

        
        for (auto & track : layer.tracks) {
            // std::cout << "." << std::flush;
            std::cout << ">>> Track ";
            std::cout << track.segment << std::endl;
            
            int number_of_collisions = 0;
            adjacentTracks(&track, [&](const Track * v) {
                std::cout << "  v: " << v->segment << std::endl;
                number_of_collisions++;
                return true;
            });            
            max_collisions = std::max(max_collisions, number_of_collisions);
        }

    }
    std::cout << "max_collisions = " << max_collisions << '\n';
}

void Router::adjacentTracks(const Track * u, std::function<bool(const Track*)> f) const {

    auto above = u->segment;
    auto bellow = u->segment;

    above.p1.coords[2]--;    
    above.p2.coords[2]--;    

    bellow.p1.coords[2]++;    
    bellow.p2.coords[2]++;    

    track_index.Search(
        above.p1.coords.begin(),
        above.p2.coords.begin(),
        f);
    track_index.Search(
        bellow.p1.coords.begin(),
        bellow.p2.coords.begin(),
        f);
}

void Router::build(const ast::Input & input) {

    parameters = input.parameters;
    boundary.p1.coords[0] = input.boundary.p1.x;
    boundary.p1.coords[1] = input.boundary.p1.y;
    boundary.p2.coords[0] = input.boundary.p2.x;
    boundary.p2.coords[1] = input.boundary.p2.y;

    // Layers must be initialized before evething else
    // because of layer numbering
    init_number_layer(input);

    init_obstacles(input);
    init_tracks(input);
}


void Router::route(const Track* from, const Track* to) {
    AStarWire w;
    Vertex v1{from, from->segment.p1};
    Vertex v2{to, to->segment.p2};

    std::cout << "pushing path" << std::endl;    
    paths.push_back(w.dijkstra(v1, v2));

    std::cout << "calc p.size() = " << paths.back().size() << std::endl;
    
}


void Router::global_routing(const ast::Input & input) {
    for(auto bus : input.buses) {
        for(auto bit : bus.bits) {
            if(bit.shapes.size() != 2) {
                std::cout << "bit with shapes != 2" << std::endl;
                // exit(-1);
            }
            auto shape1 = fromRoutedShape(bit.shapes[0]);
            auto shape2 = fromRoutedShape(bit.shapes[1]);

            Track* t1;
            track_index.Search(
                shape1.p1.coords.begin(), 
                shape1.p2.coords.begin(),
                [&t1](auto x) { t1 = x; return false; }
                );
            Track* t2;
            track_index.Search(
                shape2.p1.coords.begin(), 
                shape2.p2.coords.begin(),
                [&t2](auto x) { t2 = x; return false; }
                );
            std::cout << "track " << t1 << " --> " << t2 << std::endl;
            route(t1, t2);
        }
    }
}

}