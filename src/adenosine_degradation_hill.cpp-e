// Time-stamp: <2019-01-04 13:17:48 macbookair>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Description: This class updates the ado_ext_deg_dxdt synapse variable
// Reference: M. Stamatakis & N. Mantzaris JTB 2006

#include <vector>
#include <iostream>
#include <cmath>

#include "include/new_insilico.hpp"

#include "physical_constants.hpp"
#include "data_types.hpp"
#include "adenosine_degradation_hill.hpp"

void ado_degradation_hill::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{
  // Checks if atp_ext variable is present in the synapse
  bool ado_ext_absent = 1;
  unsigned ado_ext_index = newinsilico::get_synapse_index(index, "ado_ext",ado_ext_absent);

  // If any of the below variables are not present in the synapse then exit from function
  if(ado_ext_absent){
    newinsilico::synapse_value(index,"ado_deg_hill_ado_ext_flux",0.0);
    return;
  }

  // Set lower limits on variable values
  variables[ado_ext_index] = std::max<double>(variables[ado_ext_index],0.0);

  // Get variable values
  double ado_ext = variables[ado_ext_index];

  // Get parameter values
  const double v_max = newinsilico::synapse_value(index, "ado_deg_hill_v_max");
  const double k_diss = newinsilico::synapse_value(index, "ado_deg_hill_k_diss");

  // Compute dxdt values
  double ado_ext_deg_flux = (v_max * ado_ext) / (k_diss + ado_ext);

  // Writeout dxdt values
  newinsilico::synapse_value(index, "ado_deg_hill_ado_ext_flux", ado_ext_deg_flux);
}
