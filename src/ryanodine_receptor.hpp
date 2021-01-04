// Time-stamp: <2016-03-15 17:00:37 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Ref: Saftenku, William & Sitsapesan, Biophysical Jr. (2001)
// Note: Number of RYR receptors = 1. Number of RYR receptors are taken into account by the maximum flux parameter.
// Note: Change in ca_cyt concentration due to binding with RYR receptor is not considered.

#ifndef RYANODINE_RECEPTOR_HPP_INCLUDED
#define RYANODINE_RECEPTOR_HPP_INCLUDED

#include "data_types.hpp"

class ryanodine_receptor
{
public:
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

#endif
