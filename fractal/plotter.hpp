
#ifndef PLOTTER
#define PLOTTER 

#include "fractal.hpp"

namespace Plotter {

    void plot(const VD &data, const string &title = "Plot") {

        int data_size = data.size();
        if (data_size % 4 != 0){
            std::cerr << "The data file has " << data_size << " entries! \n";
        }

        string data_filename = title + ".plt";

        std::fstream f;
        f.open(data_filename.c_str(), std::ios::out);

        for (int i = 0; i < data_size; i += 4) {
            f << data[i]   << " " << data[i+1] << "\n"
              << data[i+2] << " " << data[i+3] << "\n\n";
        }

        f.close();
        
        string cmd_filename = title;
        f.open(cmd_filename, std::ios::out);
        f << "set grid\n";
        f << "set title '" << title << "'\n";
        f << "unset key\n";
        f << "plot '" << data_filename << "' w l\n";
        

        f.close();
        
        std::cout << "Created command file " << cmd_filename << endl;
    }
}

#endif
