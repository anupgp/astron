// Time-stamp: <2016-12-14 16:42:54 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Ref: higgins2006; bartol2015

#ifndef SERCA_HIGG_HPP_INCLUDED
#define SERCA_HIGG_HPP_INCLUDED

#include "data_types.hpp"
#include "insilico/core.hpp"
#include "insilico/core/type.hpp"

class serca_higg
{
public:
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

#endif
