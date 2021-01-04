// Time-stamp: <2017-03-04 12:07:11 anup>
// Units: All SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Description: This class is called by a atp_synapse class. It simply updates the value of the atp_ext synapse variable if the presynaptic cell has released an atp vesicle

#include <vector>
#include <iostream>
#include <cmath>

#include "insilico/core.hpp"

#include "runtime_modifications_synapse.hpp"

#include "data_types.hpp"
#include "physical_constants.hpp"
#include "global_variables.hpp"

#include "atp_production.hpp"

namespace gvars=astron::globals;

void atp_production::current(state_type &variables, state_type &dxdt, const double t, unsigned index)
{
  // Gets the pre_neuron_index/post_neuron_index for the particular synapse
  const unsigned pre_index = newinsilico::synapse_value(index,"pre"); 
  const unsigned post_index = newinsilico::synapse_value(index,"post"); 
  // const unsigned post_index = newinsilico::synapse_value(index,"post"); 

  // Checks if atp_ext variable is present in the synapse
  bool atp_ext_absent = 1;
  unsigned atp_ext_index = newinsilico::get_synapse_index(index, "atp_ext",atp_ext_absent);
  
  // Checks if atpves_prod_time variable is present in the synapse
  bool atpves_prod_time_absent = 1;
  double atpves_prod_time = newinsilico::synapse_value(index, "atpves_prod_time", atpves_prod_time_absent);

  // Checks if atpves_content variable is present in the synapse
  bool atpves_content_absent = 1;
  double atpves_content = newinsilico::synapse_value(index,"atpves_content",atpves_content_absent);

  // Checks if atpves_rel_time_pre variable is present in the presynaptic neuron
  bool atpves_rel_time_absent = 1;
  double atpves_rel_time = newinsilico::neuron_value(pre_index, "atpves_rel_time", atpves_rel_time_absent);

  // If any of the below variables are not present in the synapse then exit from function
  if(!atp_ext_absent && !atpves_prod_time_absent && !atpves_content_absent && !atpves_rel_time_absent){
    // if(gvars::RK4SYN.counter[index] == 1){
    // Calculate atp production if the pre neuron has released atp
    if (atpves_rel_time > atpves_prod_time) {
      std::cout << "^^^ atp_ext production for synapse " << index  << " Pre: " << pre_index <<  " Post: " << post_index << std::endl;
      // variables[atp_ext_index] = variables[atp_ext_index] + atpves_content;
      newinsilico::synapse_value(index,"atpves_prod_time",t);
    }  
    else{
      newinsilico::synapse_value(index,"atpves_prod_time",-1.0);
    }
    // }
  }
};
