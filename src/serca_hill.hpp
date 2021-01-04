// Time-stamp: <2016-03-15 16:55:51 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Ref: Young & Keizer PNAS 1992; J Wade et al. PloS One 2011,

#ifndef SERCA_HILL_HPP_INCLUDED
#define SERCA_HILL_HPP_INCLUDED

#include "data_types.hpp"

class serca_hill
{
public:
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

#endif
