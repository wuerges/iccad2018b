#include <global.hpp>

namespace base {

R3 fromRoutedShape(const ast::RoutedShape & r) {
    R3 res;
    res.p1.coords[0] = r.rect.p1.x;
    res.p1.coords[1] = r.rect.p1.y;
    res.p1.coords[2] = r.layer;
    res.p2.coords[0] = r.rect.p2.x;
    res.p2.coords[1] = r.rect.p2.y;
    res.p2.coords[2] = r.layer;
    return res;
}


void build(const ast::Input & input) {

    router.parameters = input.parameters;
    router.boundary.p1.coords[0] = input.boundary.p1.x;
    router.boundary.p1.coords[1] = input.boundary.p1.y;
    router.boundary.p2.coords[0] = input.boundary.p2.x;
    router.boundary.p2.coords[1] = input.boundary.p2.y;

    for(auto & robstacle : input.obstacles) {
        R3 obstacle = fromRoutedShape(robstacle);

        router.obstacle_index.Insert(obstacle.p1.coords.begin(), obstacle.p2.coords.begin(), &obstacle);

    }

}

}