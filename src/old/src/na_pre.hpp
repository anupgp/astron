// Time-stamp: <2017-03-04 11:46:26 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Model from Dominique Engel & Preter Jonas 2005

#ifndef NA_PRE_HPP_INCLUDED
#define NA_PRE_HPP_INCLUDED

#include "insilico/core.hpp"
#include "data_types.hpp"

// na_pre class declaration
class na_pre
{
public:
  void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

#endif
