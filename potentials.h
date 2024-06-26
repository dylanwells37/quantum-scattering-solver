// file: potentials.h
//
// Header file for the Potentials C++ class.
//
// Programmer:  Dylan Wells  <wells.1629@osu.edu>
//
// Revision history: https://github.com/dylanwells37/quantum-scattering-solver
//
//*****************************************************************

#ifndef POTENTIAL_H
#define POTENTIAL_H

struct potential_parameters
{
    double a;
    double b;
    double c;
    double d;
    char *potential;
};

#include <string>


class Potential
{
    public:
        Potential(char *passed_potential, potential_parameters  *passed_parameters);
        ~Potential();

        double get_potential(double r, double theta=0, double phi=0);

    private:
        potential_parameters  *potl_params;
        double coulomb_potential(double r);
        double square_well_potential(double r);
        double wacky_potential(double r, double theta, double phi);
};

#endif