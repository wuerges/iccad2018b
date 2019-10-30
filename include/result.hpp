#pragma once

#include <iostream>

using std::ostream;

struct Result {

    friend ostream & operator<<(ostream &, const Result &);

};