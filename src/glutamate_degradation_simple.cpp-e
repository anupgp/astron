// Time-stamp: <2019-01-04 13:31:30 macbookair>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Description: This class updates the glu_ext_dxdt synapse variable

#include <vector>
#include <iostream>
#include <cmath>

#include "include/new_insilico.hpp"

#include "physical_constants.hpp"
#include "global_variables.hpp"
#include "data_types.hpp"
#include "glutamate_degradation_simple.hpp"

void glutamate_degradation_simple::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{

  // Checks if glu_ext variable is present in the synapse
  bool glu_ext_absent = 1;
  unsigned glu_ext_index = newinsilico::get_synapse_index(index, "glu_ext",glu_ext_absent);

  // If any of the below variables are not present in the synapse then exit from function
  if(glu_ext_absent){
    newinsilico::synapse_value(index,"glu_deg_simple_glu_ext_flux",0.0);
    return;
  }

  // Set lower limits on variable values
  variables[glu_ext_index] = std::max<double>(variables[glu_ext_index],0.0);

  // Get variable values
  double glu_ext = variables[glu_ext_index];

  // Get parameter values
  const double glu_clearance = newinsilico::synapse_value(index, "glu_deg_simple_spillover");

  // Compute dxdt values
  double glu_ext_deg_flux = (glu_ext * glu_clearance);

  // Writeout dxdt values
  newinsilico::synapse_value(index, "glu_deg_simple_glu_ext_flux", glu_ext_deg_flux);
};
