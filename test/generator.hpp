#pragma once

#include <base.hpp>

#include <rapidcheck.h>

#include <array>

using namespace std;
using namespace base;

namespace rc {


template<int N>
struct Arbitrary<Point<N>> {
    static Gen<Point<N>> arbitrary() {
        const auto genPT = gen::container<array<int, N>>(gen::inRange(0, 100000));
        return gen::map(genPT,
            [](array<int, N> vs) {
                return Point<N>{vs};
            });
    }
};

template<int N>
struct Arbitrary<Rectangle<N>> {
    static Gen<Rectangle<N>> arbitrary() {
    return gen::map(
        gen::container<array<Point<N>, 2>>(gen::arbitrary<Point<N>>()),
        [](const array<Point<N>, 2> pts) {
            auto a = min(pts[0], pts[1]);
            auto b = max(pts[0], pts[1]);
        return Rectangle<N>{a, b};
        });
    }
};

}