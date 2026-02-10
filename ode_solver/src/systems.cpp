#include "../include/systems.h"
#include <cmath>

Pendulum::Pendulum() {
    A = 0.;
    m = 0.1;
    l = 0.1;
    alpha = 0.;
    beta = 0;
    g = GRAVITY;
}

Pendulum::Pendulum(double A_, double m_, double l_, double alpha_, double beta_, double g_) {
    A = A_;
    m = m_;
    l = l_;
    alpha = alpha_;
    beta = beta_;
    g = g_;
}

State Pendulum::operator()(const State &s, double t) const {
    const int state_size = s.getSize();

    State ds(state_size, t);
    ds.x[0] = s.x[1];
    ds.x[1] =   ((A / (m * l)) * std::cos(alpha * t)) 
              - ((beta / m) * s.x[1])
              - ((g / l) * std::sin(s.x[0]));

    return ds;
}
