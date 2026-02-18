#ifndef RK4_H
#define RK4_H

#include "config.h"
#include "state.h"
#include "systems.h"
#include "types.h"
#include <functional>

using DerivativeFunc = std::function<State(const State&, double)>;

State rk4_step(State &curr_state, double dt, DerivativeFunc f);

State rk4_step_adaptive(State&, double&, DerivativeFunc, double);
State rk4_step_adaptive_shrinking(State&, State&, double&, DerivativeFunc, double);
State rk4_step_adaptive_growing(State&, State&, double&, DerivativeFunc, double);

#endif // !RK4_H
