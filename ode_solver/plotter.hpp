#ifndef PLOTTER
#define PLOTTER 

#include "solver.hpp"

namespace Plotter {

    void discretePlot(const VI &t, const VD &x, const std::string &title = "Plot") {

        if (t.size() != x.size()) {
            std::cerr << "Error: Vectors must be the same size.\n";
            return;
        }

        string data_filename = title + ".plt";

        std::fstream f;
        f.open(data_filename.c_str(), std::ios::out);

        int size = (int) t.size();

        for (int i = 0; i < size; ++i) f << t[i] << " " << x[i] << "\n";

        f.close();
        
        string cmd_filename = title;
        f.open(cmd_filename, std::ios::out);

        f << "set grid\n";
        f << "set yrange [-0.1:1.1]\n";
        f << "set title '" << title << "'\n";
        f << "unset key\n";
        f << "plot '" << data_filename << "' w p pt 157 ps 0.5 \n";
        
        std::cout << "Created command file " << cmd_filename << "\n";

        f.close();
    }
    
    void contPlot(const VD &x, const VD &y, const std::string &title = "Plot") {

        if (x.size() != y.size()) {
            std::cerr << "Error: Vectors must be the same size." << std::endl;
            return;
        }

        string data_filename = title + ".plt";

        std::fstream f;
        f.open(data_filename.c_str(), std::ios::out);

        int size = (int) x.size();

        for (int i = 0; i < size; ++i) f << x[i] << " " << y[i] << "\n";

        f.close();
        
        string cmd_filename = title;
        f.open(cmd_filename, std::ios::out);
        f << "set grid" << endl;
        f << "set xrange [-0.1:1.1]\n";
        f << "set yrange [-0.1:1.1]\n";
        f << "set title '" << title << "'\n";
        f << "unset key" << endl;
        f << "plot '" << data_filename << "' w p pt 157 ps 0.5" << endl;
        

        f.close();
        
        std::cout << "Created command file " << cmd_filename << endl;
    }
}
#endif
