// Time-stamp: <2019-01-05 16:48:43 macbookair>
// Units: All SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Ref: bartol2015; maravall2000;

#include <vector>
#include <iostream>
#include <cmath>

#include "include/new_insilico.hpp"

#include "data_types.hpp"
#include "physical_constants.hpp"
#include "global_variables.hpp"
#include "ca_cyt_dye.hpp"

namespace consts=astron::phy_const;
namespace gvars=astron::globals;

void ca_cyt_dye::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{
  // Get all variable indices
  unsigned ca_cyt_index = newinsilico::get_neuron_index(index, "ca_cyt");
      
  unsigned c0_index = newinsilico::get_neuron_index(index, "ca_cyt_dye_c0");
  unsigned c1_index = newinsilico::get_neuron_index(index, "ca_cyt_dye_c1");
  
  // Get all parameter values
  const double kc0c1 = newinsilico::neuron_value(index, "ca_cyt_dye_kc0c1");
  const double kc1c0 = newinsilico::neuron_value(index, "ca_cyt_dye_kc1c0");

  // Set limits on variable values
  variables[ca_cyt_index] = std::max<double>(variables[ca_cyt_index],0.0);
  variables[c0_index] = std::max<double>(variables[c0_index],0.0);
  variables[c1_index] = std::max<double>(variables[c1_index],0.0);

  // Get all variable values
  double ca_cyt = variables[ca_cyt_index];

  double c0 = variables[c0_index];
  double c1 = variables[c1_index];

  // Compute dxdt values
  dxdt[c0_index] = (-c0 * ca_cyt * kc0c1) + (c1 * kc1c0);
  dxdt[c1_index] = (-c1 * kc1c0) + (c0 * ca_cyt * kc0c1);

  // Compute flux
  double ca_cyt_dye_ca_cyt_flux = (-c0 * ca_cyt * kc0c1) + (c1 * kc1c0);

  newinsilico::neuron_value(index, "ca_cyt_dye_ca_cyt_flux", ca_cyt_dye_ca_cyt_flux);

}
