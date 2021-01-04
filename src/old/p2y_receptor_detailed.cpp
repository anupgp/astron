// Time-stamp: <2016-12-12 15:11:36 anup>
// Units: All SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Description: A detailed model of P2Y receptor activation
// Note: The change in ATP concentration at individual synapses due to p2y receptors is not taken into account
// Ref 1: garrad1998 (dsen_k_diss, dsen_v_max)
// Ref 2: lemon2003 (dsen)
// Ref 3: flores2005 (dsen)
// Ref 4: otero2000 (dsen)
// Ref 5: centemeri1997 (hill_k_diss)

#include <vector>
#include <iostream>
#include <cmath>

#include "data_types.hpp"
#include "physical_constants.hpp"
#include "global_variables.hpp"

#include "insilico/core.hpp"

namespace consts=astron::phy_const;
namespace gvars=astron::globals;

void p2y_receptor_detailed::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{

  // Get pre_neuron variable indices 

  auto atp_ext_indices = newinsilico::get_pre_neuron_indices(index, "atp_ext");

  // Sum up all atp_ext from all the pre_cell synapses

  double atp_ext = 0.0;
  for(unsigned int iter = 0; iter < atp_ext_indices.size(); ++iter) {
    atp_ext = atp_ext + std::max(variables[atp_ext_indices[iter]],0.0);
  }

  // Get all variable indices
  unsigned ca_cyt_index = newinsilico::get_neuron_index(index, "ca_cyt");
  unsigned p2yr_dsen_frac_index = newinsilico::get_neuron_index(index, "p2yr_hill_dsen_frac");

  // Set lower limits on variable values
  variables[ca_cyt_index] = std::max<double>(variables[ca_cyt_index],0.0);
  variables[p2yr_dsen_frac_index] = std::max<double>(variables[p2yr_dsen_frac_index],0.0);

  // Set upper limits on variable values
  variables[p2yr_dsen_frac_index] = std::min<double>(variables[p2yr_dsen_frac_index],1.0);

  // Get variable values
  double p2yr_dsen_frac = variables[p2yr_dsen_frac_index];

  // Get parameter values
  const double dsen_v_max = newinsilico::neuron_value(index, "p2yr_hill_dsen_v_max");
  const double dsen_k_diss = newinsilico::neuron_value(index, "p2yr_hill_dsen_k_diss");

  const double v_max = newinsilico::neuron_value(index, "p2yr_hill_v_max");
  const double k_diss = newinsilico::neuron_value(index, "p2yr_hill_k_diss");
  const double hill_coop = newinsilico::neuron_value(index, "p2yr_hill_coop");
