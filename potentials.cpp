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
//  - wacky potential
//*****************************************************************
// Include Files

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string.h>

#include "potentials.h"

//*****************************************************************

// Constructor for Potentials
Potential::Potential(char *passed_potential, potential_parameters  *passed_parameters){
    potential = passed_potential;
    potl_params = passed_parameters;
}

// Destructor for Potentials
Potential::~Potential(){
}

double Potential::get_potential(double r, double theta, double phi){
    // Get the potential at a given distance r
    // for a given potential type
    if (strcmp(potential, "coulomb") == 0)
    {
        return coulomb_potential(r);
    }
    else if (strcmp(potential, "square_well") == 0)
    {
        return square_well_potential(r);
    }
    else if (strcmp(potential, "wacky") == 0)
    {
        return wacky_potential(r, theta, phi);
    }
    else
    {
        std::cout << "Invalid potential type" << std::endl;
        return 0;
    }

}


// Coulomb potential
double Potential::coulomb_potential(double r){
    // Coulomb potential: V(r) = a/r
    // Will not converge, has an infinite cross-section

    double a = potl_params->a;
    
    return -a/r;
}


// Square well potential
double Potential::square_well_potential(double r){
    // Square well potential: V(r) = -a for r < b, V(r) = 0 for r > b
    
    double a = potl_params->a;
    double b = potl_params->b;

    if (r < b)
    {
        return -a;
    }
    else
    {
        return 0;
    }

}


// Made up potential
double wacky_potential(double r, double theta, double phi){
    return 0;
}
