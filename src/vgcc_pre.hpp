// Time-stamp: <2016-03-15 16:51:33 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads

#ifndef VGCC_PRE_HPP_INCLUDED
#define VGCC_PRE_HPP_INCLUDED

#include "data_types.hpp"

class vgcc_pre
{
public:
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
  static double get_E_Ca(double ca_cyt_, double ca_ext_);
};

#endif
