## Quantum Scattering Solver

quantum-scattering-solver is a C++ program made to solve for the differnetial cross-section for a given potential in a quantum scattering problem.

This program supports three different methods of solving the for the differential cross-section:

        1. General Born-Approximation (Future Wrok)
        2. Low Energy (Long Wavelength) Born-Approximation
        3. Spherically Symmetric Born-Approximation

The program also supports the following potentials natively:
    
        1. Coulomb Potential
        2. Square Well Potential
        3. Wacky non-physical Potential

## Installation

To install the program, clone the repository and run the following commands inside the repository:

```make -f make_scattering_solver```

This will create an executable called `scattering_solver.x`.

## Usage

To run the program, run the following command:

```./scattering_solver <config>```

Where `<config>` is the name of the configuration file. The configuration file should be a text file with the following format:

## Config File

The configuration file is an xml file with the following format:

```xml
<config> <!-- configuration file for quantum scattering solver -->
    <potential>potential</potential> <!-- coulomb, square-well, wacky -->
    <method>method</method> <!-- low_energy, spherical, born -->
    <potential_parameters> <!-- potential parameters -->
        <a>a</a>  <!-- Constant for coulomb, V for square well-->
        <b>b</b>  <!-- Radius of square well -->
        <c>c</c>  <!-- Add later -->
        <d>d</d>  <!-- Add later -->
    </potential_parameters>
    <method_parameters> <!-- method parameters -->
        <m>mass</m> <!-- mass-->
        <k>wave number</k> <!-- wave number -->
        <theta>theta</theta> <!-- theta angle -->
        <phi>phi</phi> <!-- phi angle -->
    </method_parameters>
    <integration_parameters>
        <n>num_samples</n> <!-- number of integration points -->
        <r_min>min radius</r_min> <!-- minimum radius -->
        <r_max>max radius</r_max> <!-- maximum radius -->
    </integration_parameters>
    <output> <!-- output parameters -->
        <file>output.dat</file> <!-- output file name-->
    </output>
</config>
```

There are sample config files to choose from in the config directory.


## Examples

To run the program with the sample square well configuration, run the following command:

```./scattering_solver square_well_config.xml```

## Physics / Math

The program uses the following formulas to solve for the differential cross-section:

1. General Born-Approximation (Future Work)
2. Low Energy (Long Wavelength) Born-Approximation
3. Spherically Symmetric Born-Approximation

### Sphericallly-Symmetric Born-Approximation

The differential cross-section for the low energy Born-Approximation is given by:

```dσ/dΩ = |f(θ)|^2```

Where `f(θ)` is the scattering amplitude given by:

```f(θ) = -2mV0/(ħ^2 * k) * ∫[0,∞] sin(kr) * V(r) * r dr```

### Low Energy (Long Wavelength) Born-Approximation
