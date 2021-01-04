// Time-stamp: <2016-03-15 14:54:13 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Ref: Ullah, Jung & Bell Cell Calcium (2006)
// Note: The binding and unbinding of glutamate at the receptor will change local glutamate concentration. Currently this is not taken into account. 

#ifndef MGLU_RECEPTOR_HILL_HPP_INCLUDED
#define MGLU_RECEPTOR_HILL_HPP_INCLUDED

#include "data_types.hpp"

class mglu_receptor_hill
{
public:
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

#endif
