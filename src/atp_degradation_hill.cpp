// Time-stamp: <2019-01-04 13:24:41 macbookair>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Description: This class updates the atp_ext_deg_dxdt synapse variable: rate of chnage of atp_ext in the extracellular space using classic Michealis-Menten enzymatic kinetics
// Reference: M. Stamatakis & N. Mantzaris JTB 2006

#include <vector>
#include <iostream>
#include <cmath>

#include "include/new_insilico.hpp"

#include "physical_constants.hpp"
#include "global_variables.hpp"
#include "data_types.hpp"
#include "atp_degradation_hill.hpp"

void atp_degradation_hill::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{
  // Checks if atp_ext variable is present in the synapse
  bool atp_ext_absent = 1;
  unsigned atp_ext_index = newinsilico::get_synapse_index(index, "atp_ext",atp_ext_absent);

  // If any of the below variables are not present in the synapse then exit from function
  if(atp_ext_absent){
    newinsilico::synapse_value(index,"atp_deg_hill_atp_ext_flux",0.0);
    return;
  };

  // Set lower limits on variable values
  variables[atp_ext_index] = std::max<double>(variables[atp_ext_index],0.0);

  // Get variable values
  double atp_ext = variables[atp_ext_index];

  // Get parameter values
  const double v_max = newinsilico::synapse_value(index, "atp_deg_hill_v_max");
  const double k_diss = newinsilico::synapse_value(index, "atp_deg_hill_k_diss");

  // Compute dxdt values
  // Calculate atp degradation rate from atp_ext using Michaelis-Menten kinetics
  double atp_ext_deg_flux = (v_max * atp_ext) / (k_diss + atp_ext);

  // Writeout dxdt values
  newinsilico::synapse_value(index, "atp_deg_hill_atp_ext_flux", atp_ext_deg_flux);
}
