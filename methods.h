// file: potentials.h
//
// Header file for the Potentials C++ class.
//
// Programmer:  Dylan Wells  <wells.1629@osu.edu>
//
//*****************************************************************

#ifndef METHODS_H
#define METHODS_H

#include <string>
#include "potentials.h"

struct method_parameters
{
    const double hbar = 1.0545718e-34; // J s
    const double pi = 3.14159265358979323846;
    double m;
    double k;
    double theta;
    double phi;
    Potential *pot;
};

class Method
{
    public:
        Method(char *passed_method, method_parameters *passed_parameters);
        ~Method();
        double get_integrand(double r);

    private:
        char * method;
        method_parameters *method_params;
        double born(double r);
        double low_energy(double r);
        double spherical(double r);
};

#endif