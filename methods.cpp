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

    // Define the integrand
    double mass = method_params->m;
    double hbar = method_params->hbar;
    double const front_const = - mass / (2 * M_PI * pow(hbar, 2));

    integration_parameters *integ_params = new integration_parameters;
    integ_params = method_params->integ_params;
    integ_params->dimensions = 1;
    
    
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
    //double error;
    double const front_const = - 2 * mass / (pow(hbar, 2) * kappa);

    // Create the integration parameters structure
    integration_parameters *integ_params = new integration_parameters;
    integ_params = method_params->integ_params;
    integ_params->dimensions = 1;

    // Create the integration workspace
    

    
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