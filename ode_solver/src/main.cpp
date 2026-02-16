#include "../include/rk4.h"
#include "../include/plotter.h"


const int ARGNUM = 12;

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

    std::vector<double> thetas;
    std::vector<double> omegas;

    thetas.push_back(theta);
    omegas.push_back(omega);

    setThetasAndOmegas(thetas, omegas);

    //VSS histories = run_multiple_sims(t0, dt, n_iter, A, m, l, alpha, beta, g, thetas, omegas);
    VS history = run_one_sim(t0, dt, n_iter, A, m, l, alpha, beta, g, theta, omega);

    std::string state_space_name = "State-Space-Plot";
    std::string portrait_name = "State-Space-Portrait";

    Plotter::plot_2D_state_space(history, state_space_name);
//    Plotter::plot_multiple_2D_state_spaces(histories, portrait_name);
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
