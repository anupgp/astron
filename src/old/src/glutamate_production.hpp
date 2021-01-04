// Time-stamp: <2016-03-23 10:01:16 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Description: This class is called by a glutamate_synapse class. It simply updates the value of the glu_ext synapse variable if the presynaptic cell has released a glutamate vesicle

#ifndef GLUTAMATE_PRODUCTION_HPP_INCLUDED
#define GLUTAMATE_PRODUCTION_HPP_INCLUDED

#include "data_types.hpp"

class glutamate_production
{
public:
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

#endif
