// file: methods.cpp
//
// Definitions for the Methods C++ class.
//
// Programmer:  Dylan Wells  <wells.1629@osu.edu>
//
// Revision history: https://github.com/dylanwells37/quantum-scattering-solver
//
// Supports:
//  - general
//  - low_energy
//  - spherical
//*****************************************************************
// Include Files

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string.h>
#include <gsl/gsl_integration.h>

#include "methods.h"
#include "potentials.h"
//*****************************************************************

// Constructor for Methods
Method::Method(char *passed_method, method_parameters *passed_parameters){
    method = passed_method;
    method_params = passed_parameters;
}


// Destructor for Potentials
Method::~Method(){
}

double Method::solve_scattering(){
    // Get the integrand at a given distance r
    // for a given method type
    if (strcmp(method, "born") == 0)
    {
        return born();
    }
    else if (strcmp(method, "low_energy") == 0)
    {
        return low_energy();
    }
    else if (strcmp(method, "spherical") == 0)
    {   
        std::cout << "got here" << std::endl;
        return spherical();
    }
    else
    {
        std::cout << "Invalid method type" << std::endl;
        return 0;
    }
}

// General Born Approximation
double Method::born(){
    // return the integrand for the Born approximation
    return 0;
}


// Low energy method
double Method::low_energy(){
    // return the value of f(theta,phi) for the low energy approximation
    // f(theta,phi) =  -m/(2pih^2) * integral[V(r0) d^3r0]
    // where V(r0) is the potential at a distance r0 from the origin

    double const front_const = - method_params->m / (2 * M_PI * pow(method_params->hbar, 2));

    
    
    return 0;

}


// Spherical method
double Method::spherical(){
    // return the integrand for the spherical approximation
    // f(theta,phi) = -2m/(h^2K) * integral[r0 * sin(Kr0) * V(r0) dr0] from 0 to infinity
    
    // define the integrand
    gsl_function F;
    F.function = [](double x, void *params) -> double {
        return static_cast<Method*>(params)->spherical_integrand(x, params);
    };
    F.params = method_params;


    std::cout << "got here 2" << std::endl;
    // define the workspace
    gsl_integration_workspace *w = gsl_integration_workspace_alloc(1000);
    
    // define the integral
    double result, error;
    //gsl_integration_qagiu(&F, 0, 0, 1e-7, 1000, w, &result, &error);

    gsl_integration_qagiu(&F, 0, 0, 1, 100, w, &result, &error);

    std::cout << "got here 3" << std::endl;
    // free the workspace
    gsl_integration_workspace_free(w);

    
    return result;
}


double Method::low_energy_integrand(double r, double theta, double phi, void *params){
    // return the integrand for the low energy approximation:
    // V(r) * r^2 * sin(theta)

    method_parameters *p = (method_parameters *) params;
    double V = p->pot->get_potential(r, theta, phi);
    return V * pow(r, 2) * sin(theta);
}

double Method::spherical_integrand(double r, void *params){
    // return the integrand for the spherical approximation:
    // r * sin(Kr) * V(r)

    // V(r, theta, phi) = V(r)
    method_parameters *p = (method_parameters *) params;
    double V = p->pot->get_potential(r);
    double K = p->k;

    return r * sin(K * r) * V;
}

double Method::born_integrand(double r, double theta, double phi, void *params){
    return 0;
}