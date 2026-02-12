#include "../include/rk4.h"
#include "../include/systems.h"
#include "../include/plotter.h"
#include <cmath>


const int ARGNUM = 12;

void run_one_sim(double t0, double dt, int n_iter, double A, double m, double l, double alpha, double beta, double g, double theta, double omega);

void run_multiple_sims(double t0, double dt, int n_iter, double A, double m, double l, double alpha, double beta, double g, std::vector<double> thetas, std::vector<double> omegas);

void setThetasAndOmegas(std::vector<double>&, std::vector<double>&);

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

//    std::vector<double> thetas;
//    std::vector<double> omegas;

//    thetas.push_back(theta);
//    omegas.push_back(omega);

//    setThetasAndOmegas(thetas, omegas);


//    run_multiple_sims(t0, dt, n_iter, A, m, l, alpha, beta, g, thetas, omegas);
    run_one_sim(t0, dt, n_iter, A, m, l, alpha, beta, g, theta, omega);
}


void run_one_sim(double t0, double dt, int n_iter, double A, double m, double l, double alpha, double beta, double g, double theta, double omega)
{

    Pendulum pend(A, m, l, alpha, beta, g);

    std::vector<State> history;

    State curr_state(2, t0);
    curr_state.x[0] = theta;
    curr_state.x[1] = omega;

    history.reserve(n_iter);
    history.push_back(curr_state);

    double t_new = t0 + dt;

    for (int i = 1; i < n_iter; ++i) {

        State new_state(2, t_new);
        new_state = rk4_step(curr_state, dt, pend);
        history.push_back(new_state);
        curr_state = new_state;
    }
    
    std::string state_space_plotname = "State-Space-Plot";

    Plotter::plot_2D_state_space(history, state_space_plotname);
}

void run_multiple_sims(double t0, double dt, int n_iter, double A, double m, double l, double alpha, double beta, double g, std::vector<double> thetas, std::vector<double> omegas)
{
    Pendulum pend(A, m, l, alpha, beta, g);

    const int N_THETAS = thetas.size();
    const int N_OMEGAS = omegas.size();
    const int N_STARTS = N_THETAS * N_OMEGAS;

    std::vector<std::vector<State>> histories;
    histories.reserve(N_STARTS);

    for (int j = 0; j < N_THETAS; ++j) {
        for (int k = 0; k < N_OMEGAS; ++k) {
        
            std::vector<State> history;

            State curr_state(2, t0);
            curr_state.x[0] = thetas[j];
            curr_state.x[1] = omegas[k];

            history.reserve(n_iter);
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
    std::string state_space_plotname = "State-Space-Portrait";

    Plotter::plot_multiple_2D_state_spaces(histories, state_space_plotname);
}

void setThetasAndOmegas(std::vector<double> &thetas, std::vector<double> &omegas) {

    for (int i = -15; i <= 15; ++i) {
        thetas.push_back(PI * i / 5);
    }
    for (int i = -2; i < 3; ++i) {
        thetas.push_back((PI * i) - 0.25);
        thetas.push_back((PI * i) + 0.25);
        thetas.push_back((PI * i) - 0.1);
        thetas.push_back((PI * i) + 0.1);
    }
    for (int i = -3; i < 3; ++i) {
        omegas.push_back(i * 0.01);
    }
    omegas.push_back(20.5);
    omegas.push_back(-20.5);

}
