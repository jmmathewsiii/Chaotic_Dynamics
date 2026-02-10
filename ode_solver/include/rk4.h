#ifndef RK4_H
#define RK4_H

#include "config.h"
#include "state.h"
#include <functional>

using DerivativeFunc = std::function<State(const State&, double)>;

State rk4_step(State &curr_state, double dt, DerivativeFunc f);

#endif // !RK4_H
