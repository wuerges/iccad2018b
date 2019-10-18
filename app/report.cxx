#include <iostream>
#include <parser.hpp>

int main(int narg, char** argv) {
    using std::cout;
    using std::cin;

    if (narg<2) {
        cout << "Insuficient arguments, please use ./Report <csv|md>" << std::endl;
        return 1;
    }

    //csv|markdown
    std::string s = argv[1];
    if (s!="md" && s!="csv") {
        cout << "Unknown table style" << std::endl;
        return 1;
    }
    bool markdown = s=="md" ? true : false;
    if (markdown) {
        cout << "| Test case path | Boundary rectangle | Number of layers | Number of tracks | Number of buses | Number of bits in buses | Number of obstacles |\n";
        cout << "|----------------|--------------------|------------------|------------------|-----------------|-------------------------|---------------------|\n";
    }
    else {
        cout << "\"Test case path\",\"Boundary rectangle\",\"Number of layers\",\"Number of tracks\",\"Number of buses\",\"Number of bits in buses\",\"Number of obstacles\"\n";
    }

    char testcase[80];
    while (cin >> testcase) {
        auto result = parser::parse_file(testcase);
        if(result) {
            int layer_count;
            std::string boundary_rectangle;
            int track_count;
            int bus_count;
            int bit_count;
            int obstacles_count;

            layer_count = result->layers.size();
            boundary_rectangle = std::to_string(result->boundary.p2.x-result->boundary.p1.x) + 'x' + std::to_string(result->boundary.p2.y-result->boundary.p1.y);
            track_count = result->tracks.size();
            bus_count = result->buses.size();
            bit_count = 0;
            for (ast::Bus b:result->buses)
                bit_count += b.bits.size();
            obstacles_count = result->obstacles.size();

            if (markdown) {
                cout <<
                    "| " << testcase <<
                    " | " << boundary_rectangle <<
                    " | " << layer_count <<
                    " | " << track_count <<
                    " | " << bus_count <<
                    " | " << bit_count <<
                    " | " << obstacles_count << " |\n";
            }
            else {
                cout <<
                    '"' << testcase << "\"," <<
                    boundary_rectangle << ',' <<
                    layer_count << ',' <<
                    track_count << ',' <<
                    bus_count << ',' <<
                    bit_count << ',' <<
                    obstacles_count << '\n';
            }
        }
        else {
            cout << "Parser ERROR\n";
        }
    }

    return 0;
}