#include <iostream>
#include <parser.hpp>

int main(int narg, char** argv) {
    using std::cout;

    auto result = parser::parse_file(argv[1]);

    if(result) {
        int layer_count;
        int track_count;
        int bus_count;
        int bit_count;
        int obstacles_count;

        layer_count = result->layers.size();
        track_count = result->tracks.size();
        bus_count = result->buses.size();
        bit_count = 0;
        for (ast::Bus b:result->buses)
            bit_count += b.bits.size();
        obstacles_count = result->obstacles.size();

        cout <<
            layer_count << ',' <<
            track_count << ',' <<
            bus_count << ',' <<
            bit_count << ',' <<
            obstacles_count << '\n';
    }
    else {
        cout << "Parser ERROR\n";
    }
}