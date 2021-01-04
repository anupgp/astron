// Time-stamp: <2019-01-04 13:40:00 macbookair>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Description: A simple phenomenological model for p2x2 receptor activation using Hill equation
 
#include <vector>
#include <iostream>
#include <cmath>

#include "include/new_insilico.hpp"

#include "physical_constants.hpp"
#include "global_variables.hpp"
#include "data_types.hpp"
#include "p2x2_receptor_hill.hpp"

void p2x2_receptor_hill::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
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

  // Set lower limits on variable values
  variables[ca_cyt_index] = std::max(variables[ca_cyt_index],0.0);

  // Get parameter values
  const double v_max = newinsilico::neuron_value(index, "p2x2r_hill_v_max");
  const double k_half = newinsilico::neuron_value(index, "p2x2r_hill_k_half");
  const double hill_coop = newinsilico::neuron_value(index, "p2x2r_hill_coop");

 // Compute dxdt values
  double p2x2r_ca_cyt_flux = v_max * (pow(atp_ext,hill_coop) / (pow(atp_ext,hill_coop) + pow(k_half,hill_coop)));

  newinsilico::neuron_value(index, "p2x2r_hill_ca_cyt_flux", p2x2r_ca_cyt_flux);
}
