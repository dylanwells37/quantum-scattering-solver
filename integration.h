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
    int dimensions;
    double min_radius;
    double max_radius;
    int num_samples;
};

#include <string>
#include "potentials.h"
#include "methods.h"

class Integration
{
    public:
        Integration(const char *passed_method, void *passed_parameters);
        ~Integration();
        double integrate();

    private:
        const char * method;
        void *method_params;
        double gsl_integration();
        double monte_carlo_integration();

};

#endif