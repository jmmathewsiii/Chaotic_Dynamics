#include "../include/rk4.h"

State rk4_step(State &curr_state, double dt, DerivativeFunc f)
{

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

State rk4_step_adaptive(State &curr_state, double &dt0, DerivativeFunc f, double tol)
{
    cout << "Tol = " << tol << "\n";
    State full_step_result      = rk4_step(curr_state          , dt0      , f);

    State one_half_step_result  = rk4_step(curr_state          , dt0 * 0.5, f);
    State two_half_steps_result = rk4_step(one_half_step_result, dt0 * 0.5, f);

    State shrink_err_state = two_half_steps_result - full_step_result;
    double shrink_err_norm = shrink_err_state.twoNorm();
    
    if (shrink_err_norm > tol) {
        dt0 *= 0.5;
        return rk4_step_adaptive_shrinking(curr_state, one_half_step_result, dt0, f, tol);
    }
    
    State two_full_steps_result = rk4_step(full_step_result, dt0, f);
    State one_double_step_result = rk4_step(curr_state, dt0 * 2., f);

    State grow_err_state = two_full_steps_result - one_double_step_result;
    double grow_err_norm = grow_err_state.twoNorm();

    if (grow_err_norm < tol)
    {
        dt0 *= 2.;
        return rk4_step_adaptive_growing(curr_state, one_double_step_result, dt0, f, tol);
    }

    return full_step_result;
}

State rk4_step_adaptive_shrinking(State &curr_state, State &cached_state, double &dt, DerivativeFunc f, double tol)
{
    State full_step_result = cached_state;

    State one_half_step_result  = rk4_step(curr_state          , dt * 0.5, f);
    State two_half_steps_result = rk4_step(one_half_step_result, dt * 0.5, f);

    State shrink_err_state = two_half_steps_result - full_step_result;
    double shrink_err_norm = shrink_err_state.twoNorm();
    
    if (shrink_err_norm > tol) {
        dt *= 0.5;
        return rk4_step_adaptive_shrinking(curr_state, one_half_step_result, dt, f, tol);
    }
    else {
        return full_step_result;
    }
}

State rk4_step_adaptive_growing(State &curr_state, State &cached_state, double &dt, DerivativeFunc f, double tol)
{
    State full_step_result = cached_state;
    State two_full_steps_result = rk4_step(full_step_result, dt * 2., f);

    State one_double_step_result = rk4_step(curr_state, dt, f);

    State grow_err_state = two_full_steps_result - one_double_step_result;
    double grow_err_norm = grow_err_state.twoNorm();

    if (grow_err_norm < tol)
    {
        dt *= 2.;
        return rk4_step_adaptive_growing(curr_state, one_double_step_result, dt, f, tol);
    }
    else {
        return full_step_result;
    }
}
