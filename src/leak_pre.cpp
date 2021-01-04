// Time-stamp: <2019-01-03 16:54:04 macbookair>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads

#include <vector>
#include <iostream>
#include <cmath>

#include "include/new_insilico.hpp"

#include "data_types.hpp"
#include "leak_pre.hpp"

// leak_pre class definition

void leak_pre::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 

{
  double rev = newinsilico::neuron_value(index,"leak_pre_rev"); // Reversal potential for Potassium currents in Volts
  double gmax = newinsilico::neuron_value(index,"leak_pre_gmax"); // Maximum conductance for Potassium channels S/m^2

  int voltage_index = newinsilico::get_neuron_index(index, "voltage");

  double voltage = variables[voltage_index];
  
  double i_leak = gmax * (voltage -rev);

  newinsilico::neuron_value(index, "leak_pre_current", i_leak);
};
