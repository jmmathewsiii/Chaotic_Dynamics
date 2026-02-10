#include "../include/plotter.h"

void Plotter::plot_time_series(std::vector<State> &states, std::string &name) {

    int size = states.size();

    std::string data_filename = name + ".plt";
    std::string data_filepath = "/output/" + data_filename;

    std::ofstream f;
    f.open(data_filepath.c_str(), std::ios::out);

    for (int i = 0; i < size; ++i) {
        f << states[i].t << " " << states[i].x[0] << "\n";
    }

    f.close();

    std::cout << "Data file written: " << data_filename << "\n";
    
    std::string cmd_filename = name;
    std::string cmd_filepath = "/output/" + cmd_filename;

    f.open(cmd_filepath.c_str(), std::ios::out);
    f << "set title '" << name <<"'\n";
    f << "unset key\n";
    f << "plot '" << data_filename << "' wl\n";

    f.close();

    std::cout << "Command file written: " << cmd_filename << "\n";
}

void Plotter::plot_2D_state_space(std::vector<State> &states, std::string &name) {

    int size = states.size();

    std::string data_filename = name + ".plt";
    std::string data_filepath = "/output/" + data_filename;

    std::ofstream f;
    f.open(data_filepath.c_str(), std::ios::out);

    for (int i = 0; i < size; ++i) {
        f << states[i].x[0] << " " << states[i].x[1] << "\n";
    }

    f.close();

    std::cout << "Data file written: " << data_filename << "\n";
    
    std::string cmd_filename = name;
    std::string cmd_filepath = "/output/" + cmd_filename;

    f.open(cmd_filepath.c_str(), std::ios::out);
    f << "set title '" << name <<"'\n";
    f << "unset key\n";
    f << "plot '" << data_filename << "' wl\n";

    f.close();

    std::cout << "Command file written: " << cmd_filename << "\n";
}

void Plotter::plot_3D_state_space(std::vector<State> &states, std::string &name) {

    int size = states.size();

    std::string data_filename = name + ".plt";
    std::string data_filepath = "/output/" + data_filename;

    std::ofstream f;
    f.open(data_filepath.c_str(), std::ios::out);

    for (int i = 0; i < size; ++i) {
        f << states[i].x[0] << " " << states[i].x[1] << states[i].x[2] << "\n";
    }

    f.close();

    std::cout << "Data file written: " << data_filename << "\n";
    
    std::string cmd_filename = name;
    std::string cmd_filepath = "/output/" + cmd_filename;

    f.open(cmd_filepath.c_str(), std::ios::out);
    f << "set title '" << name <<"'\n";
    f << "unset key\n";
    f << "splot '" << data_filename << "' wl\n";

    f.close();

    std::cout << "Command file written: " << cmd_filename << "\n";
}
