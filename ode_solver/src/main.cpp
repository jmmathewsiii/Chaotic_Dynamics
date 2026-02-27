#include "../include/plotter.h"
#include "../include/simulation.h"
#include "../include/section.h"

const int    PEND_ARGNUM = 17;
const int  LORENZ_ARGNUM = 15;
const int ROSSLER_ARGNUM = 15;

VS getStartStates(string, double);

int main(int argc, char* argv[])
{
    if (argc != PEND_ARGNUM && argc != LORENZ_ARGNUM && argc != ROSSLER_ARGNUM) {
        std::cerr << "Error: Too few arguments.\n" 
                  << "Expected: " << PEND_ARGNUM << " for pendulum simulation, " << LORENZ_ARGNUM 
                  << " for Lorenz, or " << ROSSLER_ARGNUM << " for Rossler.\n"
                  << "Received: " << argc << "\n";
        return -1;
    }

    string system_type = argv[1];
    string   plot_type = argv[2];
    string    adaptive = argv[3];
    string     section = argv[4];
    double          t0 = std::stod(argv[5]);
    double          dt = std::stod(argv[6]);
    int         n_iter = std::stoi(argv[7]);
    double hyp_plane_t = std::stod(argv[8]);

    string plot_name;

    if (system_type == "pendulum" && argc == PEND_ARGNUM)
    {
        double     A = std::stod(argv[9]);
        double     m = std::stod(argv[10]);
        double     l = std::stod(argv[11]);
        double alpha = std::stod(argv[12]);
        double  beta = std::stod(argv[13]);
        double     g = std::stod(argv[14]);
        double theta = std::stod(argv[15]);
        double omega = std::stod(argv[16]);

        Pendulum pend(A, m, l, alpha, beta, g);

        State start_state(2, t0);
        start_state.x[0] = theta;
        start_state.x[1] = omega;

        if (plot_type == "single")
        {
            VS history;
            plot_name = "Pendulum-State-Space-Plot";
            string ts_plot_name = "TS-Plot";

            if (adaptive == "fixed") {
                history = run_one_sim<Pendulum>(start_state, t0, dt, n_iter, pend);
            }
            else if (adaptive == "adaptive") {
                history = run_one_sim_adaptive<Pendulum>(start_state, t0, dt, n_iter, pend);
            }
            else {
                cerr << "Invalid adaptiveness parameter: " << adaptive << "\n";
            }

            if (section == "section") {
                plot_name = "Pendulum-State-Space-Plot-Section";
                VS section_points = interpolatedTemporalPoincare(history, hyp_plane_t);
                Plotter::plot_2D_state_space_section(section_points, plot_name);
            }
            else if (section == "full") {
                Plotter::plot_2D_state_space(history, plot_name);
            }
            else {
                cerr << "Invalid section parameter: " << section << "\n";
            }
        }
        else if (plot_type == "portrait")
        {
            VS start_states = getStartStates("pendulum", t0);
            start_states.push_back(start_state);
            plot_name = "Pendulum-State-Space-Portrait";
            VSS histories = run_multiple_sims<Pendulum>(start_states, t0, dt, n_iter, pend);
            Plotter::plot_multiple_2D_state_spaces(histories, plot_name);
        }
        else {
            cerr << "Invalid plot type: " << plot_type << "\n";
        }
    }
    else if (system_type == "lorenz" && argc == LORENZ_ARGNUM)
    {
        double a  = std::stod(argv[9]);
        double b  = std::stod(argv[10]);
        double r  = std::stod(argv[11]);
        double x0 = std::stod(argv[12]);
        double y0 = std::stod(argv[13]);
        double z0 = std::stod(argv[14]);

        Lorenz lorenz(a, b, r);
        State start_state(3, t0);
        start_state.x[0] = x0;
        start_state.x[1] = y0;
        start_state.x[2] = z0;

        if (plot_type == "single")
        {
            VS history;

            if (adaptive == "fixed") {
                history = run_one_sim<Lorenz>(start_state, t0, dt, n_iter, lorenz);
                plot_name = "Nonadaptive-Lorenz-State-Space-Plot";
            }
            else if (adaptive == "adaptive") {
                history = run_one_sim_adaptive<Lorenz>(start_state, t0, dt, n_iter, lorenz);
                plot_name = "Adaptive-Lorenz-State-Space-Plot";
            }
            else {
                cerr << "Invalid adaptiveness parameter: " << adaptive << "\n";
            }
            Plotter::plot_3D_state_space(history, plot_name);
        }
        else if (plot_type == "portrait")
        {
            VS start_states = getStartStates("lorenz", t0);
            start_states.push_back(start_state);
            plot_name = "Lorenz-State-Space-Portrait";
            VSS histories = run_multiple_sims<Lorenz>(start_states, t0, dt, n_iter, lorenz);
            Plotter::plot_multiple_3D_state_spaces(histories, plot_name);
        }
        else {
            cerr << "Invalid plot type: " << plot_type << "\n";
        }
    }
    else if (system_type == "variation" && argc == LORENZ_ARGNUM){
        double a  = std::stod(argv[9]);
        double b  = std::stod(argv[10]);
        double r  = std::stod(argv[11]);
        double x0 = std::stod(argv[12]);
        double y0 = std::stod(argv[13]);
        double z0 = std::stod(argv[14]);

        LorenzVariation lorenz(a, b, r);
        State start_state(12, t0);
        start_state.x[0] = x0;
        start_state.x[1] = y0;
        start_state.x[2] = z0;

        start_state.x[3] = 1.;
        start_state.x[4] = 0.;
        start_state.x[5] = 0.;
        
        start_state.x[6] = 0.;
        start_state.x[7] = 1.;
        start_state.x[8] = 0.;

        start_state.x[9] = 0.;
        start_state.x[10] = 0.;
        start_state.x[11] = 1.;

        if (plot_type == "single")
        {
            VS history;

            if (adaptive == "fixed") {
                history = run_one_sim<LorenzVariation>(start_state, t0, dt, n_iter, lorenz);
                plot_name = "Nonadaptive-Lorenz-State-Space-Plot";
                State final = history.back();

                double delta_x_sum = 0.;
                double delta_y_sum = 0.;
                double delta_z_sum = 0.;

                for (int i = 0; i < 3; ++i) {
                   cout << "State[" << i << "] = " << final.x[i] << "\n";
                }
                cout << "\nMatrix of Variations:\n";
                for (int i = 3; i < 6; ++i) 
                {
                    delta_x_sum += final.x[i];
                    delta_y_sum += final.x[i+3];
                    delta_z_sum += final.x[i+6];
                    cout << final.x[i] << "     " << final.x[i+3] << "     " << final.x[i+6] << "\n";
                }
                cout << "\nx variation sum = " << delta_x_sum << "\ny variation sum = " << delta_y_sum
                     << "\nz variation sum = " << delta_z_sum << "\n";
            }
            else if (adaptive == "adaptive") {
                history = run_one_sim_adaptive<LorenzVariation>(start_state, t0, dt, n_iter, lorenz);
                plot_name = "Adaptive-Lorenz-State-Space-Plot";
            }
            else {
                cerr << "Invalid adaptiveness parameter: " << adaptive << "\n";
            }
            Plotter::plot_3D_state_space(history, plot_name);
        }
        else if (plot_type == "portrait")
        {
            VS start_states = getStartStates("lorenz", t0);
            start_states.push_back(start_state);
            plot_name = "Lorenz-State-Space-Portrait";
            VSS histories = run_multiple_sims<LorenzVariation>(start_states, t0, dt, n_iter, lorenz);
            Plotter::plot_multiple_3D_state_spaces(histories, plot_name);
        }
        else {
            cerr << "Invalid plot type: " << plot_type << "\n";
        }
    }
    else if (system_type == "rossler" && argc == ROSSLER_ARGNUM)
    {
        double a  = std::stod(argv[9]);
        double b  = std::stod(argv[10]);
        double c  = std::stod(argv[11]);
        double x0 = std::stod(argv[12]);
        double y0 = std::stod(argv[13]);
        double z0 = std::stod(argv[14]);

        Rossler rossler(a, b, c);
        State start_state(3, t0);
        start_state.x[0] = x0;
        start_state.x[1] = y0;
        start_state.x[2] = z0;

        if (plot_type == "single")
        {
            VS history;
            plot_name = "Rossler-State-Space-Plot";

            if (adaptive == "fixed") {
                history = run_one_sim<Rossler>(start_state, t0, dt, n_iter, rossler);
            }
            else if (adaptive == "adaptive") {
                history = run_one_sim_adaptive<Rossler>(start_state, t0, dt, n_iter, rossler);
            }
            else {
                cerr << "Invalid adaptiveness parameter: " << adaptive << "\n";
            }
            Plotter::plot_3D_state_space(history, plot_name);
        }
        else if (plot_type == "portrait")
        {
            VS start_states = getStartStates("rossler", t0);
            start_states.push_back(start_state);
            plot_name = "Rossler-State-Space-Portrait";
            VSS histories = run_multiple_sims<Rossler>(start_states, t0, dt, n_iter, rossler);
            Plotter::plot_multiple_3D_state_spaces(histories, plot_name);
        }
        else {
            cerr << "Invalid plot type: " << plot_type << "\n";
        }

    }
    else
    {
        cerr << "Invalid system type: " << system_type << "\n";
    }
}


VS getStartStates(string system_type, double t0)
{
    VS start_states;

    if (system_type == "pendulum")
    {
        for (int i = -15; i <= 15; ++i) {
            for (int j = -3; j <= 3; ++j) {
                State curr_state(2, t0);
                curr_state.x[0] = PI * i / 5;
                curr_state.x[1] = j * 0.01;
                start_states.push_back(curr_state);
            }
            State extra_state1(2, t0);
            State extra_state2(2, t0);

            extra_state1.x[0] = PI * i / 5;
            extra_state1.x[1] = 20.5;

            extra_state2.x[0] = PI * i / 5;
            extra_state2.x[1] = -20.5;

            start_states.push_back(extra_state1);
            start_states.push_back(extra_state2);
        }
        for (int i = -2; i <= 2; ++i) {
            for (int j = -3; j <= 3; ++j) {
                State curr_state1(2, t0);
                State curr_state2(2, t0);
                State curr_state3(2, t0);
                State curr_state4(2, t0);

                curr_state1.x[0] = ((PI * i) - 0.25);
                curr_state2.x[0] = ((PI * i) + 0.25);
                curr_state3.x[0] = ((PI * i) - 0.1);
                curr_state4.x[0] = ((PI * i) + 0.1);
                curr_state1.x[1] = j * 0.01;
                curr_state2.x[1] = j * 0.01;
                curr_state3.x[1] = j * 0.01;
                curr_state4.x[1] = j * 0.01;

                start_states.push_back(curr_state1);
                start_states.push_back(curr_state2);
                start_states.push_back(curr_state3);
                start_states.push_back(curr_state4);
            }
        }
    }
    else if (system_type == "lorenz")
    {
        State curr_state(3, t0);
        curr_state.x[0] = 0.;
        curr_state.x[1] = 0.;
        curr_state.x[2] = 0.;
        start_states.push_back(curr_state);
    }
    else if (system_type == "rossler")
    {
        State curr_state(3, t0);
        curr_state.x[0] = 0.;
        curr_state.x[1] = 0.;
        curr_state.x[2] = 0.;
        start_states.push_back(curr_state);
    }
    else {
        cerr << "Invalid system type: " << system_type << "\n";
    }
    return start_states;
}
