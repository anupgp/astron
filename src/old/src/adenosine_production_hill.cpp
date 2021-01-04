// Time-stamp: <2016-03-23 10:42:44 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Description: This class updates the ado_ext synapse variable from atp_ext using simple Michaelis-Menten kinetics
// Reference: TV. Dunwiddie et al. JNS 1997 

#include <vector>
#include <iostream>
#include <cmath>

#include "insilico/core.hpp"

#include "physical_constants.hpp"
#include "data_types.hpp"
#include "adenosine_production_hill.hpp"

void ado_production_hill::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{

  // Checks if ado_ext variable is present in the synapse
  bool ado_ext_absent = 1;
  unsigned ado_ext_index = newinsilico::get_synapse_index(index, "ado_ext",ado_ext_absent);
  
  // Checks if atp_ext variable is present in the synapse
  bool atp_ext_absent = 1;
  unsigned atp_ext_index = newinsilico::get_synapse_index(index, "atp_ext",atp_ext_absent);
  
  // If any of the below variables are not present in the synapse then exit from function
  if(atp_ext_absent || ado_ext_absent){
    newinsilico::synapse_value(index,"ado_prod_hill_ado_ext_flux",0.0);
    return;
  }

  // Set lower limits on variable values
  variables[atp_ext_index] = std::max<double>(variables[atp_ext_index],0.0);
  variables[ado_ext_index] = std::max<double>(variables[ado_ext_index],0.0);

  // Get variable values
  double atp_ext = variables[atp_ext_index];

  // Get parameter values
  const double v_max = newinsilico::synapse_value(index, "ado_prod_hill_v_max");
  const double k_diss = newinsilico::synapse_value(index, "ado_prod_hill_k_diss");

  // Compute dxdt values
  // Calculate ado production rate from atp_ext using Michaelis-Menten kinetics
  double ado_ext_prod_flux = (v_max * atp_ext) / (k_diss + atp_ext);

  // Writeout dxdt values
  newinsilico::synapse_value(index, "ado_prod_hill_ado_ext_flux", ado_ext_prod_flux);  
}
