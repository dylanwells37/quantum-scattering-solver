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

//*****************************************************************

// Constructor for Methods
Methods::Methods(std::string passed_potential, double passed_a, double passed_b, double passed_c, double passed_d)
{
    potential = passed_potential;
    a = passed_a;
    b = passed_b;
    c = passed_c;
    d = passed_d;
}

// Destructor for Potentials
Methods::~Methods()
{
}

// General method
double Methods::general(double r)
{
    return 0;
}


// Low energy method
double Methods::low_energy(double r)
{
    return 0;
}


// Spherical method
double Methods::spherical(double r)
{
    return 0;
}
