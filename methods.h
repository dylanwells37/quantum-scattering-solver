// file: potentials.h
//
// Header file for the Potentials C++ class.
//
// Programmer:  Dylan Wells  <wells.1629@osu.edu>
//
//*****************************************************************

#ifndef METHODS_H
#define METHODS_H

#include <string>

class Methods
{
    public:
        Methods(std::string passed_method, double passed_a, double passed_b, double passed_c, double passed_d);
        ~Methods();
        double general(double r);
        double low_energy(double r);
        double spherical(double r);

    private:
        std::string potential;
        double a;
        double b;
        double c;
        double d;
};

#endif