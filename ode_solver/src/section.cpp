#include "../include/section.h"
#include <cmath>

VS temporalPoincare(VS &states, double T)
{
    const int SIZE = states.size();
    const int STATE_SIZE = states[0].getSize();
    VS section_states;
    State curr_state(STATE_SIZE);
    double curr_t;
    double counter = 0;
    double update_T = T;

    for (int i = 1; i < SIZE; ++i)
    {
        curr_state = states[i];
        curr_t = curr_state.t;

        if (curr_t >= update_T)
        {
            section_states.push_back(curr_state);
            ++counter;
            update_T += T;
        }
    }
    cout << "Number of hits: " << counter << "\n";
    return section_states;
}

VS interpolatedTemporalPoincare(VS &states, double T)
{
    const size_t SIZE = states.size();
    const int STATE_SIZE = states[0].getSize();

    VS section_states;

    State curr_state(STATE_SIZE);
    State prev_state(STATE_SIZE);
    State diff_state(STATE_SIZE);
    State interp_state(STATE_SIZE);

    const double t_diff = states[1].t - states[0].t;
    double curr_t;
    double prev_t;
    double t_factor;

    int counter = 0;
    double update_T = T;

    for (size_t i = 0; i < SIZE; ++i)
    {
        curr_state = states[i];
        curr_t = curr_state.t;

        if (curr_t >= update_T)
        {
            prev_state = states[i-1];
            prev_t = prev_state.t;

            diff_state = curr_state - prev_state;

            t_factor = (update_T - prev_t) / t_diff;
            interp_state = prev_state + (diff_state * t_factor);
            interp_state.t = update_T;

            section_states.push_back(interp_state);

            update_T += T;
            ++counter;
        }
    }
    cout << "Number of hits: " << counter << "\n";
    return section_states;
}
