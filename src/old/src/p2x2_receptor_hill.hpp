// Time-stamp: <2016-03-15 15:34:45 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Description: A simple phenomenological model for p2x2 receptor activation using Hill equation
 
#ifndef P2X2_RECEPTOR_HILL_HPP_INCLUDED
#define P2X2_RECEPTOR_HILL_HPP_INCLUDED

#include "data_types.hpp"

class p2x2_receptor_hill
{
public:
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

#endif
