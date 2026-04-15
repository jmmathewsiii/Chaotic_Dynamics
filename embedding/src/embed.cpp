#include "../include/embed.h"
#include <cmath>

VS Embed::build(VD& xvals, VD& tvals, double tau, int m)
{
    VS result;

    double dt = tvals[1] - tvals[0];
    std::cout << "dt = " << dt << "\n";
    std::size_t step = (std::size_t)std::round(tau / dt);
    if (step == 0) step = 1;
    std::cout << "Step = " << step << "\n";

    std::size_t span = (std::size_t)(m - 1) * step;
    std::cout << "Span = " << span << "\n";
    std::size_t n = xvals.size();

    for (std::size_t i = 0; i + span < n; ++i)
    {
        State s(m, tvals[i]);
        for (int c = 0; c < m; ++c)
            s.x[c] = xvals[i + (std::size_t)c * step];
        result.push_back(s);
    }

    return result;
}
