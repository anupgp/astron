// Time-stamp: <2017-02-21 11:08:26 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Description: This class calls the other atp-related classes to update the dxdt variables

#ifndef ATP_SYNAPSE_HPP_INCLUDED
#define ATP_SYNAPSE_HPP_INCLUDED

#include "data_types.hpp"

class atp_synapse : public insilico::Synapse
{
public:
  void ode_set(state_type &variables, state_type &dxdt, state_type &noise, const double t, unsigned index);
  // void ode_set(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

#endif // ATP_SYNAPSE_HPP_INCLUDED
