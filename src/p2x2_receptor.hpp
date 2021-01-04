// Time-stamp: <2016-03-15 15:28:01 anup>
// Units: All SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Description: A kinetic model for p2x2 receptor activation using from Moffatt & Hume 2007
// Ref: Moffatt & Hume Jr. Gen, Phys (2007)

#ifndef P2X2_RECEPTOR_HPP_INCLUDED
#define P2X2_RECEPTOR_HPP_INCLUDED

#include "data_types.hpp"

class p2x2_receptor
{
public:
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

#endif
