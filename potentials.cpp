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
#include <string.h>

#include "potentials.h"

//*****************************************************************

// Constructor for Potentials
Potentials::Potentials(char *passed_potential, potential_parameters  *passed_parameters)
{
    potential = passed_potential;
    parameters = passed_parameters;
}

// Destructor for Potentials
Potentials::~Potentials()
{
    // Destructor
}

double Potentials::get_potential(double r)
{
    if (potential == "coulomb")
    {
        return coulomb_potential(r);
    }
    else if (potential == "square_well")
    {
        return square_well_potential(r);
    }
    else if (potential == "gaussian")
    {
        return gaussian_potential(r);
    }
    else if (potential == "yukawa")
    {
        return yukawa_potential(r);
    }
    else if (potential == "morse")
    {
        return morse_potential(r);
    }
    else if (potential == "lennard_jones")
    {
        return lennard_jones_potential(r);
    }
    else
    {
        std::cout << "Invalid potential" << std::endl;
        exit(1);
    }

}


// Coulomb potential
double Potentials::coulomb_potential(double r)
{
    // Coulomb potential: V(r) = a/r
    double a = parameters->a;
    
    return -a/r;
}


// Square well potential
double Potentials::square_well_potential(double r)
{
    // Square well potential: V(r) = -a for r < b, V(r) = 0 for r > b
    double a = parameters->a;
    double b = parameters->b;

    if (r < b)
    {
        return -a;
    }
    else
    {
        return 0;
    }

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
