#include "logistic_map.hpp"
#include "plotter.hpp"

int main(int argc, char* argv[]) {

    if (argc != 7) {
        std::cout << "Pass in the right number of parameters" << std::endl;
        return 0;
    }

    double R_min   = std::stod(argv[1]);
    double R_max   = std::stod(argv[2]);
    double R_diff  = std::stod(argv[3]);
    double x0      = std::stod(argv[4]);
    int max_iter   = std::stoi(argv[5]);
    int start_iter = std::stoi(argv[6]);

    int total_iters = max_iter - start_iter;
    VI tvals(total_iters);
    for (int i = 0; i < total_iters; ++i) tvals[i] = i;

    double Rvals_size = (R_max - R_min) / R_diff;
    VD Rvals(Rvals_size);
    for (int i = 0; i < Rvals_size; ++i) {
        Rvals[i] = R_min + (i * R_diff);
    }
    cout << "Beginning logistic map simulation \n\n";

    cout << "R min       = " << R_min << "\n"
         << "R_max       = " << R_max << "\n"
         << "R_diff      = " << R_diff << "\n" 
         << "x0          = " << x0 << "\n"
         << "max_iter    = " << max_iter << "\n"
         << "start_iter  = " << start_iter << "\n\n"
         << "total_iters = " << total_iters << "\n"
         << "Rvals_size  = " << Rvals_size << "\n";


    VDD bifurcation_data(Rvals_size, VD(total_iters));
    
    getBifurcationData(bifurcation_data, Rvals, x0, start_iter, max_iter);

    Plotter::bifurcationPlot(Rvals, bifurcation_data, "Bifurcation");




/*    
    logisticMap(xvals, R, x0, max_iter); 

    VD plusOneT = extendVec(xvals, R);

    VD plusTwoT = extendVec(plusOneT, R);

    Plotter::discretePlot(tvals, xvals, "Time-Domain");
    Plotter::contPlot(xvals, plusOneT, "First-Return-Map");
    Plotter::contPlot(xvals, plusTwoT, "Second-Return-Map");
*/

    return 0;
}

void getBifurcationData(VDD &bifurcation_data, VD &Rvals, double x0, int start_iter, int max_iter) {
    int rvals_size = Rvals.size();

    for (int i = 0; i < rvals_size; ++i) {
        double R = Rvals[i];
        logisticMap(bifurcation_data[i], R, x0, start_iter, max_iter);
    }
}

/* Logistic Map */

void logisticMap(VD &xvals, double R, double x0, int start_iter, int max_iter) {

    double x = x0;
    int total_iters = max_iter - start_iter;

    for (int i = 0; i < start_iter; ++i) x = R * x * (1 - x);

    for (int i = 0; i < total_iters; ++i) {
        xvals[i] = x;
        x = R * x * (1 - x);
    }
}

void HenonMap(VD &xvals, VD &yvals, double a, double b, double x0, double y0, int start_iter, int max_iter) {

    double x = x0;
    double y = y0;
    double x_old = x;

    int total_iters = max_iter - start_iter;

    for (int i = 0; i < start_iter; ++i) {
        x = y + 1 - (a * x * x);
        y = b * x_old;
        x_old = x;
    }

    for (int i = 0; i < total_iters; ++i) {
        xvals[i] = x;
        yvals[i] = y;

        x = y + 1 - (a * x * x);
        y = b * x_old;
        x_old = x;
    }
}
