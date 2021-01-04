// Time-stamp: <2017-09-12 09:52:05 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Ref: di_garbo2007

#ifndef CAP_CA_ENTRY_HPP_INCLUDED
#define CAP_CA_ENTRY_HPP_INCLUDED

#include "data_types.hpp"

class cap_ca_entry
{
public:
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

#endif
