#include <iostream>
#include <parser.hpp>

int main(int narg, char** argv) {
    using std::cout;
    using std::cin;

    //csv|markdown
    std::string s = argv[1];
    bool markdown = s=="markdown" ? true : false;
    if (markdown) {
        cout << "| Test case path | Number of layers | Number of tracks | Number of buses | Number of bits in buses | Number of obstacles |\n";
        cout << "|----------------|------------------|------------------|-----------------|-------------------------|---------------------|\n";
    }
    else {
        cout << "\"Test case path\",\"Number of layers\",\"Number of tracks\",\"Number of buses\",\"Number of bits in buses\",\"Number of obstacles\"\n";
    }

    char testcase[80];
    while (cin >> testcase) {
        auto result = parser::parse_file(testcase);
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

            if (markdown) {
                cout <<
                    "| " << testcase <<
                    " | " << layer_count <<
                    " | " << track_count <<
                    " | " << bus_count <<
                    " | " << bit_count <<
                    " | " << obstacles_count << " |\n";
            }
            else {
                cout <<
                    '"' << testcase << "\"," <<
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
}