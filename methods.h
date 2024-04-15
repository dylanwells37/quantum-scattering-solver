// file: methods.h
//
// Header file for the Methods C++ class.
//
// Programmer:  Dylan Wells  <wells.1629@osu.edu>
//
// Revision history: https://github.com/dylanwells37/quantum-scattering-solver
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
    double m; // mass of particle
    double k; // wave number
    double theta; // angle of incidence
    double phi; // azimuthal angle
    char * method; // method type
    void *pot; // pointer to potential parameters
    integration_parameters *integ_params; // pointer to integration parameters
    const char *output_file; // output file name
    double exact; // exact solution if known
};

class Method
{
    public:
        Method(char *passed_method, method_parameters *passed_parameters);
        ~Method();
        double solve_scattering();
        double relative_error(double exact, double approx);

    private:
        method_parameters *method_params;
        double born();
        double low_energy();
        double spherical();
};

#endif