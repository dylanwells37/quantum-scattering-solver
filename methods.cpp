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
    const char *output_file = method_params->output_file;
    double exact = method_params->exact;
    double monte_result;
    double monte_error;

    method_params->integ_params->dimensions = 3;

    // Create the Integrals for monte_carlo 
    // Currently only monte carlo has 3d integration
    Integration *monte_integ = new Integration("monte_carlo", method_params);

    // output file
    std::ofstream output;
    output.open(output_file);  

    output << "# log10(N)     Monte Carlo Result   log10(Monte Carlo Error)" << std::endl;
    // Loop through number of steps N
    for (int num_steps = 2; num_steps <= 100000000; num_steps*=2){
        std::cout << "Calculating for: " << num_steps << " Steps." << std::endl;
        // only comparing the integrals as the front const is the same for both
        monte_result = monte_integ->integrate(num_steps);
        
        output << log10(num_steps) << " " << monte_result * front_const << " ";

        // check if we have the exact. If so, we can calculate the error
        if (isnan(exact)){
            output << std::endl;
        }
        else{
            monte_error = relative_error(exact, monte_result);
            output << log10(monte_error) << std::endl;
        }

    }

    output.close();

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
    const char *output_file = method_params->output_file;
    double exact = method_params->exact;
    double monte_result;
    double milne_result;
    double monte_error;
    double milne_error;
    double const front_const = - 2 * mass / (pow(hbar, 2) * kappa);

    // set dimensions of the integral
    method_params->integ_params->dimensions = 1;

    // Create the Integrals for monte_carlo and gsl
    Integration *monte_integ = new Integration("monte_carlo", method_params);
    Integration *milne_integ = new Integration("milne", method_params);

    // output file
    std::ofstream output;
    output.open(output_file);  

    output << "# log10(N)     Monte Carlo Result   Milne Result   log10(Monte Carlo Error)   log10(Milne Error)" << std::endl;

    // Loop through number of steps N
    for (int n = 2; n <= 100000000; n*=2){
        int num_steps = 4 * n + 1;
        std::cout << "Calculating for: " << num_steps << " Steps." << std::endl;
        // only comparing the integrals as the front const is the same for both

        monte_result = monte_integ->integrate(num_steps);
        milne_result = milne_integ->integrate(num_steps);
        
        output << log10(num_steps) << " " << monte_result * front_const << " " 
                << milne_result * front_const << " ";

        // check if we have the exact. If so, we can calculate the error
        if (isnan(exact)){
            output << std::endl;
        }
        else{
            monte_error = relative_error(exact, monte_result);
            milne_error = relative_error(exact, milne_result);
            output << log10(monte_error) << " " << log10(milne_error) << std::endl;
        }

    }

    output.close();

    return 0;
}

// Calculate the relative error
double Method::relative_error(double exact, double approx){
    return fabs((exact - approx) / exact);
}

