#ifndef STATE_H
#define STATE_H

#include "config.h"

class State {
    public:
    double t;
    VD x;

    State(std::size_t capacity, double t_=0.);
    
    State operator+(const State &other) const;
    State operator*(double scalar) const;

    int getSize() const;
};

#endif // STATE_H
