#include "solver.hpp"
#include "plotter.hpp"

const int ARGNUM = 10;

int main(int argc, char* argv[])
{
    if (argc != ARGNUM) {
        std::cerr << "Error: Too few arguments.\nExpected: " << ARGNUM << ". Received: " << argc << "\n";
        return -1;
    }

    double t0 = std::stod(argv[1]);
    double dt = std::stod(argv[2]);
    int   num = std::stoi(argv[3]);
    double y0 = std::stod(argv[4]);
    double  m = std::stod(argv[5]);
    double  l = std::stod(argv[6]);
    double  b = std::stod(argv[7]);
    double  A = std::stod(argv[8]);
    double al = std::stod(argv[9]);

}

void RK4()
{
    
}

