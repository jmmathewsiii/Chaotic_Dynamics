#include "../include/rk4.h"
#include "../include/systems.h"
#include "../include/plotter.h"


const int ARGNUM = 12;

int main(int argc, char* argv[])
{
    if (argc != ARGNUM) {
        std::cerr << "Error: Too few arguments.\nExpected: " 
                  << ARGNUM << ". Received: " << argc << "\n";
        return -1;
    }

    double    t0 = std::stod(argv[1]);
    double    dt = std::stod(argv[2]);
    int   n_iter = std::stoi(argv[3]);
    double     A = std::stod(argv[4]);
    double     m = std::stod(argv[5]);
    double     l = std::stod(argv[6]);
    double alpha = std::stod(argv[7]);
    double  beta = std::stod(argv[8]);
    double     g = std::stod(argv[9]);
    double theta = std::stod(argv[10]);
    double omega = std::stod(argv[11]);

    Pendulum pend(A, m, l, alpha, beta, g);

    State curr_state(2, t0);
    curr_state.x[0] = theta;
    curr_state.x[1] = omega;

    std::vector<State> history;
    history.reserve(n_iter);
    history.push_back(curr_state);

    double t_new = t0 + dt;

    for (int i = 1; i < n_iter; ++i) {
        State new_state(2, t_new);
        new_state = rk4_step(curr_state, dt, pend);
        history.push_back(new_state);
    }

    std::string pltname = "TS Plot";
    Plotter::plot_time_series(history, pltname);

}
