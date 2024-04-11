// file: integration.cpp
//
// Definitions for the Integration C++ class.
//
// Programmer:  Dylan Wells  <wells.1629@osu.edu>
//
// Revision history: https://github.com/dylanwells37/quantum-scattering-solver
//
// Supports:
//  - 1D gsl integration
//  - 1D monte carlo integration
//  - 3D monte carlo integration
//*****************************************************************
// Include Files

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string.h>

#include "integration.h"
#include "methods.h"

//*****************************************************************

// Constructor for Integration Routines
Integration::Integration(char *passed_method, method_parameters *passed_parameters){
    method = passed_method;
    method_parameters = passed_parameters;
    integ_params = passed_parameters->integ_params;
}

// Destructor for Integration Routines
Integration::~Integration(){
}

Integration::integrate(){
    // Integrate a function using the specified method
    if (strcmp(method, "gsl") == 0)
    {
        return gsl_integration();
    }
    else if (strcmp(method, "monte_carlo") == 0)
    {
        return monte_carlo_integration();
    }
    else
    {
        std::cout << "Invalid integration method" << std::endl;
        return 0;
    }
}


// gsl integration
double Integration::gsl_integration(){
    // Integrate a function using the gsl library
    // define the integrand

    void *method_params = integ_params->method_params;
    int num_samples = integ_params->num_samples;
    int dimensions = integ_params->dimensions;
    double min_radius = integ_params->min_radius;
    double max_radius = integ_params->max_radius;
    double (*integrand)(double, void *) = integ_params->integrand;


    gsl_function F;
    //F.function = [](double x, void *params) -> double {
     //   return static_cast<Method*>(params)->spherical_integrand(x, params);
    //};

    F.function = [](double x, void *params) -> double {
        return *integrand(x, params);
    };

    F.params = method_params;

    // define the workspace
    gsl_integration_workspace *w = gsl_integration_workspace_alloc(num_samples);
    
    // integrate
    double result, error;

    // integrate( function, a, b, epsabs, epsrel, limit, key, workspace, result, abserr )
    gsl_integration_qag(&F, min_radius, max_radius, 0, 1e-7, num_samples, 6, w, &result, &error);

    // free the workspace
    gsl_integration_workspace_free(w);

    return result;
}

// monte carlo integration
double Integration::monte_carlo_integration(){
    // Integrate a function using the monte carlo method
    // Randomly sample points in the integration region
    // and average the function value at those points
    
    int dimensions = integ_params->dimensions;
    int num_samples = integ_params->num_samples;
    double min_radius = integ_params->min_radius;
    double max_radius = integ_params->max_radius;
    double (*integrand)(double, void *) = integ_params->integrand;
    void *method_params = integ_params->method_params;

    double sum = 0;
    double volume = 0;
    double r, theta, phi;
    double result;
    //double error;
    double lower_bound = min_radius;
    double upper_bound = max_radius;
    
    if (dimensions == 1)
    {
        // 1D monte carlo integration
        for (int i = 0; i < num_samples; i++)
        {
            r = lower_bound + (upper_bound - lower_bound) * rand() / RAND_MAX;
            sum += *integrand(r, method_params);
        }
        volume = upper_bound - lower_bound;
        result = (sum / num_samples) / volume;
    }
    else if (dimensions == 3)
    {
        // 3D monte carlo integration
        for (int i = 0; i < num_samples; i++)
        {
            r = lower_bound + (upper_bound - lower_bound) * rand() / RAND_MAX;
            theta = 2 * M_PI * rand() / RAND_MAX;
            phi = M_PI * rand() / RAND_MAX;
            sum += *integrand(r, theta, phi, method_params);
        }
        volume = 4 * M_PI * pow(max_radius, 3) / 3;
        result = (sum / num_samples) / volume;
    }
    else
    {
        std::cout << "Invalid number of dimensions" << std::endl;
        return 0;
    }

    return result;
}