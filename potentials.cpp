// file: potentials.cpp
//
// Definitions for the Potentials C++ class.
//
// Programmer:  Dylan Wells  <wells.1629@osu.edu>
//
// Revision history: https://github.com/dylanwells37/quantum-scattering-solver
//
// Supports:
//  - coulomb_potential
//  - square_well_potential
//  - gaussian_potential
//  - yukawa_potential
//  - morse_potential
//  - lennard_jones_potential
//*****************************************************************
// Include Files

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

#include "potentials.h"

//*****************************************************************

// Constructor for Potentials
Potentials::Potentials(std::string passed_potential, double passed_a, double passed_b, double passed_c, double passed_d)
{
    potential = passed_potential;
    a = passed_a;
    b = passed_b;
    c = passed_c;
    d = passed_d;
}

// Destructor for Potentials
Potentials::~Potentials()
{
}


// Coulomb potential
double Potentials::coulomb_potential(double r)
{
    return 0
}


// Square well potential
double Potentials::square_well_potential(double r)
{
    return 0;
}


// Gaussian potential
double Potentials::gaussian_potential(double r)
{
    return 0;
}


// Yukawa potential
double Potentials::yukawa_potential(double r)
{
    return 0;
}


// Morse potential
double Potentials::morse_potential(double r)
{
    return 0;
}


// Lennard-Jones potential
double Potentials::lennard_jones_potential(double r)
{
    return 0;
}
