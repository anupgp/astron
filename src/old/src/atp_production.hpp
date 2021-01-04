// Time-stamp: <2016-03-15 13:28:12 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Description: This class is called by a atp_synapse class. It simply updates the value of the atp_ext synapse variable if the presynaptic cell has released an atp vesicle

#ifndef ATP_PRODUCTION_HPP_INCLUDED
#define ATP_PRODUCTION_HPP_INCLUDED

#include "data_types.hpp"

class atp_production
{
public:
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};


#endif	// ATP_PRODUCTION_HPP_INCLUDED
