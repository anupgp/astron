// Time-stamp: <2016-03-15 14:29:18 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Ref: De Pitta 2009

#ifndef IP3_KINASE_HILL_HPP_INCLUDED
#define IP3_KINASE_HILL_HPP_INCLUDED

#include "data_types.hpp"

class ip3_kinase_hill
{
public:
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

#endif	// IP3_KINASE_HILL_HPP_INCLUDED
