// file: potentials.h
//
// Header file for the Potentials C++ class.
//
// Programmer:  Dylan Wells  <wells.1629@osu.edu>
//
//*****************************************************************

#ifndef POTENTIALS_H
#define POTENTIALS_H

#include <string>

class Potentials
{
    public:
        Potentials(std::string passed_potential, double passed_a, double passed_b, double passed_c, double passed_d);
        ~Potentials();
        double coulomb_potential(double r);
        double square_well_potential(double r);
        double gaussian_potential(double r);
        double yukawa_potential(double r);
        double morse_potential(double r);
        double lennard_jones_potential(double r);

    private:
        std::string potential;
        double a;
        double b;
        double c;
        double d;
};

#endif