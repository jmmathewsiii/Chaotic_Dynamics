#include "../include/utils.h"
#include "../include/state.h"
#include <sstream>
#include <cmath>

void Utils::read_data_into_vectors(VD &tvals, VD &xvals, string filename)
{
    filename = "./input/" + filename;
    std::ifstream f;
    f.open(filename);

    if (!f.is_open()) {
        cerr << "Filename not recognized: " << filename << "\n";
        return;
    }

    string line;
    while (std::getline(f, line)) {
        std::istringstream lss(line);
        double t;
        double theta;
        if (lss >> theta >> t) {
            tvals.push_back(t);
            xvals.push_back(theta);
        }
    }
    f.close();
}

VD Utils::downsample(VD &data, std::size_t step){
    VD sampled_data;

    for (std::size_t i = 0; i < data.size(); i += step)
        sampled_data.push_back(data[i]);

    return sampled_data;
}

VD Utils::forward_euler(VD &xvals, VD &tvals)
{
    VD dx_vals;

    for (std::size_t i = 0; i < xvals.size() - 1; ++i)
    {
        double dx = (xvals[i+1] - xvals[i]) / (tvals[i+1] - tvals[i]);
        dx_vals.push_back(dx);
    }

    return dx_vals;
}

void Utils::plot_2D_state_space(std::vector<State> &states, std::string &name) {

    int size = states.size();

    std::string data_filename = name + ".plt";
    std::string data_filepath = "./output/" + data_filename;

    std::ofstream f;
    f.open(data_filepath.c_str(), std::ios::out);

    double theta = 0;
    double prev_theta = 0;

    for (int i = 0; i < size; ++i) {
        theta = states[i].x[0];
        theta = std::fmod(theta, 2 * PI);
        if (theta < 0) theta += 2 * PI;
        if (std::abs(theta - prev_theta) > 6.) {f << "\n";}
        f << theta << " " << states[i].x[1] << "\n";
        prev_theta = theta;
    }

    f.close();

    std::cout << "Data file written: " << data_filepath << "\n";

    std::string cmd_filename = name;
    std::string cmd_filepath = "./output/" + cmd_filename;

    f.open(cmd_filepath.c_str(), std::ios::out);
    f << "set title '" << name <<"' font ', 14'\n";
    f << "set tics font ', 14'\n"; 
    f << "unset key\n";
    f << "plot '" << data_filename << "' w l lw 1 \n";

    f.close();

    std::cout << "Command file written: " << cmd_filepath << "\n";
}

void Utils::plot_embed(VS &states, int j, int k, std::string &name)
{

    int size = states.size();

    std::string data_filename = name + ".plt";
    std::string data_filepath = "./output/" + data_filename;

    std::ofstream f;
    f.open(data_filepath.c_str(), std::ios::out);

    double x = 0;
    // double prev_x = 0;
    double y = 0;
    // double prev_y = 0;

    for (int i = 0; i < size; ++i) {
        x = states[i].x[j];
        y = states[i].x[k];
        // x = std::fmod(x, 2 * PI);
        // y = std::fmod(y, 2 * PI);
        // if (std::abs(x - prev_x) > 6. || std::abs(y - prev_y) > 6.) {f << "\n";}
        f << x << " " << y << "\n";
        // prev_x = x;
        // prev_y = y;
    }

    f.close();

    std::cout << "Data file written: " << data_filename << "\n";
    
    std::string cmd_filename = name;
    std::string cmd_filepath = "./output/" + cmd_filename;

    f.open(cmd_filepath.c_str(), std::ios::out);
    f << "set title '" << name <<"' font ', 14'\n";
    f << "set tics font ', 14'\n"; 
    f << "unset key\n";
    f << "plot '" << data_filename << "' w p ps 0.5 pt 22\n";

    f.close();

    std::cout << "Command file written: " << cmd_filename << "\n";
}

void Utils::plot_embed_3D(VS &states, int j, int k, int l, std::string &name)
{

    int size = states.size();

    std::string data_filename = name + ".plt";
    std::string data_filepath = "./output/" + data_filename;

    std::ofstream f;
    f.open(data_filepath.c_str(), std::ios::out);

    double x = 0;
    double y = 0;
    double z = 0;

    for (int i = 0; i < size; ++i) {
        x = states[i].x[j];
        y = states[i].x[k];
        z = states[i].x[l];
        f << x << " " << y << " " << z << "\n";
    }

    f.close();

    std::cout << "Data file written: " << data_filename << "\n";

    std::string cmd_filename = name;
    std::string cmd_filepath = "./output/" + cmd_filename;

    f.open(cmd_filepath.c_str(), std::ios::out);
    f << "set title '" << name <<"' font ', 14'\n";
    f << "set tics font ', 14'\n";
    f << "unset key\n";
    f << "splot '" << data_filename << "' w p ps 0.5 pt 22\n";

    f.close();

    std::cout << "Command file written: " << cmd_filename << "\n";
}
