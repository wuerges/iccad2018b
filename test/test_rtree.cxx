#include <base.hpp>

#include <RTree.h>

#include <iostream>

using namespace std;
using namespace base;

int main() {

    P2 p1{0,1};
    
    P2 p2{1,1};
    
    // P2 p3{0,1};
    
    // P2 p4{1,0};

    R2 r{p1, p2};


    rtree::RTree<int, int, 2, double> tree;

    tree.Insert(r.p1.coords.begin(), r.p2.coords.begin(), 0);

    tree.Search(r.p1.coords.begin(), r.p2.coords.begin(), [](auto x) {
        cout << "found " << x << endl;
        return true;
    });    

}