#ifndef SYSTEMS_H
#define SYSTEMS_H

#include "state.h"

class Pendulum {
private:
    double A; /* amplitude of forcing function */
    double m; /* mass i think */ 
    double l; /* length i think */
    double alpha; /* frequency of the forcing function */
    double beta; /* damping coefficient */
    double g; /* gravity */

public:
    Pendulum();
    Pendulum(double, double, double, double, double, double);

    State operator()(const State &s, double t) const;
};

class Lorenz {
    private:
        double a;
        double b;
        double r;
    public:
        Lorenz();
        Lorenz(double, double, double);

        State operator()(const State &s, double t) const;
};


#endif // !SYSTEMS_H
