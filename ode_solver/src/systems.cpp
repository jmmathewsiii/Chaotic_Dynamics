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
    const std::size_t state_size = s.getSize();

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
    const std::size_t state_size = s.getSize();

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
    const std::size_t state_size = s.getSize();

    State ds(state_size, t);

    ds.x[0] = -(s.x[1] + s.x[2]);
    ds.x[1] = s.x[0] + (a * s.x[1]);
    ds.x[2] = b + (s.x[2] * (s.x[0] - c));

    return ds;
}


LorenzVariation::LorenzVariation() {
    a = 16;
    b = 4;
    r = 45;
}

LorenzVariation::LorenzVariation(double a_, double b_, double r_) {
    a = a_;
    b = b_;
    r = r_;
}

State LorenzVariation::operator()(const State &s, double t) const {
    const std::size_t STATE_SIZE = s.getSize();

    State ds(STATE_SIZE, t);

    // Regular Lorenz system
    ds.x[0] = a * (s.x[1] - s.x[0]);
    ds.x[1] = (r * s.x[0]) - s.x[1] - (s.x[0] * s.x[2]);
    ds.x[2] = (s.x[0] * s.x[1]) - (b * s.x[2]);

    // Variations
    // Order by starting at top-left entry and go down the first column, then go down the second column, etc.
    ds.x[3] = a * (s.x[4] - s.x[3]);
    ds.x[4] = ((r - s.x[2]) * s.x[3]) - s.x[4] - (s.x[0] * s.x[5]);
    ds.x[5] = (s.x[1] * s.x[3]) + (s.x[0] * s.x[4]) - (b * s.x[5]);

    ds.x[6] = a * (s.x[7] - s.x[6]);
    ds.x[7] = ((r - s.x[2]) * s.x[6]) - s.x[7] - (s.x[0] * s.x[8]);
    ds.x[8] = (s.x[1] * s.x[6]) + (s.x[0] * s.x[7]) - (b * s.x[8]);

    ds.x[9] = a * (s.x[10] - s.x[9]);
    ds.x[10] = ((r - s.x[2]) * s.x[9]) - s.x[10] - (s.x[0] * s.x[11]);
    ds.x[11] = (s.x[1] * s.x[9]) + (s.x[0] * s.x[10]) - (b * s.x[11]);

    return ds;

}
