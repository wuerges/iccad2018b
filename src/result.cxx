#include <result.hpp>

#include <iostream>



ostream & 
operator<<(ostream & out, const Result & r) {
    out << "Dummy Result" << std::endl;
    return out;
}