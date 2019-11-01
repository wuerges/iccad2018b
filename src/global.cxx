#include <global.hpp>

namespace base {

void build(Router & r, const ast::Input & input) {

    r.parameters = input.parameters;
    r.boundary.p1.coords[0] = input.boundary.p1.x;
    r.boundary.p1.coords[1] = input.boundary.p1.y;
    r.boundary.p2.coords[0] = input.boundary.p2.x;
    r.boundary.p2.coords[1] = input.boundary.p2.y;

}

}