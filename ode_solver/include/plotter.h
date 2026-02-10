#ifndef PLOTTER
#define PLOTTER

#include <iostream>
#include <fstream>
#include <string>
#include "state.h"

namespace Plotter {
    void plot_time_series(std::vector<State>&, std::string&);
    void plot_2D_state_space(std::vector<State>&, std::string&);
    void plot_3D_state_space(std::vector<State>&, std::string&);
}

#endif // !PLOTTER
