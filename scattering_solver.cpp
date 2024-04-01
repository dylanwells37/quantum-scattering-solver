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
#include <string>     // C++ strings         
#include <fstream>  

using namespace std;   

int main (int argc, char *argv[])
{

}