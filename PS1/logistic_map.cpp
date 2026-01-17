#include "logistic_map.h"
#include "plotter.hpp"
#include <algorithm>

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

    double last = xvals.back();
    double extend = last * R * (1 - R);
    double extend2 = extend * R * (1 - R);

    VD plusOneT = xvals;
    std::rotate(plusOneT.begin(), plusOneT.begin() + 1, plusOneT.end());
    plusOneT.back() = extend;

    VD plusTwoT = plusOneT;
    std::rotate(plusTwoT.begin(), plusTwoT.begin() + 1, plusTwoT.end());
    plusTwoT.back() = extend2;

    Plotter::discretePlot(tvals, xvals, "lmap");
    Plotter::contPlot(xvals, plusOneT, "o1");
    Plotter::contPlot(xvals, plusTwoT, "o2");

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

