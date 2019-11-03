#include <solver.hpp>
#include <global.hpp>
#include <astar.hpp>

#include <iostream>
using namespace std;

Result solve(const ast::Input & input) {
    Result r;


    base::router().build(input);
    base::router().global_routing(input);

    // TODO build global circuit representation

    // AStar astar;

    // auto routes = astar.globalRoute();


    // DEBUG

    // cout << "Routing:" << endl;

    // for(auto & l : base::router().layers) {
    //     for(auto & t : l.tracks) {
    //         base::router().route(
    //             &t,
    //             &base::router().layers.front().tracks.front());
    //     }
    // }

    // TODO Build result from routes

    return r;
}