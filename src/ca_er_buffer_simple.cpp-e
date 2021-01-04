// Time-stamp: <2019-01-05 16:49:00 macbookair>
// Units: All SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Ref: higgins2006;

#include <vector>
#include <iostream>
#include <cmath>

#include "include/new_insilico.hpp"

#include "data_types.hpp"
#include "physical_constants.hpp"
#include "global_variables.hpp"
#include "ca_er_buffer_simple.hpp"

namespace consts=astron::phy_const;
namespace gvars=astron::globals;

void ca_er_buffer_simple::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{
  // Get all variable indices
  unsigned ca_er_index = newinsilico::get_neuron_index(index, "ca_er");
      
  unsigned c0_index = newinsilico::get_neuron_index(index, "ca_er_buffer_simple_c0");
  unsigned c1_index = newinsilico::get_neuron_index(index, "ca_er_buffer_simple_c1");
  
  // Get all parameter values
  const double kc0c1 = newinsilico::neuron_value(index, "ca_er_buffer_simple_kc0c1");
  const double kc1c0 = newinsilico::neuron_value(index, "ca_er_buffer_simple_kc1c0");

  // Set limits on variable values
  variables[ca_er_index] = std::max<double>(variables[ca_er_index],0.0);
  variables[c0_index] = std::max<double>(variables[c0_index],0.0);
  variables[c1_index] = std::max<double>(variables[c1_index],0.0);

  // Get all variable values
  double ca_er = variables[ca_er_index];

  double c0 = variables[c0_index];
  double c1 = variables[c1_index];

  // Compute dxdt values
  dxdt[c0_index] = (-c0 * ca_er * kc0c1) + (c1 * kc1c0);
  dxdt[c1_index] = (-c1 * kc1c0) + (c0 * ca_er * kc0c1);

  // Compute flux
  double ca_er_buffer_simple_flux = (-c0 * ca_er * kc0c1) + (c1 * kc1c0);

  newinsilico::neuron_value(index, "ca_er_buffer_simple_flux", ca_er_buffer_simple_flux);

}
