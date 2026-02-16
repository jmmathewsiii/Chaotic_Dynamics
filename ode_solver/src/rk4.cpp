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

VS run_one_sim(double t0, double dt, int n_iter, double A, double m, double l, double alpha, double beta, double g, double theta, double omega)
{
    Pendulum pend(A, m, l, alpha, beta, g);

    State curr_state(2, t0);
    curr_state.x[0] = theta;
    curr_state.x[1] = omega;

    VS history;
    history.reserve(n_iter);
    history.push_back(curr_state);

    double t_new = t0 + dt;

    for (int i = 1; i < n_iter; ++i) {

        State new_state(2, t_new);
        new_state = rk4_step(curr_state, dt, pend);
        history.push_back(new_state);
        curr_state = new_state;
    }
    return history;
}

VSS run_multiple_sims(double t0, double dt, int n_iter, double A, double m, double l, double alpha, double beta, double g, std::vector<double> thetas, std::vector<double> omegas)
{
    Pendulum pend(A, m, l, alpha, beta, g);

    const int N_THETAS = thetas.size();
    const int N_OMEGAS = omegas.size();
    const int N_STARTS = N_THETAS * N_OMEGAS;

    VSS histories;
    histories.reserve(N_STARTS);

    for (int j = 0; j < N_THETAS; ++j) {
        for (int k = 0; k < N_OMEGAS; ++k) {
        
            std::vector<State> history;
            history.reserve(n_iter);

            State curr_state(2, t0);
            curr_state.x[0] = thetas[j];
            curr_state.x[1] = omegas[k];

            history.push_back(curr_state);

            double t_new = t0 + dt;

            for (int i = 1; i < n_iter; ++i) {

                State new_state(2, t_new);
                new_state = rk4_step(curr_state, dt, pend);
                history.push_back(new_state);
                curr_state = new_state;
            }

            histories.push_back(history);
        }
    }
    return histories;
}
