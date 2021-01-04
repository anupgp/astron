// Time-stamp: <2019-01-04 13:50:34 macbookair>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Ref: higgins2006; bartol2015

#ifndef SERCA_HIGG_HPP_INCLUDED
#define SERCA_HIGG_HPP_INCLUDED

#include "data_types.hpp"
#include "include/new_insilico.hpp"

class serca_higg
{
public:
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

#endif
