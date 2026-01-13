#include<iostream>

void logisticMap(double*, double, double, int);

int main(int argc, char* argv[]) {

    double R = std::stod(argv[0]);
    double x0 = std::stod(argv[1]);
    int max_iter = std::stoi(argv[2]);

    double* xvals = new double[max_iter];
    
    logisticMap(xvals, R, x0, max_iter); 

    return 0;
}

void logisticMap(double* xvals, double R, double x0, int max_iter) {

    double x = x0;
    for (int i = 0; i < max_iter; i++) {
        xvals[i] = x;
        x = R * x * (1 - x);
    }
}

