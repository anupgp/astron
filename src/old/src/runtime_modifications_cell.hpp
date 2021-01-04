// Time-stamp: <2017-03-04 11:55:54 anup>
// Units: All SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Description: This file will contain all the codes which will modify the variables or parameters at run time
// This script will implement the call to dynamic parameters and external currents

#ifndef RUNTIME_MODIFICATIONS_CELL_HPP_INCLUDED
#define RUNTIME_MODIFICATIONS_CELL_HPP_INCLUDED

#include "data_types.hpp"

class runtime_modifications_cell
{
public:
  static void current(state_type &variables, const state_type &dxdt, const double t, const unsigned index);
};


#endif
