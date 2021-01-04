// Time-stamp: <2019-01-04 13:32:11 macbookair>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Description: This class is called by a glutamate_synapse class. It simply updates the value of the glu_ext synapse variable if the presynaptic cell has released a glutamate vesicle

#include <vector>
#include <iostream>
#include <cmath>

#include "include/new_insilico.hpp"

#include "runtime_modifications_synapse.hpp"

#include "data_types.hpp"
#include "physical_constants.hpp"
#include "global_variables.hpp"

#include "glutamate_production.hpp"

namespace gvars=astron::globals;

void glutamate_production::current(state_type &variables, state_type &dxdt, const double t, unsigned index)
{
  // Gets the pre_neuron_index/post_neuron_index for the particular synapse
  const unsigned pre_index = newinsilico::synapse_value(index,"pre"); 
  const unsigned post_index = newinsilico::synapse_value(index,"post"); 
  // const unsigned post_index = newinsilico::synapse_value(index,"post"); 

  // Checks if glu_ext variable is present in the synapse
  bool glu_ext_absent = 1;
  unsigned glu_ext_index = newinsilico::get_synapse_index(index, "glu_ext",glu_ext_absent);
  
  // Checks if gluves_prod_time variable is present in the synapse
  bool gluves_prod_time_absent = 1;
  double gluves_prod_time = newinsilico::synapse_value(index, "gluves_prod_time", gluves_prod_time_absent);

  // Checks if gluves_content variable is present in the synapse
  bool gluves_content_absent = 1;
  double gluves_content = newinsilico::synapse_value(index,"gluves_content_spillover",gluves_content_absent);

  // Checks if gluves_rel_time_pre variable is present in the presynaptic neuron
  bool gluves_rel_time_absent = 1;
  double gluves_rel_time = newinsilico::neuron_value(pre_index, "gluves_rel_time", gluves_rel_time_absent);

  // If any of the below variables are not present in the synapse then exit from function
  if(!glu_ext_absent && !gluves_prod_time_absent && !gluves_content_absent && !gluves_rel_time_absent){
    // if(gvars::RK4SYN.counter[index] == 1){
      // Calculate glutamate production if the pre neuron has released glutamate
      // std::cout << "Calling glutamate_production for synapse " << index  << " Pre: " << pre_index << std::endl;
      if (gluves_rel_time > gluves_prod_time) {
      	std::cout << "+++ glu_ext production for synapse " << index  << " Pre: " << pre_index << " Post: " << post_index << std::endl;
      	// variables[glu_ext_index] = variables[glu_ext_index] + gluves_content;
      	newinsilico::synapse_value(index,"gluves_prod_time",t);
      }  
      else{
      	newinsilico::synapse_value(index,"gluves_prod_time",-1.0);
      }
    // }
  }  
};
