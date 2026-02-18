#ifndef PLOTTER
#define PLOTTER

#include <fstream>
#include "state.h"
#include "types.h"

namespace Plotter {
    void plot_time_series(VS&, string&);
    void plot_2D_state_space(VS&, string&);
    void plot_multiple_2D_state_spaces(VSS&, string&);
    void plot_3D_state_space(VS&, string&);
    void plot_multiple_3D_state_spaces(VSS&, string&);
}

#endif // !PLOTTER
