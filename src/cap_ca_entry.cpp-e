// Time-stamp: <2019-01-05 16:49:32 macbookair>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Ref: di_garbo2007

#include <vector>
#include <iostream>
#include <cmath>

#include "include/new_insilico.hpp"

#include "data_types.hpp"
#include "physical_constants.hpp"
#include "global_variables.hpp"
#include "cap_ca_entry.hpp"

namespace consts=astron::phy_const;
namespace gvars=astron::globals;

void cap_ca_entry::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{

  // Get all variable indices
  unsigned ca_er_index = newinsilico::get_neuron_index(index, "ca_er");
  
  // Get all parameter values
  const double v_max = newinsilico::neuron_value(index, "cap_ca_entry_v_max");
  const double k_half = newinsilico::neuron_value(index, "cap_ca_entry_k_half");
  const double coeff = newinsilico::neuron_value(index, "cap_ca_entry_coeff");

  variables[ca_er_index] = std::max<double>(variables[ca_er_index],0.0);

  // Get all variable values
  double ca_er = variables[ca_er_index];

  // --------------------------------------------

  double cap_ca_entry_ca_cyt_flux = v_max * (pow(ca_er,coeff) / (pow(ca_er,coeff) + pow(k_half,coeff)));

  // Update parameter values  
  newinsilico::neuron_value(index, "cap_ca_entry_ca_cyt_flux", cap_ca_entry_ca_cyt_flux);

};
