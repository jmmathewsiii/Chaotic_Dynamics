#include "fractal.hpp"
#include "plotter.hpp"

const int MAX_ITER = 15;
const double PI = 3.1415926535898;

int main()
{
    VD data = {0, 0, 0, 1};

    double l_angle = PI * 0.333333333333;
    double r_angle = PI * 0.222222222222;

    double llen = 0.7; double rlen = 0.65;

    fractal(data, 'n', 0, 1, l_angle, r_angle, llen, rlen, llen, rlen);

    Plotter::plot(data, "Tree");

}

void fractal(VD &data, char prev_dir, double x0, double y0, double l_angle, double r_angle, double llen, double rlen, double l_ratio, double r_ratio, int iter)
{
    // Even indices contain x values. The following odd indices contain the corresponding y values in the
    // (x, y) pairing.

    if (iter >= MAX_ITER) { return; }
    
    double l_vec[2]; 
    double r_vec[2];
    char l_dir;
    char r_dir;

    switch (prev_dir) {
        case 'n':
        {
            l_dir = 'w'; r_dir = 'e';

            l_vec[0] = -llen; l_vec[1] = 0;
            r_vec[0] =  rlen; r_vec[1] = 0;

            break;
        }
        case 'e':
        {
            l_dir = 'n'; r_dir = 's';

            l_vec[0] = 0; l_vec[1] =  llen;
            r_vec[0] = 0; r_vec[1] = -rlen;

            break;
        }
        case 's':
        {
            l_dir = 'e'; r_dir = 'w';

            l_vec[0] =  llen; l_vec[1] = 0;
            r_vec[0] = -rlen; r_vec[1] = 0;

            break;
        }
        case 'w':
        {
            l_dir = 's'; r_dir = 'n';

            l_vec[0] = 0; l_vec[1] = -llen;
            r_vec[0] = 0; r_vec[1] =  rlen;

            break;
        }
        default:
            std::cerr << "Invalid previous direction: " << prev_dir << "\n";
            return;
    }  

    if (l_angle) {
        double l_sin = sin(l_angle); 
        double l_cos = cos(l_angle); 

        l_vec[0] = l_cos * l_vec[0] - l_sin * l_vec[1];
        l_vec[1] = l_sin * l_vec[0] + l_cos * l_vec[1];
    }
    if (r_angle) {
        double r_sin = sin(r_angle);
        double r_cos = cos(r_angle);

        r_vec[0] = r_cos * r_vec[0] - r_sin * r_vec[1];
        r_vec[1] = r_sin * r_vec[0] + r_cos * r_vec[1];
    }
    
    l_vec[0] += x0; r_vec[0] += x0;
    l_vec[1] += y0; r_vec[1] += y0;

    data.push_back(x0);       data.push_back(y0);
    data.push_back(l_vec[0]); data.push_back(l_vec[1]);

    data.push_back(x0);       data.push_back(y0);
    data.push_back(r_vec[0]); data.push_back(r_vec[1]);


    fractal(data, l_dir, l_vec[0], l_vec[1], l_angle, r_angle, llen * l_ratio, rlen * r_ratio, l_ratio, r_ratio, iter + 1);
    fractal(data, r_dir, r_vec[0], r_vec[1], l_angle, r_angle, llen * l_ratio, rlen * r_ratio, l_ratio, r_ratio, iter + 1);
}











