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
#include "integration.h"
//*****************************************************************

// Constructor for Methods
Method::Method(char *passed_method, method_parameters *passed_parameters){
    method_params = passed_parameters;
    method_params->method = passed_method;
}


// Destructor for Potentials
Method::~Method(){
}

double Method::solve_scattering(){
    // Get the integrand at a given distance r
    // for a given method type
    char *method = method_params->method;
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

    // Define the integrand
    double mass = method_params->m;
    double hbar = method_params->hbar;
    double const front_const = - mass / (2 * M_PI * pow(hbar, 2));

    method_params->integ_params->dimensions = 1;
    
    
    return 0;

}


// Spherical method
double Method::spherical(){
    // return the value of f(theta,phi) for the spherical approximation

    double theta = method_params->theta;
    double phi = method_params->phi;
    double k = method_params->k;
    double hbar = method_params->hbar;
    double mass = method_params->m;
    double kappa = 2 * k * sin(theta / 2);
    double result;
    double error;
    double const front_const = - 2 * mass / (pow(hbar, 2) * kappa);

    // set dimensions of the integral
    method_params->integ_params->dimensions = 1;

    // Create the Integral
    const char *integration_type = "monte_carlo";
    Integration *integ = new Integration(integration_type, method_params);

    // Solve the integral
    result = integ->integrate();
    
    return result;
}


double Method::get_integrand(double r, void * params, double theta, double phi){
    // return the integrand for the given method type
    char *method = method_params->method;
    if (strcmp(method, "born") == 0)
    {
        return born_integrand(r, theta, phi, params);
    }
    else if (strcmp(method, "low_energy") == 0)
    {
        return low_energy_integrand(r, theta, phi, params);
    }
    else if (strcmp(method, "spherical") == 0)
    {
        return spherical_integrand(r, params);
    }
    else
    {
        std::cout << "Invalid method type" << std::endl;
        return 0;
    }
}


double Method::low_energy_integrand(double r, double theta, double phi, void *params){
    // return the integrand for the low energy approximation:
    // V(r) * r^2 * sin(theta)

    method_parameters *params_ptr = (method_parameters *) params;

    Potential *potential_ptr = (Potential *) params_ptr->pot;

    double V = potential_ptr->get_potential(r, theta, phi);
    return V * pow(r, 2) * sin(theta);
}

double Method::spherical_integrand(double r, void *params){
    // return the integrand for the spherical approximation:
    // r * sin(Kr) * V(r)

    // V(r, theta, phi) = V(r)
    method_parameters *params_ptr = (method_parameters *) params;
    
    Potential *potential_ptr = (Potential *) params_ptr->pot;

    double V = potential_ptr->get_potential(r);
    double K = params_ptr->k;

    return r * sin(K * r) * V;
}

double Method::born_integrand(double r, double theta, double phi, void *params){
    return 0;
}