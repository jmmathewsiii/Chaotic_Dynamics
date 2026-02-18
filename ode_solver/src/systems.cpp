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


Lorenz::Lorenz() {
    a = 16.;
    b = 4.;
    r = 45.;
}

Lorenz::Lorenz(double a_, double b_, double r_) {
    a = a_;
    b = b_;
    r = r_;
}

State Lorenz::operator()(const State &s, double t) const {
    const int state_size = s.getSize();

    State ds(state_size, t);

    ds.x[0] = a * (s.x[1] - s.x[0]);
    ds.x[1] = (r * s.x[0]) - s.x[1] - (s.x[0] * s.x[2]);
    ds.x[2] = (s.x[0] * s.x[1]) - (b * s.x[2]);

    return ds;
}


Rossler::Rossler() {
    a = 0.398;
    b = 2.;
    c = 4;
}

Rossler::Rossler(double a_, double b_, double c_) {
    a = a_;
    b = b_;
    c = c_;
}

State Rossler::operator()(const State &s, double t) const {
    const int state_size = s.getSize();

    State ds(state_size, t);

    ds.x[0] = -(s.x[1] + s.x[2]);
    ds.x[1] = s.x[0] + (a * s.x[1]);
    ds.x[2] = b + (s.x[2] * (s.x[0] - c));

    return ds;
}
