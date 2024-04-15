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
#include <gsl/gsl_integration.h>

#include "integration.h"
#include "methods.h"

//*****************************************************************

// Constructor for Integration Routines
Integration::Integration(const char *passed_method, void *passed_parameters){
    method = passed_method;
    method_params = passed_parameters;
}

// Destructor for Integration Routines
Integration::~Integration(){
}

double Integration::integrate(int num_steps){
    // Integrate a function using the specified method
    if (strcmp(method, "gsl") == 0)
    {
        return gsl_integration(num_steps);
    }
    else if (strcmp(method, "monte_carlo") == 0)
    {
        return monte_carlo_integration(num_steps);
    }
    else if (strcmp(method, "milne") == 0)
    {
        return milne_rule(num_steps);
    }
    else
    {
        std::cout << "Invalid integration method" << std::endl;
        return 0;
    }
}


// gsl integration
double Integration::gsl_integration(int num_steps){
    // Integrate a function using the gsl library
    // define the integrand

    method_parameters *mp_ptr = (method_parameters *) method_params;
    integration_parameters *integ_params = mp_ptr->integ_params;

    //int num_samples = integ_params->num_samples;
    int dimensions = integ_params->dimensions;
    double min_radius = integ_params->min_radius;
    double max_radius = integ_params->max_radius;

    gsl_function F;
    F.function = [](double r, void *params) -> double {
       return static_cast<Integration*>(params)->Integration::get_integrand(r, params);
    };

    F.params = method_params;

    // define the workspace
    gsl_integration_workspace *w = gsl_integration_workspace_alloc(num_steps*1000);
    
    // integrate
    double result, error;

    // integrate( function, a, b, epsabs, epsrel, limit, key, workspace, result, abserr )
    gsl_integration_qag(&F, min_radius, max_radius, 0, 1e-7, num_steps, 6, w, &result, &error);

    // free the workspace
    gsl_integration_workspace_free(w);

    return result;
}

// monte carlo integration
double Integration::monte_carlo_integration(int num_steps){
    // Integrate a function using the monte carlo method
    // Randomly sample points in the integration region
    // and average the function value at those points
    method_parameters *mp_ptr = (method_parameters *) method_params;
    integration_parameters *integ_params = mp_ptr->integ_params;


    int dimensions = integ_params->dimensions;
    //int num_samples = integ_params->num_samples;
    double min_radius = integ_params->min_radius;
    double max_radius = integ_params->max_radius;
    
    double sum = 0;
    double volume = 0;
    double r, rand_theta, rand_phi;
    double result;
    //double error;
    double lower_bound = min_radius;
    double upper_bound = max_radius;

    if (dimensions == 1)
    {
        // 1D monte carlo integration
        for (int i = 0; i < num_steps; i++)
        {
            r = lower_bound + (upper_bound - lower_bound) * rand() / RAND_MAX;
            sum += get_integrand(r, method_params, 0.0, 0.0);
        }
        volume = upper_bound - lower_bound;
        result = (sum / num_steps) * volume;
    }
    else if (dimensions == 3)
    {
        // 3D monte carlo integration
        for (int i = 0; i < num_steps; i++)
        {
            r = lower_bound + (upper_bound - lower_bound) * rand() / RAND_MAX;
            rand_theta = 2 * M_PI * rand() / RAND_MAX;
            rand_phi = M_PI * rand() / RAND_MAX;
            sum += get_integrand(r, method_params, rand_theta, rand_phi);
        }
        volume = 4 * M_PI * pow(max_radius, 3) / 3;
        result = (sum / num_steps) * volume;
    }
    else
    {
        std::cout << "Invalid number of dimensions" << std::endl;
        return 0;
    }

    return result;
}


double Integration::milne_rule (int num_points) {
    /* Calcualte the milne rule estimation for a given integrand,
    num_points, and range */

    method_parameters *mp_ptr = (method_parameters *) method_params;
    integration_parameters *integ_params = mp_ptr->integ_params;


    //int num_samples = integ_params->num_samples;
    double x_min = integ_params->min_radius;
    double x_max = integ_params->max_radius;
    
    double h = (x_max - x_min) / (num_points - 1); // step size
    double sum = 0;

    // add even contribution (always 64h/45 * f(x))
    for (int n = 2; n < num_points; n += 2){
        double x = x_min + h * (n - 1);
        sum += (64.0 / 45.0) * h * get_integrand(x, method_params, 0.0, 0.0);
    }
    // Add odd contributions
    for (int n = 3; n < num_points; n += 4){
        double x = x_min + h * (n - 1);
        sum += (24.0 / 45.0) * h * get_integrand(x, method_params, 0.0, 0.0);
    }
    // add odd contributions counted twice
    for (int n = 5; n < num_points; n+=4){
        double x = x_min + h * (n - 1);
        sum += (28.0 / 45.0) * h * get_integrand(x, method_params, 0.0, 0.0);
    }

    // add endpoint contribution
    sum += (14.0 / 45.0) * h * (get_integrand(x_min, method_params, 0.0, 0.0) + get_integrand(x_max, method_params, 0.0, 0.0));

    return sum;
}


double Integration::get_integrand(double r, void * params, double integ_theta, double integ_phi){
    // return the integrand for the given method type
    method_parameters *params_ptr = (method_parameters *) params;
    const char *chosen_method = params_ptr->method;
    if (strcmp(chosen_method, "born") == 0)
    {
        return born_integrand(r, integ_theta, integ_phi, params);
    }
    else if (strcmp(chosen_method, "low_energy") == 0)
    {
        return low_energy_integrand(r, integ_theta, integ_phi, params);
    }
    else if (strcmp(chosen_method, "spherical") == 0)
    {
        return spherical_integrand(r, params, integ_theta, integ_phi);
    }
    else
    {
        std::cout << "Invalid method type" << std::endl;
        return 0;
    }
}


double Integration::low_energy_integrand(double r, double integ_theta, double integ_phi, void *params){
    // return the integrand for the low energy approximation:
    // V(r) * r^2 * sin(theta)

    method_parameters *params_ptr = (method_parameters *) params;

    Potential *potential_ptr = (Potential *) params_ptr->pot;

    double V = potential_ptr->get_potential(r, integ_theta, integ_phi);
    return V * pow(r, 2) * sin(integ_theta);
}

double Integration::spherical_integrand(double r, void *params, double integ_theta=0.0, double integ_phi=0.0){
    // return the integrand for the spherical approximation:
    // r * sin(Kr) * V(r)

    // V(r, theta, phi) = V(r)
    method_parameters *params_ptr = (method_parameters *) params;
    
    Potential *potential_ptr = (Potential *) params_ptr->pot;

    double V = potential_ptr->get_potential(r);
    double chosen_theta = params_ptr->theta;
    double k = params_ptr->k;
    double kappa = 2 * k * sin(chosen_theta / 2);

    return r * sin(kappa * r) * V;
}

double Integration::born_integrand(double r, double integ_theta, double integ_phi, void *params){
    return 0;
}