// file: methods.h
//
// Header file for the Methods C++ class.
//
// Programmer:  Dylan Wells  <wells.1629@osu.edu>
//
//*****************************************************************

#ifndef METHODS_H
#define METHODS_H

#include <string>
#include "potentials.h"
#include "integration.h"

struct method_parameters
{
    const double hbar = 1.0545718e-34; // J s
    double m;
    double k;
    double theta;
    double phi;
    Potential *pot;
    integration_parameters *integ_params;
};

class Method
{
    public:
        Method(char *passed_method, method_parameters *passed_parameters);
        ~Method();
        double solve_scattering();

    private:
        char * method;
        method_parameters *method_params;
        double born();
        double low_energy();
        double spherical();
        double low_energy_integrand(double r, double theta, double phi, void *params);
        double spherical_integrand(double r, void *params);
        double born_integrand(double r, double theta, double phi, void *params);
};

#endif