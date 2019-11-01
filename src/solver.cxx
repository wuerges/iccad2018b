#include <solver.hpp>
#include <global.hpp>
#include <astar.hpp>

Result solve(const ast::Input & input) {
    Result r;
    r.build(input);

    // TODO build global circuit representation

    AStar astar;

    auto routes = astar.globalRoute();

    // TODO Build result from routes

    return r;
}