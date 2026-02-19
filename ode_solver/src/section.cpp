#include "../include/section.h"
#include <cmath>

VS temporalPoincare(VS &states, double T, double err = 0.00001)
{
    const int SIZE = states.size();
    const int STATE_SIZE = states[0].getSize();
    VS section_states;
    State curr_state(STATE_SIZE);
    double curr_t;

    for (int i = 0; i < SIZE; ++i)
    {
        curr_state = states[i];
        curr_t = curr_state.t;

        if (std::fmod(curr_t, T) < err)
        {
            section_states.push_back(curr_state);
        }
    }
    return section_states;
}
