// file: potentials.h
//
// Header file for the Potentials C++ class.
//
// Programmer:  Dylan Wells  <wells.1629@osu.edu>
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
};

#include <string>

class Potential
{
    public:
        Potential(char *passed_potential, potential_parameters  *passed_parameters);
        ~Potential();

        double get_potential(double r);

    private:
        char * potential;
        potential_parameters  *potl_params;
        double coulomb_potential(double r);
        double square_well_potential(double r);
        double gaussian_potential(double r);
        double yukawa_potential(double r);
        double morse_potential(double r);
        double lennard_jones_potential(double r);
};

#endif