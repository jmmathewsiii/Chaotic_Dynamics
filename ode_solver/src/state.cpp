#include "../include/state.h"
#include <algorithm>
#include <cmath>

State::State(std::size_t capacity, double t_) {
   x.resize(capacity);
   t = t_;
}

State State::operator+(const State &other) const {
    int size = x.size();
    State result(size, t);
    for (int i = 0; i < size; i++) {
        result.x[i] = x[i] + other.x[i];
    }
    return result;
}

State State::operator*(double scalar) const {
    int size = x.size();
    State result(size, t);
    for (int i = 0; i < size; i++) {
        result.x[i] = x[i] * scalar;
    }
    return result;
}

State State::operator-(const State &other) const {
    int size = x.size();
    State result(size, t);
    for (int i = 0; i < size; ++i) {
        result.x[i] = x[i] - other.x[i];
    }
    return result;
}

double State::infNorm() const
{
    auto max_it = std::max_element(x.begin(), x.end());
    auto max = *max_it;
    return max;
}

double State::twoNorm() const
{
    int size = x.size();
    double sum = 0.;
    for (int i = 0; i < size; ++i)
    {
        double sq = x[i] * x[i];
        sum += sq;
    }
    double result = std::sqrt(sum);
    return result;
}

int State::getSize() const {
    return x.size();
}
