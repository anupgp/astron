// time-stamp: <2016-01-08 14:57:06 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Ref: Wagner & Keizer Biophysical Jr. (1994)

#include <vector>
#include <iostream>
#include <cmath>

#include "insilico-0.25/include/insilico/core.hpp"

#include "insilico/include/data_types.hpp"
#include "insilico/include/physical_constants.hpp"
#include "insilico/include/astron_global_variables.hpp"

#include "er_buffer.hpp"

namespace consts=astron::phy_const;
namespace gvars=astron::global_vars;

void er_leak::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{

  // Get all variable indices
  unsigned ca_cyt_index = newinsilico::get_neuron_index(index, "ca_cyt");
  unsigned ca_er_index = newinsilico::get_neuron_index(index, "ca_er");
  const double volume_cyt = newinsilico::neuron_value(index, "volume_cyt");
  const double volume_er = newinsilico::neuron_value(index, "volume_er");

  // Get all parameter values
  const double er_leak_flux_coef = newinsilico::neuron_value(index, "er_leak_flux_coef");

 // Set lower limits on variable values
  variables[ca_cyt_index] = std::max<double>(variables[ca_cyt_index],0.0);
  variables[ca_er_index] = std::max<double>(variables[ca_er_index],0.0);

  // Get all variable values
  double ca_cyt = variables[ca_cyt_index];
  double ca_er = variables[ca_er_index];

  // --------------------------------------------

  double ca_flux = er_leak_flux_coef * (ca_er - ca_cyt);
  double er_leak_ca_cyt_dxdt = ca_flux * (volume_er/volume_cyt);
  double er_leak_ca_er_dxdt = - ca_flux * (volume_cyt/volume_er);

  // Update parameter values
  
  newinsilico::neuron_value(index, "er_leak_ca_cyt_dxdt", er_leak_ca_cyt_dxdt);
  newinsilico::neuron_value(index, "er_leak_ca_er_dxdt", er_leak_ca_er_dxdt);
  newinsilico::neuron_value(index, "er_leak_ca_cyt_flux", er_leak_ca_cyt_dxdt);
};
