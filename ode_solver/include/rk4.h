#ifndef RK4_H
#define RK4_H

#include "config.h"
#include "state.h"
#include "systems.h"
#include "types.h"
#include <functional>

using DerivativeFunc = std::function<State(const State&, double)>;

State rk4_step(State &curr_state, double dt, DerivativeFunc f);

VS run_one_sim(double t0, double dt, int n_iter, double A, double m, double l, double alpha, double beta, double g, double theta, double omega);

VSS run_multiple_sims(double t0, double dt, int n_iter, double A, double m, double l, double alpha, double beta, double g, std::vector<double> thetas, std::vector<double> omegas);

#endif // !RK4_H
