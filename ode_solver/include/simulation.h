#ifndef SIMULATION_H
#define SIMULATION_H

#include "rk4.h"

template<typename SystemType>
VS run_one_sim(State &start_state, double t0, double dt, int n_iter, SystemType system)
{
    const int STATE_SIZE = start_state.getSize();
    State curr_state = start_state;

    VS history;
    history.reserve(n_iter);
    history.push_back(curr_state);

    double t_new = t0 + dt;

    for (int i = 1; i < n_iter; ++i) {

        State new_state(STATE_SIZE, t_new);
        new_state = rk4_step(curr_state, dt, system);
        history.push_back(new_state);
        curr_state = new_state;
    }
    return history;}

template<typename SystemType>
VS run_one_sim_adaptive(State &start_state, double t0, double dt, int n_iter, SystemType system)
{
    const int STATE_SIZE = start_state.getSize();
    State curr_state = start_state;

    VS history;
    history.reserve(n_iter);
    history.push_back(curr_state);

    double t_new = t0 + dt;

    for (int i = 1; i < n_iter; ++i) {

        State new_state(STATE_SIZE, t_new);
        new_state = rk4_step_adaptive(curr_state, dt, system, 0.6); // hard-coded tolerance
        history.push_back(new_state);
        curr_state = new_state;
    }
    return history;
}

template<typename SystemType>
VSS run_multiple_sims(VS &start_states, double t0, double dt, int n_iter, SystemType system)
{

    const int N_STARTS = start_states.size();
    const int STATE_SIZE = start_states[0].getSize();

    VSS histories;
    histories.reserve(N_STARTS);

    for (int j = 0; j < N_STARTS; ++j)
    {
        VS history;
        history.reserve(n_iter);

        State curr_state = start_states[j];

        history.push_back(curr_state);

        double t_new = t0 + dt;

        for (int i = 1; i < n_iter; ++i) {
            State new_state(STATE_SIZE, t_new);
            new_state = rk4_step(curr_state, dt, system);
            history.push_back(new_state);
            curr_state = new_state;
        }

        histories.push_back(history);
    }
    return histories;
}
#endif // !SIMULATION_H
