#include "../include/utils.h"
#include "../include/state.h"
#include "../include/embed.h"

int main(int argc, char** argv)
{
    if (argc != 9) { cerr << "Usage: ts_analysis <dataset> <type> <s> <tau> <m> <j> <k> <l>\n"; return 0; }

    string dataset = argv[1];
    string type    = argv[2];
    std::size_t s  = std::stoul(argv[3]);
    double tau     = std::stod(argv[4]);
    int m          = std::stoi(argv[5]);
    int j          = std::stoi(argv[6]);
    int k          = std::stoi(argv[7]);
    int l          = std::stoi(argv[8]);

    VD tvals;
    VD xvals;

    Utils::read_data_into_vectors(tvals, xvals, dataset);

    VD tvals_s = Utils::downsample(tvals, s);
    VD xvals_s = Utils::downsample(xvals, s);

    if (type == "ss")
    {
        VD dx_vals = Utils::forward_euler(xvals_s, tvals_s);

        VS states;
        for (std::size_t i = 0; i < dx_vals.size(); ++i)
        {
            State curr_state(2, tvals_s[i]);
            curr_state.x[0] = xvals_s[i];
            curr_state.x[1] = dx_vals[i];
            states.push_back(curr_state);
        }
        string plotname = dataset + "-state-space";
        Utils::plot_2D_state_space(states, plotname);
    }
    else if (type == "embed")
    {
        VS states = Embed::build(xvals_s, tvals_s, tau, m);
        string plotname = dataset + "-embed";
        Utils::plot_embed_3D(states, j, k, l, plotname);
    }

    return 0;
}
