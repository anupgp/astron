// Time-stamp: <2018-02-26 11:00:40 anup>
// Units: All SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Description: This file will contain all the codes which will modify the variables or parameters at run time
// This script will implement the call to dynamic parameters and external currents

#ifndef WRITING_CONDITIONS_HPP_INCLUDED
#define WRITING_CONDITIONS_HPP_INCLUDED

#include "data_types.hpp"

class writing_conditions
{
public:
  static void current(state_type &variables, const state_type &dxdt, const double t, const unsigned index);
};


#endif
