// Time-stamp: <2017-03-04 11:48:27 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads

#include <vector>
#include <iostream>
#include <cmath>

#include "insilico/core.hpp"

#include "data_types.hpp"
#include "k_pre.hpp"

// k_pre class definition

void k_pre::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{
  double rev = newinsilico::neuron_value(index,"k_pre_rev"); // Reversal potential for Potassium currents in Volts
  double gmax = newinsilico::neuron_value(index,"k_pre_gmax"); // Maximum conductance for Potassium channels S/m^2

  unsigned voltage_index = newinsilico::get_neuron_index(index, "voltage");
  unsigned n_index = newinsilico::get_neuron_index(index, "k_pre_n");
  
  variables[n_index] = std::max(variables[n_index],0.0);
  variables[n_index] = std::min(variables[n_index],1.0);
  
  double voltage = variables[voltage_index] * 1e03;
  double n = variables[n_index];

  double alpha_n = ( -0.01e03 * (voltage + 55) / ( exp( -(voltage +  55) / 10) - 1.0 ) );
  double beta_n =  (0.125e03 * exp (- (voltage + 65) / 80) );
    
  dxdt[n_index] =  ( (alpha_n * (1-n)) - (beta_n * n) );
  double i_k = gmax * std::pow(n, 4) * ((voltage*1e-3) - rev);

  newinsilico::neuron_value(index, "k_pre_current", i_k);
};
