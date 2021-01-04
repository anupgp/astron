// Time-stamp: <2019-01-03 16:51:53 macbookair>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Description: This class calls the other glutamate-related classes to update the dxdt variables 

#ifndef GLUTAMATE_SYNAPSE_HPP_INCLUDED
#define GLUTAMATE_SYNAPSE_HPP_INCLUDED

#include "data_types.hpp"
#include "include/new_insilico.hpp"

namespace gvars=astron::globals;

class glutamate_synapse : public newinsilico::Synapse
{
public:
  void ode_set(state_type &variables, state_type &dxdt, state_type &noise, const double t, unsigned index);
  // void ode_set(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

#endif // GLUTAMATE_SYNAPSE_HPP_INCLUDED
