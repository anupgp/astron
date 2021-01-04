// Time-stamp: <2016-03-15 13:39:11 anup>
// Units: All SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Ref: De Young & Keizer PNAS(1992)

#ifndef ER_LEAK_HPP_INCLUDED
#define ER_LEAK_HPP_INCLUDED

#include "data_types.hpp" 

class er_leak
{
public:
  // Static functions
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

#endif // ER_LEAK_HPP_INCLUDED
