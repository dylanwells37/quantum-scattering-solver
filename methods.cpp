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
#include <string>

#include "methods.h"
#include "potentials.h"
//*****************************************************************

// Constructor for Methods
Method::Method(char *passed_method, method_parameters *passed_parameters)
{
    method = passed_method;
    method_params = passed_parameters;
}


// Destructor for Potentials
Method::~Method()
{
}

double Method::get_integrand(double r)
{
    // Get the integrand at a given distance r
    // for a given method type
    if (method == "born")
    {
        return born(r);
    }
    else if (method == "low_energy")
    {
        return low_energy(r);
    }
    else if (method == "spherical")
    {
        return spherical(r);
    }
    else
    {
        std::cout << "Invalid method type" << std::endl;
        return 0;
    }
}

// General Born Approximation
double Method::born(double r)
{
    // return the integrand for the Born approximation
    return 0;
}


// Low energy method
double Method::low_energy(double r)
{
    // return the integrand for the low energy approximation
    // f(theta,phi) =  -m/(2pih^2) * integral[V(r0) d^3r0]
    return 0;
}


// Spherical method
double Method::spherical(double r)
{
    // return the integrand for the spherical approximation
    // f(theta,phi) = -2m/(h^2K) * integral[r0 * sin(Kr0) * V(r0) dr0] from 0 to infinity
    

    return 0;
}
