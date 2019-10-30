#pragma once

#include <iostream>
#include <array>

namespace base {

template <int N>
struct Point {
    std::array<uint32_t, N> coords;
    uint32_t operator[](const int i) const {
        return coords[i];
    }
};

template<int N>
std::ostream & operator<<(std::ostream & out, const Point<N> & p) {
    out << "(";
    for(int i = 0; i < N; ++i) {
        out << (i==0 ? "": " ") << p[i];
    }
    out << ")";
    return out;
}

template <int N>
struct Rectangle {
    Point<N> p1, p2;
};

template<int N>
bool operator==(const Point<N> & p1, const Point<N> & p2) {
    for(int i = 0; i < N; ++i) {
        if(p1[i] != p2[i]) {
            return false;
        }
    }
    return true;
}



// void decls() {
using R2 = Rectangle<2>;
using R3 = Rectangle<3>;
using P2 = Point<2>;
using P3 = Point<3>;
// }


}