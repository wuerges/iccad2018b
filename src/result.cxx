#include <result.hpp>

#include <iostream>


using std::endl;


std::ostream & 
operator<<(std::ostream & out, const ResultShape & shape) {
    out << "L" << shape.layer;
    if(shape.rect.p1 == shape.rect.p2) {
        out << shape.rect.p1;
    }
    else {
        out << shape.rect.p1 << " " << shape.rect.p2;
    }
    out << endl;
    return out;
}

ostream & 
operator<<(ostream & out, const Result & r) {

    for(auto & [busname, bit] : r.buses) {
        out << "BUS " << busname << endl;
        for(auto & [bitname, path] : bit) {
            out << "BIT " << bitname << endl;
            auto & [pathname, shapes] = path;
            out << "PATH " << pathname << endl;
            for(auto & shape : shapes) {
                
            }
        }
    }
    return out;
}