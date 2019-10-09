#include <iostream>
#include <parser.hpp>

int main(int narg, char** argv) {
    using std::cout;

    auto result = parser::parse_file(argv[1]);

    if(result) {
        cout << "Parser OK!\n";
    }
    else {
        cout << "Parser ERROR\n";
    }
}