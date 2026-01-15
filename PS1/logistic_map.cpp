#include "logistic_map.h"
#include "plotter.hpp"

void logisticMap(VD &xvals, double R, double x0, int max_iter); 

int main(int argc, char* argv[]) {

    if (argc != 4) {
        std::cout << "Pass in the right number of parameters" << std::endl;
        return 0;
    }

    double R = std::stod(argv[1]);
    double x0 = std::stod(argv[2]);
    int max_iter = std::stoi(argv[3]);

    VI tvals;
    tvals.resize(max_iter);

    VD xvals;
    xvals.resize(max_iter);

    for (int i = 0; i < max_iter; ++i) tvals[i] = i;
    
    logisticMap(xvals, R, x0, max_iter); 

    /*
    for (int i = 0; i < max_iter; i++) {
        std::cout << xvals[i] << " ";
        if (i % 5 == 4) {
            std::cout << std::endl;
        }
    } 
    */

    Plotter::plot(tvals, xvals, "logmap");

    return 0;
}

/* Logistic Map */

void logisticMap(VD &xvals, double R, double x0, int max_iter) {

    double x = x0;
    for (int i = 0; i < max_iter; i++) {
        xvals[i] = x;
        x = R * x * (1 - x);
    }
}

