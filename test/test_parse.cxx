#include <parser.hpp>
#include <global.hpp>

#include <iostream>

int main(int narg, char** argv) {
    using std::cout;

    auto result = parser::parse_file(argv[1]);


    if(result) {
        cout << "Parser OK!\n";
        base::router().build(*result);    
        cout << "Build OK!\n";
    }
    else {
        cout << "Parser ERROR\n";
    }
}