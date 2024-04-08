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
#include <pugixml.hpp>

using namespace std;   
#include "potentials.h"  // Header file for the Potentials class
#include "methods.h"


int check_parameters(char **potential_ptr, char **method_ptr,
                     potential_parameters **potl_params_ptr,
                     method_parameters **method_params_ptr);

int main ()
{
    // Initialize parameters
    char *potential;
    char *method;
    potential_parameters *potl_params = new potential_parameters;
    method_parameters *method_params = new method_parameters;

    // Check to see if the input parameters are valid
    check_parameters(&potential, &method, &potl_params, &method_params);

    cout << "Potential: " << potential << endl;
    cout << "Method: " << method << endl;
    cout << "Potential parameters: " << potl_params->a << " " << potl_params->b << " " << potl_params->c << " " << potl_params->d << endl;
    cout << "Method parameters: " << method_params->m << " " << method_params->k << " " << method_params->theta << " " << method_params->phi << endl;


}

int check_parameters(char **potential_ptr, char **method_ptr,
                     potential_parameters **potl_params_ptr,
                     method_parameters **method_params_ptr){
    
    char *potential;
    char *method;
    // Read in the xml config file
    pugi::xml_document doc;
    if (!doc.load_file("config.xml")) {
        cout << "Could not load config.xml" << endl;
        exit(1);
    }

    pugi::xml_node config = doc.child("config");

    // Set values of potential and method parameters
    *potential_ptr = strdup(config.child_value("potential"));
    *method_ptr = strdup(config.child_value("method"));

    pugi::xml_node potl_params = config.child("potential_parameters");
    (*potl_params_ptr)->a = potl_params.child("a").text().as_double();
    (*potl_params_ptr)->b = potl_params.child("b").text().as_double();
    (*potl_params_ptr)->c = potl_params.child("c").text().as_double();
    (*potl_params_ptr)->d = potl_params.child("d").text().as_double();

    pugi::xml_node method_params = config.child("method_parameters");
    (*method_params_ptr)->m = method_params.child("m").text().as_double();
    (*method_params_ptr)->k = method_params.child("k").text().as_double();
    (*method_params_ptr)->theta = method_params.child("theta").text().as_double();
    (*method_params_ptr)->phi = method_params.child("phi").text().as_double();

    potential = *potential_ptr;
    method = *method_ptr;

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