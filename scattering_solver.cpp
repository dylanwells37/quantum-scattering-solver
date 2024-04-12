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
#include <string.h>    // C++ strings         
#include <fstream>  
#include <pugixml.hpp> // XML parser

using namespace std;   
#include "potentials.h"  // Header file for the Potential class
#include "methods.h"     // Header file for the Method class
#include "integration.h" // Header file for the Integration class


int check_parameters(string filename,
                     char **potential_ptr, char **method_ptr,
                     potential_parameters **potl_params_ptr,
                     method_parameters **method_params_ptr,
                     integration_parameters **integration_params_ptr);

int main (int argc, char *argv[])
{   
    // Initialize Variables
    string filename = argv[1];
    double result;
    //double error;
    char *potential;
    char *method;
    potential_parameters *potl_params = new potential_parameters;
    method_parameters *method_params = new method_parameters;
    integration_parameters *integ_params = new integration_parameters;

    // Check to see if the input parameters are valid
    // And load the parameters from the config.xml file
    check_parameters(filename, 
                    &potential, &method, 
                    &potl_params, &method_params,
                    &integ_params);

    // Create the potential and method objects
    Potential *pot = new Potential(potential, potl_params);
    method_params->pot = pot;
    method_params->integ_params = integ_params;
    Method *meth = new Method(method, method_params);

    // Solve for the differential cross-section
    result = meth->solve_scattering();

    cout << "The differential cross-section is: " << result << endl;//<< " +/- " << error << endl;

}


int check_parameters(string filename,
                     char **potential_ptr, char **method_ptr,
                     potential_parameters **potl_params_ptr,
                     method_parameters **method_params_ptr,
                     integration_parameters **integration_params_ptr){
    // Read in the xml config file
    char *potential;
    char *method;
    pugi::xml_document doc;
    string filepath = "configs/" + filename;

    if (!doc.load_file(filepath.c_str()))
    {
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
    
    pugi::xml_node potl = config.child("integration_parameters");
    (*integration_params_ptr)->min_radius = potl.child("min_radius").text().as_double();
    (*integration_params_ptr)->max_radius = potl.child("max_radius").text().as_double();
    (*integration_params_ptr)->num_samples = potl.child("num_samples").text().as_int();

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
        strcmp(potential, "wacky") != 0 
        )
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