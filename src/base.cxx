#include <base.hpp>

namespace base {


int disti(int a, int b, int aw, int bw) {
    if(a < b) {
        if(a + aw < b) {
            return b - a - aw;
        }
        return 0;
    }
    else {
        if(b + bw < a) {
            return a - b - bw;
        }
        return 0;
    }
}

}