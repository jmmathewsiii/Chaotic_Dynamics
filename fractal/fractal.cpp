#include "fractal.hpp"
#include "plotter.hpp"

int MAX_ITER = 18;

int main()
{
    VD data = {0, 0, 0, 1};

    fractal(data, 0, 1);

    Plotter::plot(data, "Tree");

}

void fractal(VD &data, double x0, double y0, double len, int iter, double p)
{
    // Even indices contain x values. The following odd indices contain the corresponding y values in the
    // (x, y) pairing.
    
    if (iter >= MAX_ITER) {return;}

    switch (iter % 2) {
        case 1: {
            double xl = x0 - len;
            double xr = x0 + len;

            data.push_back(x0); data.push_back(y0);
            data.push_back(xl); data.push_back(y0);

            data.push_back(x0); data.push_back(y0);
            data.push_back(xr); data.push_back(y0);

            fractal(data, xl, y0, len * p, iter + 1);
            fractal(data, xr, y0, len * p, iter + 1);

            break;
        }
        case 0: {
            double yl = y0 - len;
            double yr = y0 + len;

            data.push_back(x0); data.push_back(y0);
            data.push_back(x0); data.push_back(yl);

            data.push_back(x0); data.push_back(y0);
            data.push_back(x0); data.push_back(yr);

            fractal(data, x0, yl, len * p, iter + 1);
            fractal(data, x0, yr, len * p, iter + 1);

            break;
        }
    }
    return;
}
