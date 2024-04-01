## Quantum Scattering Solver

quantum-scattering-solver is a C++ program made to solve for the differnetial cross-section for a given potential in a quantum scattering problem.

This program supports three different methods of solving the for the differential cross-section (WIP):

        1. General Born-Approximation
        2. Low Energy (Long Wavelength) Born-Approximation
        3. Spherically Symmetric Born-Approximation

The program also supports the following potentials natively (WIP):
    
        1. Coulomb Potential
        2. Square Well Potential
        3. Gaussian Potential
        4. Yukawa Potential
        5. Morse Potential
        6. Lennard-Jones Potential

## Installation

To install the program, clone the repository and run the following commands inside the repository:

```make -f make_scattering_solver```

This will create an executable called `scattering_solver`.

## Usage

To run the program, run the following command:

```./scattering_solver <potential> <method> <parameters> -t <theta> -p <phi>```

Where `<potential>` is the potential you want to use, `<method>` is the method you want to use, and `<parameters>` are the parameters for the potential. 

The `-t` and `-p` flags are optional and are used to specify the angles theta and phi for the scattering.

## Examples

To run the program with the Coulomb potential using the General Born-Approximation method, run the following command:

```./scattering_solver coulomb general 1 -t 0 -p 0```

To run the program with the Square Well potential using the Low Energy Born-Approximation method, run the following command:

```./scattering_solver square_well low 1 1 -t 0 -p 0```

## All cmdline potentials and methods

### Potentials

        1. coulomb
        2. square_well
        3. gaussian
        4. yukawa
        5. morse
        6. lennard_jones

### Methods
    
            1. general
            2. low
            3. spherical
