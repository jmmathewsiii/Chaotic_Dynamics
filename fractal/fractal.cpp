#include "fractal.hpp"
#include "plotter.hpp"

int MAX_ITER = 18;

int main()
{
    VD data = {0, 0, 0, 1};

    fractal(data, 0, 1);

    Plotter::plot(data, "Tree");

}

void fractal(VD &data, char prev_dir, double x0, double y0, double l_angle, double r_angle, double llen, double rlen, double lp, double rp, int iter)
{
    // Even indices contain x values. The following odd indices contain the corresponding y values in the
    // (x, y) pairing.
    
    double l_vec[2]; 
    double r_vec[2];

    switch (prev_dir) {
        case 'n':
        {
            l_vec[0] = -llen; l_vec[1] = 0;
            r_vec[0] =  rlen; r_vec[1] = 0;
        }
        case 'e':
        {
            l_vec[0] = 0; l_vec[1] =  llen;
            r_vec[0] = 0; r_vec[1] = -rlen;
        }
        case 's':
        {
            l_vec[0] =  llen; l_vec[1] = 0;
            r_vec[0] = -rlen; r_vec[1] = 0;
        }
        case 'w':
        {
            l_vec[0] = 0; l_vec[1] = -llen;
            r_vec[0] = 0; r_vec[1] =  rlen;
        }
        default:
            std::cerr << "Invalid previous direction: " << prev_dir << "\n";
    }

}
