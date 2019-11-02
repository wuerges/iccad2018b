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
bool operator<(const Point<N> & v1, const Point<N> & v2) {
    return v1.coords < v2.coords;        
}

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
std::ostream & operator<<(std::ostream & out, const Rectangle<N> & r) {
    out << "Rectangle(" << r.p1 <<"," << r.p2 << ")";
    return out;
}

template<int N> 
Point<N> crossing(const Rectangle<N> & r1, const Rectangle<N> & r2) {
    Point<N> ret = r2.p1;

    // If r1 is horizontal;
    if(r1.p1[0] == r1.p2[0]) {
        ret.coords[0] = r1.p1[0];
    }
    // If r1 is vertical;
    else {
        ret.coords[1] == r1.p1[1];
    }
    return ret;
}

template<int N>
uint32_t distance(const Point<N> & p1, const Point<N> & p2) {
    uint32_t result = 0;
    for(int i = 0; i < N; ++i) {
        int p1i = p1[i];
        int p2i = p2[i];
        result += std::abs(p1i - p2i);
    }
    return result;
}


int disti(int a, int b, int aw, int bw);

template<int N>
uint32_t distance(const Rectangle<N> & r1, const Rectangle<N> & r2) {

    uint32_t result = 0;
    for(int i = 0; i < N; ++i) {
        int ax1 = r1.p1[i];
        int ax2 = r1.p2[i];
        int adx = std::abs(ax1 - ax2);
        
        int bx1 = r2.p1[i];
        int bx2 = r2.p2[i];
        int bdx = std::abs(bx1 - bx2);
        
        result += disti(ax1, bx1, adx, bdx);
    }
    // std::cout << "r1 =" << r1 << std::endl;
    // std::cout << "r2 =" << r2 << std::endl;
    // std::cout << "distance = " << result << std::endl;
    return result;
}


template<int N>
bool operator==(const Point<N> & p1, const Point<N> & p2) {
    for(int i = 0; i < N; ++i) {
        if(p1[i] != p2[i]) {
            return false;
        }
    }
    return true;
}


using R2 = Rectangle<2>;
using R3 = Rectangle<3>;
using P2 = Point<2>;
using P3 = Point<3>;


}