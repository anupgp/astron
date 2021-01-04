// Time-stamp: <2020-12-24 20:59:10 anup>
// Units: All SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Description: This file will contain all the codes which will modify the variables or parameters at run time
// This script will implement the call to dynamic parameters and external currents

#include <vector>
#include <iostream>
#include <cmath>

#include "include/new_insilico.hpp"

#include "runtime_modifications_synapse.hpp"

#include "data_types.hpp"
#include "physical_constants.hpp"
#include "global_variables.hpp"

void runtime_modifications_synapse::current(state_type &variables, const state_type &dxdt, const double t, const unsigned index)
{

  // // Updates the RK4 counter function for synapse
  // astron::globals::RK4CELL.counter_update(index,t);

  // Gets the pre_neuron_index/post_neuron_index for the particular synapse
  const unsigned pre_index = newinsilico::synapse_value(index,"pre"); 
  const unsigned post_index = newinsilico::synapse_value(index,"post");

  // Checks if glu_ext variable is present in the synapse
  bool glu_ext_absent = 1;
  unsigned glu_ext_index = newinsilico::get_synapse_index(index, "glu_ext",glu_ext_absent);
  
  // // Checks if atp_ext variable is present in the synapse
  // bool atp_ext_absent = 1;
  // unsigned atp_ext_index = newinsilico::get_synapse_index(index, "atp_ext",atp_ext_absent);


  std::string dyparname;
  double dypar = 0.0;
  // -------------------------------------------
  // Increase glu concentration based on dynamic parameter     
  if(!glu_ext_absent){
    // dyparname = "dhpg" + std::to_string(index);
    // dyparname = "glu_ext1";
    dyparname = "dhpg_ext1";
    // dyparname = "dhpg_ext1";
    dypar = newinsilico::value(dyparname,t);
    if (dypar > 0.0){
      variables[glu_ext_index] = dypar;
    }
  }
  // --------------------------------------------
  // Increase atp concentration based on dynamic parameter     
  // if(!atp_ext_absent){
  //   double atp_ext_dyn = 0.0;
  //   std::string atp_ext_dyn_name = "atp_ext" + std::to_string(index);
  //   atp_ext_dyn = insilico::dynamic_params::value(atp_ext_dyn_name,t);
  //   // std::cout << "Dynparam value = " << atp_ext_dyn << "\n";
  //   if (atp_ext_dyn > 0.0){
  //     variables[atp_ext_index] = atp_ext_dyn;
  //   }
  //   if (atp_ext_dyn <= 0.0){
  //     variables[atp_ext_index] = 0.0;
  //   }
  // }
  // ---------------------------------------------
  // Release glutamate vesicle based on dynamic parameter
  if(!glu_ext_absent){
    double gluves_content = newinsilico::synapse_value(index,"gluves_content_spillover");
    dyparname = "ap_ext" + std::to_string(index);
    dypar = newinsilico::value(dyparname,t);
    if(dypar != 0){
	variables[glu_ext_index] = variables[glu_ext_index] + gluves_content;
    } 
  }
    
  // if(dypar != 0){
  //   std::cout << "Found: " << dyparname << " with value = " << dypar << "at time: " << std::setprecision(10) << t << std::endl;
  // }
}
