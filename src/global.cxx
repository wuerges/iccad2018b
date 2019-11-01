#include <global.hpp>

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
    res.p1.coords[0] = r.rect.p1.x;
    res.p1.coords[1] = r.rect.p1.y;
    res.p1.coords[2] = number_layer[r.layer];
    res.p2.coords[0] = r.rect.p2.x;
    res.p2.coords[1] = r.rect.p2.y;
    res.p2.coords[2] = number_layer[r.layer];
    return res;
}


void Router::build(const ast::Input & input) {

    router.parameters = input.parameters;
    router.boundary.p1.coords[0] = input.boundary.p1.x;
    router.boundary.p1.coords[1] = input.boundary.p1.y;
    router.boundary.p2.coords[0] = input.boundary.p2.x;
    router.boundary.p2.coords[1] = input.boundary.p2.y;

    init_number_layer(input);

    for(auto & i_obstacle : input.obstacles) {
        R3 obstacle = fromRoutedShape(i_obstacle);

        router.obstacle_index.Insert(
            obstacle.p1.coords.begin(), 
            obstacle.p2.coords.begin(), 
            &obstacle);

    }

    for(int i = 0; i < input.tracks.size(); ++i) {
        auto & i_track = input.tracks[i];        
        Track t;
        t.segment = fromRoutedShape(i_track.line);
        t.width = i_track.width;

        auto & lay = layers[t.segment.p1[2]];
        lay.tracks.push_back(t);        

        router.track_index.Insert(
            t.segment.p1.coords.begin(), 
            t.segment.p2.coords.begin(), 
            &lay.tracks.back());

    }

}

}