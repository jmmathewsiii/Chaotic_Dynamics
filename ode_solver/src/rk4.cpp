#include "../include/rk4.h"

State rk4_step(State &curr_state, double dt, DerivativeFunc f)
{
    std::size_t state_size = curr_state.getSize();

    double half_step = dt * 0.5;
    double sixth_step = dt / 6;

    double t0 = curr_state.t;
    double t1 = t0 + half_step;
    double t2 = t0 + dt;

    State k1 = f(curr_state, t0);
    State k2 = f(curr_state + (k1 * half_step), t1);
    State k3 = f(curr_state + (k2 * half_step), t1);
    State k4 = f(curr_state + (k3 * dt), t2);

    State result = curr_state + ((k1 + (k2*2) + (k3*2) + k4) * sixth_step);
    result.t = t2;

    return result;
}
