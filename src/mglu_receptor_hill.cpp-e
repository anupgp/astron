// Time-stamp: <2019-01-04 13:37:57 macbookair>
// Units: All SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Ref: Ullah, Jung & Bell Cell Calcium (2006)
// Note: The binding and unbinding of glutamate at the receptor will change local glutamate concentration. Currently this is not taken into account. 

#include <vector>
#include <iostream>
#include <cmath>

#include "include/new_insilico.hpp"

#include "physical_constants.hpp"
#include "global_variables.hpp"
#include "data_types.hpp"
#include "mglu_receptor_hill.hpp"

void mglu_receptor_hill::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{

  // Get pre_neuron variable indices 

  auto glu_ext_indices = newinsilico::get_pre_neuron_indices(index, "glu_ext");

  // Sum up all ATP_Ext from all the pre_neuron synapses

  double glu_ext = 0.0;
  for(unsigned int iter = 0; iter < glu_ext_indices.size(); ++iter) {
    glu_ext = glu_ext + std::max(variables[glu_ext_indices[iter]],0.0);
  }

  // for(auto el:glu_ext_indices){
  //   std::cout << "el" << " " << el << " ";
  // }
  // std::cout << std::endl;

  // std::cout << "glu_ext = " <<glu_ext << std::endl;
  // if(glu_ext >0.0) std::cin.get();

  // Get parameter values
  const double k_diss = newinsilico::neuron_value(index, "mglur_hill_k_diss");
  const double v_max = newinsilico::neuron_value(index, "mglur_hill_v_max");
  const double coop = newinsilico::neuron_value(index, "mglur_hill_coop");

 // Compute dxdt values

  double mglur_ip3_cyt_flux = 0.0;
  if (glu_ext > 0)
    {
      mglur_ip3_cyt_flux = (v_max * std::pow(glu_ext,coop)) / (std::pow(k_diss,coop) + std::pow(glu_ext,coop));
  }
 
 newinsilico::neuron_value(index, "mglur_hill_ip3_cyt_flux", mglur_ip3_cyt_flux);
}
