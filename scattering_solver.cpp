//  Program to solve for the differential cross-section of quantum
//  scattering
//
//  Programmer:  Dylan Wells  <wells.1629@osu.edu>
//
//  Revision history: https://github.com/dylanwells37/quantum-scattering-solver
//
//  Notes:
//  
// Three different formulas for f(theta, phi):
// 1. Born approximation
//  f(theta, phi) = -m/(2pih^2) * integral[e^(i(k prime - k) dot r0) * V(r0) d^3r0]
//
// 2. Low energy approximation:
//  f(theta,phi) = -m/(2pih^2) * integral[V(r0) d^3r0]
//
// 3. Spherically symmetric potential:
//  f(theta,phi) = -2m/(h^2K) * integral[sin(Kr0) * V(r0) dr0] from 0 to infinity
//
// I will start by implementing the spherically symmetric as it only has
// one integral to solve. I will then move on to the low energy approximation
// and finally the Born approximation.
//*****************************************************************

#include <iostream>    // cout and cin
#include <iomanip>     // manipulators like setprecision
#include <cmath>
#include <string.h>     // C++ strings         
#include <fstream>  
using namespace std;   
#include "potentials.h"  // Header file for the Potentials class
#include "methods.h"

int check_parameters(int argc, char *argv[], 
                    char **potential, char **method);

int main (int argc, char *argv[])
{
    char *potential = new char[20];
    char *method = new char[20];

    // Check for valid potential
    check_parameters(argc, argv, &potential, &method);

    // Load the potential
    


}

int check_parameters(int argc, char *argv[], 
                    char **potential_ptr, char **method_ptr){
    //
    if (argc != 3) 
    {
        cout << "Usage: scattering_solver <potential> <method>" << endl;
        exit(1);
    }

    // Set the potential and method strings to the passed arguments
    *potential_ptr = argv[1];
    *method_ptr = argv[2];

    char *potential = *potential_ptr;
    char *method = *method_ptr;

    // Check if the potential and method are valid
    if (strcmp(potential, "coulomb") != 0 &&
        strcmp(potential, "square_well") != 0 &&
        strcmp(potential, "gaussian") != 0 &&
        strcmp(potential, "yukawa") != 0 &&
        strcmp(potential, "morse") != 0 &&
        strcmp(potential, "lennard_jones") != 0)
    {
        
        cout << "Invalid potential: " << potential << endl;
        exit(1);
    }

    if (strcmp(method, "spherical") != 0 &&
        strcmp(method, "low_energy") != 0 &&
        strcmp(method, "born") != 0)
    {
        cout << "Invalid method: " << method << endl;

        exit(1);
    }

    return 0;

}