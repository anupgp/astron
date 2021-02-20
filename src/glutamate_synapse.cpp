// Time-stamp: <2021-02-19 22:08:38 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Description: This class calls the other glutamate-related classes to update the dxdt variables 

#include <vector>
#include <iostream>
#include <cmath>

#include "runtime_modifications_synapse.hpp"
#include "data_types.hpp"
#include "physical_constants.hpp"
#include "global_variables.hpp"

// Glutmate synapse specific header files

#include "glutamate_production.hpp"
#include "glutamate_degradation_simple.hpp"
#include "glutamate_synapse.hpp"

void glutamate_synapse::ode_set(state_type &variables, state_type &dxdt, state_type &noise, const double t, unsigned index)
// void glutamate_synapse::ode_set(state_type &variables, state_type &dxdt, const double t, unsigned index)
{

  // Call runtime_modifications function for synapse
  runtime_modifications_synapse::current(variables, dxdt, t, index);
  
  // Checks if glu_ext variable is present 
  bool glu_ext_absent = 1;
  unsigned glu_ext_index = newinsilico::get_synapse_index(index, "glu_ext",glu_ext_absent);

  // Checks if dhpg_ext variable is present 
  bool dhpg_ext_absent = 1;
  unsigned dhpg_ext_index = newinsilico::get_synapse_index(index, "dhpg_ext",dhpg_ext_absent);

  if(glu_ext_absent){
    // std::cout << "No glu_ext1 notfound!" << std::endl;
    return;
  }
  else{
    // std::cout << "glu_ext1 found!" << std::endl;
  }

  // Updates the integration step counter for synapse: only needed for RK4 integration
  // gvars::RK4SYN.counter_update(index,t); 

  // Get dxdt values from other classes
  glutamate_production::current(variables, dxdt, t, index);
  glutamate_degradation_simple::current(variables, dxdt, t, index);      

  // Intermediate dxdt values: glu_ext_deg_dxdt
  double glu_deg_simple_glu_ext_flux = newinsilico::synapse_value(index, "glu_deg_simple_glu_ext_flux");

  // Set lower limits on variable values
  variables[glu_ext_index] = std::max<double>(variables[glu_ext_index],0.0);
  variables[dhpg_ext_index] = std::max<double>(variables[dhpg_ext_index],0.0);
  // std::cout << "t" << " " << t << " " << "index" << " " << index << " " << "glu_ext" << " " << variables[glu_ext_index] << " " << "glu_ext_dxdt" << " " << dxdt[glu_ext_index] << std::endl;
  // if (variables[glu_ext_index] > 10E-06) std::cin.get();

  // Perform dxdt for glu_ext
  dxdt[glu_ext_index] = -glu_deg_simple_glu_ext_flux;
  // Perform dxdt for dhpg_ext
  dxdt[dhpg_ext_index] = 0;

};    
