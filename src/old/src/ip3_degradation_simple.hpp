// Time-stamp: <2016-03-15 14:27:00 anup>
// UNITS: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Ref: Stamastakis & Mantzaris 2006

#ifndef IP3_DEGRADATION_SIMPLE_HPP_INCLUDED
#define IP3_DEGRADATION_SIMPLE_HPP_INCLUDED

#include "data_types.hpp"

class ip3_degradation_simple
{
public:
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

#endif
