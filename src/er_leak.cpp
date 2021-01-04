// Time-stamp: <2019-01-05 16:49:49 macbookair>
// Units: All SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Ref: De Young & Keizer PNAS(1992)

#include <vector>
#include <iostream>
#include <cmath>

#include "include/new_insilico.hpp"

#include "data_types.hpp"
#include "physical_constants.hpp"
#include "global_variables.hpp"

#include "er_leak.hpp"

namespace consts=astron::phy_const;
namespace gvars=astron::globals;

void er_leak::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{

  // Get all variable indices
  unsigned ca_cyt_index = newinsilico::get_neuron_index(index, "ca_cyt");
  unsigned ca_er_index = newinsilico::get_neuron_index(index, "ca_er");

  // Get all parameter values
  const double er_leak_flux_coef = newinsilico::neuron_value(index, "er_leak_flux_coef");
 
  // Set lower limits on variable values
  variables[ca_cyt_index] = std::max<double>(variables[ca_cyt_index],0.0);
  variables[ca_er_index] = std::max<double>(variables[ca_er_index],0.0);

  // Get all variable values
  double ca_cyt = variables[ca_cyt_index];
  double ca_er = variables[ca_er_index];

  // --------------------------------------------

  double er_leak_ca_cyt_flux = er_leak_flux_coef * (ca_er - ca_cyt);

  // Update parameter values
  newinsilico::neuron_value(index, "er_leak_ca_cyt_flux", er_leak_ca_cyt_flux);
};
