#include <parser.hpp>

#include <iostream>

using namespace ast;


void boundary_rectangle(stringstream & ss, const Input& result) {
    int dx = result.boundary.p2.x - result.boundary.p1.x;
    int dy = result.boundary.p2.y - result.boundary.p1.y;
    ss << dx << 'x' << dy;
}

void number_of_layers(stringstream & ss, const Input& result) {
    ss << result.layers.size();
}

void number_of_tracks(stringstream & ss, const Input& result) {
    ss << result.tracks.size();
}

void number_of_buses(stringstream & ss, const Input& result) {
    ss << result.buses.size();
}

void number_of_bits(stringstream & ss, const Input& result) {
    int bit_count = 0;
    for (const Bus & b:result->buses) {
        bit_count += b.bits.size();
    }
    ss << bit_count;
}

void number_of_bits(stringstream & ss, const Input& result) {
    int max_pin_shape = 0;
    for (const Bus & b:result->buses) {
        max_pin_shape = max(max_pin_shape, b.bits[0].shapes.size());
    }
    ss << max_pin_shape;
}

void number_of_bits(stringstream & ss, const Input& result) {
    int max_number_bits = 0;
    for (const Bus & b:result->buses) {
        max_number_bits = max(max_number_bits, b.bits.size());
    }
    ss << max_number_bits;
}

void number_of_obstacles(stringstream & ss, const Input& result) {   
    ss << result.obstacles.size();
}



int main(int narg, char** argv) {
    using std::cout;
    using std::cin;
    using std::max;

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
        cout << "| Test case path | Boundary rectangle | Number of layers | Number of tracks | Number of buses | Number of bits in buses | Maximum number of pin shapes | Maximum number of bits per bus | Number of obstacles |\n";
        cout << "|----------------|--------------------|------------------|------------------|-----------------|-------------------------|------------------------------|--------------------------------|---------------------|\n";
    }
    else {
        cout << "\"Test case path\",\"Boundary rectangle\",\"Number of layers\",\"Number of tracks\",\"Number of buses\",\"Number of bits in buses\",\"Maximum number of pin shapes\",\"Maximum number of bits per bus\",\"Number of obstacles\"\n";
    }

    char testcase[80];
    while (cin >> testcase) {
        auto result = parser::parse_file(testcase);
        if(result) {
            int layer_count;
            std::string boundary_rectangle;
            int track_count;
            int bus_count;
            size_t max_pin_shape = 0;
            size_t max_number_bits = 0;
            int bit_count;
            int obstacles_count;

            layer_count = result->layers.size();
            boundary_rectangle = std::to_string(result->boundary.p2.x-result->boundary.p1.x) + 'x' + std::to_string(result->boundary.p2.y-result->boundary.p1.y);
            track_count = result->tracks.size();
            bus_count = result->buses.size();
            bit_count = 0;
            for (const Bus & b:result->buses) {
                bit_count += b.bits.size();
                max_pin_shape = max(max_pin_shape, b.bits[0].shapes.size());
                max_number_bits = max(max_number_bits, b.bits.size());
            }
            obstacles_count = result->obstacles.size();

            if (markdown) {
                cout <<
                    "| " << testcase <<
                    " | " << boundary_rectangle <<
                    " | " << layer_count <<
                    " | " << track_count <<
                    " | " << bus_count <<
                    " | " << bit_count <<
                    " | " << max_pin_shape <<
                    " | " << max_number_bits <<
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
                    max_pin_shape << ',' <<
                    max_number_bits << ',' <<
                    obstacles_count << '\n';
            }
        }
        else {
            cout << "Parser ERROR\n";
        }
    }

    return 0;
}