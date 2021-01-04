// time-stamp: <2016-01-08 14:57:06 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Ref: Wagner & Keizer Biophysical Jr. (1994)

#ifndef ER_BUFFER_HPP_INCLUDED
#define ER_BUFFER_HPP_INCLUDED

#include "data_types.h"

class er_leak
{
public:
  // Static functions
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

#endif
