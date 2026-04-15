#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class State;

using VS = std::vector<State>;
using VD = std::vector<double>;
using string = std::string;
using std::cout;
using std::cerr;

constexpr double PI = 3.1415926535897932;


namespace Utils
{
    void read_data_into_vectors(VD&, VD&, string);

    VD downsample(VD&, std::size_t);

    void plot_time_series(VD&, string&);
    void plot_2D_state_space(VS&, string&);
    void plot_embed(VS&, int j, int k, string&);
    void plot_embed_3D(VS&, int j, int k, int l, string&);
    void plot_2D_state_space_section(VD&, string&);
    void plot_multiple_2D_state_spaces(VD&, string&);
    void plot_3D_state_space(VD&, string&);
    void plot_multiple_3D_state_spaces(VD&, string&);

    VD forward_euler(VD&, VD&);
}

#endif // !UTILS_H
