#ifndef PLOTTER
#define PLOTTER 

#include"logistic_map.h"

namespace Plotter {

    void discretePlot(const VI &t, const VD &x, const std::string &title = "Plot") {

        if (t.size() != x.size()) {
            std::cerr << "Error: Vectors must be the same size." << std::endl;
            return;
        }

        string data_filename = title + ".plt";

        std::fstream f;
        f.open(data_filename.c_str(), std::ios::out);

        int size = (int) t.size();

        for (int i = 0; i < size; ++i) f << t[i] << " " << x[i] << "\n";

        f.close();
        
        string cmd_filename = title + ".p";
        f.open(cmd_filename, std::ios::out);

        f << "plot '" << data_filename << "' w p" << endl;
        
        std::cout << "Created command file " << cmd_filename << endl;

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
        
        string cmd_filename = title + ".p";
        f.open(cmd_filename, std::ios::out);
        f << "set title '" << title << "'" << endl;
        f << "set grid" << endl;

        f << "plot '" << data_filename << "' w l lw 2" << endl;

        f.close();
        
        std::cout << "Created command file " << cmd_filename << endl;
    }
}

#endif
