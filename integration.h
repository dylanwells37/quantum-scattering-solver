// file: methods.h
//
// Header file for the Methods C++ class.
//
// Programmer:  Dylan Wells  <wells.1629@osu.edu>
//
// Revision history: https://github.com/dylanwells37/quantum-scattering-solver
//
//*****************************************************************

#ifndef INTEGRATION_H
#define INTEGRATION_H

struct integration_parameters
{
    int dimensions; // 1 or 3
    double min_radius; // minimum radius
    double max_radius; // maximum radius
    int num_samples; // number of samples
};

#include <string>
#include "potentials.h"
#include "methods.h"

class Integration
{
    public:
        Integration(const char *passed_method, void *passed_parameters);
        ~Integration();
        double integrate(int num_steps);

    private:
        const char * method;
        void *method_params;
        double gsl_integration(int num_steps);
        double monte_carlo_integration(int num_steps);
        double milne_rule(int num_steps);
        double get_integrand(double r, void *method_params, double theta=0, double phi=0);
        double low_energy_integrand(double r, double integ_theta, double integ_phi, void *params);
        double spherical_integrand(double r, void *params, double integ_theta, double integ_phi);
        double born_integrand(double r, double integ_theta, double integ_phi, void *params);
};

#endif