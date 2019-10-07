#include <iostream>
#include <parser.hpp>

int main() {
    using std::cout;
    if(parse()) {
        cout << "linked parser!\n";
    }
    cout << "Hello World\n";
}