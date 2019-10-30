#include <parser.hpp>

#include <iostream>
#include <vector>
#include <functional>
#include <filesystem>

using namespace ast;
using ss = std::ostream;
using std::cout, std::cin;
using std::vector, std::pair, std::string;
using std::max;
using std::function;


void boundary_rectangle(ss & out, const Input& result) {
    int dx = result.boundary.p2.x - result.boundary.p1.x;
    int dy = result.boundary.p2.y - result.boundary.p1.y;
    out << dx << 'x' << dy;
}

void number_of_layers(ss & out, const Input& result) {
    out << result.layers.size();
}

void number_of_tracks(ss & out, const Input& result) {
    out << result.tracks.size();
}

void number_of_buses(ss & out, const Input& result) {
    out << result.buses.size();
}

void number_of_bits(ss & out, const Input& result) {
    int bit_count = 0;
    for (const Bus & b:result.buses) {
        bit_count += b.bits.size();
    }
    out << bit_count;
}

void maximum_pin_shapes(ss & out, const Input& result) {
    size_t max_pin_shape = 0;
    for (const Bus & b:result.buses) {
        max_pin_shape = max(max_pin_shape, b.bits[0].shapes.size());
    }
    out << max_pin_shape;
}

void maximum_bits(ss & out, const Input& result) {
    size_t max_number_bits = 0;
    for (const Bus & b:result.buses) {
        max_number_bits = max(max_number_bits, b.bits.size());
    }
    out << max_number_bits;
}

void number_of_obstacles(ss & out, const Input& result) {   
    out << result.obstacles.size();
}


const vector<pair<string, function<void(ss&, const Input&)>>> columns = {
    {"Boundary rectangle", boundary_rectangle},
    {"Number of layers", number_of_layers},
    {"Number of tracks", number_of_tracks},
    {"Number of buses", number_of_buses},
    {"Number of bits in buses",  number_of_bits},
    {"Maximum number of pin shapes", maximum_pin_shapes},
    {"Maximum number of bits per bus", maximum_bits},
    {"Number of obstacles", number_of_obstacles}        
};

void fix_path(ss & out, const string & path) {
    out << std::filesystem::path(path).filename().string();
}

int main(int narg, char** argv) {

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
        cout << "| Test case path |";
        for(auto & [n, _] : columns) {
            cout << " " << n << " |";
        }
        cout << std::endl;
        cout << "|:----|";
        for(auto & [n, _] : columns) {
            cout << "----:|";            
        }
        cout << std::endl;
    }
    else {
        cout << "\"Test case path\"";
        for(auto & [n, _] : columns) {
            cout << ",\"" << n << "\"";
        }
        cout << std::endl;
    }

    std::string testcase;
    while (cin >> testcase) {

        auto result = parser::parse_file(testcase.c_str());
        if(result) {

            if(markdown) {
                cout << "| "; fix_path(cout, testcase); cout << " |";
                for(auto & [_, f] : columns) {
                    cout << " ";
                    f(cout, *result);
                    cout << " |";
                }
                cout << std::endl;
            }
            else {
                cout << "\""; fix_path(cout, testcase); cout << "\"";
                for(auto & [_, f] : columns) {
                    cout << ",";
                    f(cout, *result);
                }
                cout << std::endl;
            }
        }
        else {
            cout << "Parser ERROR\n";
            return -1;
        }
    }

    return 0;
}