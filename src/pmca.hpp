// Time-stamp: <2016-03-15 16:42:07 anup>
// UNITS: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads

#ifndef PMCA_HPP_INCLUDED
#define PMCA_HPP_INCLUDED

#include "data_types.hpp"

class pmca
{
public:
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

#endif




