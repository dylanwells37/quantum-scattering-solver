// file: methods.h
//
// Header file for the Methods C++ class.
//
// Programmer:  Dylan Wells  <wells.1629@osu.edu>
//
//*****************************************************************

#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <string>
//#include "potentials.h"

struct integration_parameters
{
    double min_radius;
    double max_radius;
    double num_samples;
    void *method_params;
};


class Integration
{
    public:
        Integration(char *passed_method, method_parameters *passed_parameters);
        ~Integration();

    private:
        char * method;
        integ_params;
};

#endif