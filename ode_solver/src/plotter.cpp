#include "../include/plotter.h"
#include <cmath>

void Plotter::plot_time_series(std::vector<State> &states, std::string &name) {

    int size = states.size();

    std::string data_filename = name + ".plt";
    std::string data_filepath = "/output/" + data_filename;

    std::ofstream f;
    f.open(data_filename.c_str(), std::ios::out);

    for (int i = 0; i < size; ++i) {
        f << states[i].t << " " << states[i].x[0] << "\n";
    }

    f.close();

    std::cout << "Data file written: " << data_filename << "\n";
    
    std::string cmd_filename = name;
    std::string cmd_filepath = "/output/" + cmd_filename;

    f.open(cmd_filename.c_str(), std::ios::out);
    f << "set title '" << name <<"' font ', 16'\n";
    f << "set tics font ', 16'\n"; 
    f << "unset key\n";
    f << "plot '" << data_filename << "' w l lw 4\n";

    f.close();

    std::cout << "Command file written: " << cmd_filename << "\n";
}

void Plotter::plot_2D_state_space(std::vector<State> &states, std::string &name) {

    int size = states.size();

    std::string data_filename = name + ".plt";
    std::string data_filepath = "/output/" + data_filename;

    std::ofstream f;
    f.open(data_filename.c_str(), std::ios::out);

    double theta = 0;
    double prev_theta = 0;

    for (int i = 0; i < size; ++i) {
        theta = states[i].x[0];
        theta = std::fmod(theta, 2 * PI);
        if (std::abs(theta - prev_theta) > 6.) {f << "\n";}
        f << theta << " " << states[i].x[1] << "\n";
        prev_theta = theta;
    }

    f.close();

    std::cout << "Data file written: " << data_filename << "\n";
    
    std::string cmd_filename = name;
    std::string cmd_filepath = "/output/" + cmd_filename;

    f.open(cmd_filename.c_str(), std::ios::out);
    f << "set title '" << name <<"' font ', 14'\n";
    f << "set tics font ', 14'\n"; 
    f << "unset key\n";
    f << "plot '" << data_filename << "' w l lw 1 \n";

    f.close();

    std::cout << "Command file written: " << cmd_filename << "\n";
}

void Plotter::plot_2D_state_space_section(std::vector<State> &states, std::string &name) {

    int size = states.size();

    std::string data_filename = name + ".plt";
    std::string data_filepath = "/output/" + data_filename;

    std::ofstream f;
    f.open(data_filename.c_str(), std::ios::out);

    double theta = 0;
    double prev_theta = 0;
    int half_size = (int) size * 0.5;

    for (int i = half_size; i < size; ++i) {
        theta = states[i].x[0];
        theta = std::fmod(theta, 2 * PI);
        if (std::abs(theta - prev_theta) > 6.) {f << "\n";}
        f << theta << " " << states[i].x[1] << "\n";
        prev_theta = theta;
    }

    f.close();

    std::cout << "Data file written: " << data_filename << "\n";
    
    std::string cmd_filename = name;
    std::string cmd_filepath = "/output/" + cmd_filename;

    f.open(cmd_filename.c_str(), std::ios::out);
    f << "set title '" << name <<"' font ', 14'\n";
    f << "set tics font ', 14'\n"; 
    f << "unset key\n";
    f << "plot '" << data_filename << "' w p ps 0.75 pt 22 \n";

    f.close();

    std::cout << "Command file written: " << cmd_filename << "\n";
}

void Plotter::plot_multiple_2D_state_spaces(std::vector<std::vector<State>> &trajectories, std::string &name)
{
    int traj_size = trajectories.size();
    int state_size = trajectories[0].size();

    std::string data_filename = name + ".plt";
    std::string data_filepath = "/output/" + data_filename;

    std::ofstream f;
    f.open(data_filename.c_str(), std::ios::out);
    double theta = 0;
    double prev_theta = 0;

    for (int j = 0; j < traj_size; ++j) {
        for (int i = 0; i < state_size; ++i) {
            theta = trajectories[j][i].x[0];
            theta = std::fmod(theta, 2 * PI);
            if (std::abs(theta - prev_theta) > 6) {f << "\n";}
            f << theta << " " << trajectories[j][i].x[1] << "\n";
            prev_theta = theta;
        }
        f << "\n";
    }

    f.close();

    std::cout << "Data file written: " << data_filename << "\n";
    
    std::string cmd_filename = name;
    std::string cmd_filepath = "/output/" + cmd_filename;

    f.open(cmd_filename.c_str(), std::ios::out);
    f << "set title '" << name <<"'\n";
    f << "unset key\n";
    f << "plot '" << data_filename << "' w l\n";

    f.close();

    std::cout << "Command file written: " << cmd_filename << "\n";
}

void Plotter::plot_3D_state_space(std::vector<State> &states, std::string &name) {

    int size = states.size();

    std::string data_filename = name + ".plt";
    std::string data_filepath = "/output/" + data_filename;

    std::ofstream f;
    f.open(data_filename.c_str(), std::ios::out);

    for (int i = 0; i < size; ++i) {
        f << states[i].x[0] << " " << states[i].x[1] << " " << states[i].x[2] << "\n";
    }

    f.close();
    cout << "Last time: " << states[size - 1].t << "\n";

    std::cout << "Data file written: " << data_filename << "\n";
    
    std::string cmd_filename = name;
    std::string cmd_filepath = "/output/" + cmd_filename;

    f.open(cmd_filename.c_str(), std::ios::out);
    f << "set title '" << name <<"'\n";
    f << "unset key\n";
    f << "splot '" << data_filename << "' w l\n";

    f.close();

    std::cout << "Command file written: " << cmd_filename << "\n";
}

void Plotter::plot_multiple_3D_state_spaces(std::vector<std::vector<State>> &trajectories, std::string &name)
{
    int traj_size = trajectories.size();
    int state_size = trajectories[0].size();

    std::string data_filename = name + ".plt";
    std::string data_filepath = "/output/" + data_filename;

    std::ofstream f;
    f.open(data_filename.c_str(), std::ios::out);

    for (int j = 0; j < traj_size; ++j) {
        for (int i = 0; i < state_size; ++i) {
            f << trajectories[j][i].x[0] << " " << trajectories[j][i].x[1] << trajectories[j][i].x[2] << "\n";
        }
        f << "\n";
    }

    f.close();

    std::cout << "Data file written: " << data_filename << "\n";
    
    std::string cmd_filename = name;
    std::string cmd_filepath = "/output/" + cmd_filename;

    f.open(cmd_filename.c_str(), std::ios::out);
    f << "set title '" << name <<"'\n";
    f << "unset key\n";
    f << "splot '" << data_filename << "' w l\n";

    f.close();

    std::cout << "Command file written: " << cmd_filename << "\n";
}
