#include "generator.hpp"


void test_intersection(R3 a, R3 b) {
    RC_ASSERT(intersection(a, b) == intersection(b, a));
}

void test_intersection_distance(R3 a, R3 b) {
    auto it = intersection(a, b);
    if(it) {
        RC_ASSERT(distance(*it, a) == 0);
        RC_ASSERT(distance(*it, b) == 0);
    }
}

int main() {
    rc::check("Test intersection", test_intersection);
    rc::check("Test intersection distance", test_intersection_distance);

    // array<P3, 4> ps;
    // ps[0] = {0, 0, 0};
    // ps[1] = {1, 0, 1};
    // ps[2] = {2, 2, 4};
    // ps[3] = {4, 3, 5};


    // for(int i = 0; i < 4; ++i) {
    //     for(int j = i; j < 4; ++j) {
    //         R3 r1{ps[i], ps[j]};
    //         for(int i = 0; i < 4; ++i) {
    //             for(int j = i; j < 4; ++j) {
    //                 R3 r2{ps[i], ps[j]};
    //                 auto it = intersection(r1, r2);
    //                 if(it) {
    //                     std::cout << "r1=" << r1 << " r2=" << r2 << " int=" <<
    //                         *it << std::endl;
    //                 }
    //                 else {
    //                     std::cout << "r1=" << r1 << " r2=" << r2 << " int=empty" << std::endl;
    //                 }
    //             }
    //         }
    //     }
    // }
}