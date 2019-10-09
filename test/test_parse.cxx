#include <iostream>
#include <parser.hpp>

int main(int narg, char** argv) {
    using std::cout;


    if(parse_file(argv[1])) {
        cout << "linked parser!\n";
    }
    cout << "Hello World\n";
}