#ifndef PLOTTER
#define PLOTTER 

#include"logistic_map.h"

namespace Plotter {

    void plot(const VI &t, const VD &x, const std::string &title = "Plot") {

        if (t.size() != x.size()) {
            std::cerr << "Error: Vectors must be the same size." << std::endl;
            return;
        }

        string filename = title + ".plt";

        std::fstream f;
        f.open(filename.c_str(), std::ios::out);

        int size = (int) t.size();

        for (int i = 0; i < size; ++i) f << t[i] << " " << x[i] << "\n";

        f.close();
        
        std::cout << "Writing gnuplot command file 'pc'" << std::endl;

        f.open("pc", std::ios::out);

        f << "plot '" << filename << "'" << endl;
        f.close();
    }
}

#endif
