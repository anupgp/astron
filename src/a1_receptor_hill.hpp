// Time-stamp: <2016-03-15 09:59:13 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// "Ref 1: L. Wu & P. Saggau, Neuron (1994)"
// "Ref 2: H. Yawo & N. Chuhma, Nature (1993)"

#ifndef A1_RECEPTOR_HILL_HPP_INCLUDED
#define A1_RECEPTOR_HILL_HPP_INCLUDED

class a1_receptor_hill
{
public:
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

#endif
