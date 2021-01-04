// Time-stamp: <2019-01-04 10:46:59 macbookair>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Description: This class calls the other atp-related classes to update the dxdt variables

#include <vector>
#include <iostream>
#include <cmath>

#include "include/new_insilico.hpp"

#include "data_types.hpp"
#include "physical_constants.hpp"
#include "global_variables.hpp"

#include "runtime_modifications_synapse.hpp"

// ATP synapse specific header files

#include "atp_production.hpp"
#include "atp_degradation_hill.hpp"
#include "adenosine_production_hill.hpp"
#include "adenosine_degradation_hill.hpp"

#include "atp_synapse.hpp"

namespace gvars=astron::globals;

void atp_synapse::ode_set(state_type &variables, state_type &dxdt, state_type &noise, const double t, unsigned index)
// void atp_synapse::ode_set(state_type &variables, state_type &dxdt, const double t, unsigned index)
{
 
  // Call runtime_modifications function for synapse
  runtime_modifications_synapse::current(variables, dxdt, t, index);
  
  // Checks if atp_ext variable is present 
  bool atp_ext_absent = 1;
  unsigned atp_ext_index = newinsilico::get_synapse_index(index, "atp_ext",atp_ext_absent);

  if(atp_ext_absent){
    return;
  }

  // Get dxdt values from other classes
  atp_production::current(variables, dxdt, t, index);
  atp_degradation_hill::current(variables, dxdt, t, index);      

  // Intermediate dxdt values: atp_ext_deg_dxdt
  double atp_deg_hill_atp_ext_flux = newinsilico::synapse_value(index, "atp_deg_hill_atp_ext_flux");

  // Set lower limits on variable values
  variables[atp_ext_index] = std::max<double>(variables[atp_ext_index],0.0);
  
  // Perform dxdt for atp_ext
  dxdt[atp_ext_index] = -atp_deg_hill_atp_ext_flux;
  // dxdt[atp_ext_index] = 0.0;

  // Checks if ado_ext variable is present 
  bool ado_ext_absent = 1;
  unsigned ado_ext_index = newinsilico::get_synapse_index(index, "ado_ext",ado_ext_absent);

  if(ado_ext_absent){
    return;
  }

  // Get dxdt values from other classes
  ado_production_hill::current(variables, dxdt, t, index);
  ado_degradation_hill::current(variables, dxdt, t, index);      

  // Intermediate dxdt values: ado_ext_prod_dxdt
  double ado_prod_hill_ado_ext_flux = newinsilico::synapse_value(index, "ado_prod_hill_ado_ext_flux");

  // Intermediate dxdt values: ado_ext_deg_dxdt
  double ado_deg_hill_ado_ext_flux = newinsilico::synapse_value(index, "ado_deg_hill_ado_ext_flux");
  
  // Perform dxdt for ado_ext
  dxdt[ado_ext_index] = -ado_deg_hill_ado_ext_flux + ado_prod_hill_ado_ext_flux;

};    
