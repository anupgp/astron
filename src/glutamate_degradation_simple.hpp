// Time-stamp: <2016-03-15 14:14:38 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Description: This class updates the glu_ext_dxdt synapse variable

#ifndef GLUTAMATE_DEGRADATION_SIMPLE_HPP_INCLUDED
#define GLUTAMATE_DEGRADATION_SIMPLE_HPP_INCLUDED

#include "data_types.hpp"

class glutamate_degradation_simple
{
public:
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

#endif	// GLUTAMATE_DEGRADATION_SIMPLE_HPP_INCLUDED
