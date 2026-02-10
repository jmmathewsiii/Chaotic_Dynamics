#include "../include/state.h"

State::State(std::size_t capacity, double t_) {
   x.resize(capacity);
   t = t_;
}

State State::operator+(const State &other) const {
    State result(x.size(), t);  // or could use other.t
    for (int i = 0; i < x.size(); i++) {
        result.x[i] = x[i] + other.x[i];
    }
    return result;
}

State State::operator*(double scalar) const {
    State result(x.size(), t);
    for (int i = 0; i < x.size(); i++) {
        result.x[i] = x[i] * scalar;
    }
    return result;
}

int State::getSize() const {
    return x.size();
}
