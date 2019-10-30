#include <parser.hpp>

#include <iostream>
#include <vector>
#include <functional>

using namespace ast;
using ss = std::ostream;
using std::cout, std::cin, std::cerr;
using std::vector, std::pair, std::string;
using std::max;
using std::function;




int main(int narg, char** argv) {

    if (narg < 2) {
        cerr << "usage: " << argv[0] << " <testcase>" << std::endl;
        return -1;
    }    

    auto result = parser::parse_file(argv[1]);
    if(result) {
        
    }
    else {
        cerr << "Parser error." << std::endl;
        return -1;
    }


    return 0;
}