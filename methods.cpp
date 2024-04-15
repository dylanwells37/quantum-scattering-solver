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
#include <fstream>
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
    //double phi = method_params->phi;
    double k = method_params->k;
    double hbar = method_params->hbar;
    double mass = method_params->m;
    double kappa = 2 * k * sin(theta / 2);
    double monte_result;
    double milne_result;
    //double error;
    double const front_const = - 2 * mass / (pow(hbar, 2) * kappa);

    // set dimensions of the integral
    method_params->integ_params->dimensions = 1;

    // Create the Integrals for monte_carlo and gsl
    Integration *monte_integ = new Integration("monte_carlo", method_params);
    Integration *milne_integ = new Integration("milne", method_params);

    // output file
    std::ofstream output;
    output.open("spherical_output.dat");
     

    // Loop through number of steps N
    for (int num_steps = 2; num_steps <= 1000000; num_steps*=2){
        monte_result = front_const * monte_integ->integrate(num_steps);
        milne_result = front_const * milne_integ->integrate(num_steps);
        output << num_steps << " " << monte_result << " " << milne_result << std::endl;
    }

    output.close();

    return 0;
}

