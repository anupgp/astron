// Time-stamp: <2021-02-19 12:34:22 anup>
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
  auto dhpg_ext_indices = newinsilico::get_pre_neuron_indices(index, "dhpg_ext");

  // Sum up all glu_ext from all the pre_neuron synapses
  double glu_ext = 0.0;
  for(unsigned int iter = 0; iter < glu_ext_indices.size(); ++iter) {
    glu_ext = glu_ext + std::max(variables[glu_ext_indices[iter]],0.0);
  }
  // Sum up all dhpg_ext from all the pre_neuron synapses
  double dhpg_ext = 0.0;
  for(unsigned int iter = 0; iter < dhpg_ext_indices.size(); ++iter) {
    dhpg_ext = dhpg_ext + std::max(variables[dhpg_ext_indices[iter]],0.0);
  }

  // for(auto el:glu_ext_indices){
  //   std::cout << "el" << " " << el << " ";
  // }
  // std::cout << std::endl;

  // std::cout << "glu_ext = " <<glu_ext << std::endl;
  // if(glu_ext >0.0) std::cin.get();

  // Get parameter values for glutamate
  const double k_diss_glu = newinsilico::neuron_value(index, "mglur_hill_k_diss_glu");
  const double v_max_glu = newinsilico::neuron_value(index, "mglur_hill_v_max_glu");
  const double coop_glu = newinsilico::neuron_value(index, "mglur_hill_coop_glu");

    // Get parameter values for dhpg
  const double k_diss_dhpg = newinsilico::neuron_value(index, "mglur_hill_k_diss_dhpg");
  const double v_max_dhpg = newinsilico::neuron_value(index, "mglur_hill_v_max_dhpg");
  const double coop_dhpg = newinsilico::neuron_value(index, "mglur_hill_coop_dhpg");

 // Compute dxdt values for glu_ext & dhpg_ext
  double mglur_ip3_cyt_flux = 0.0;
  double mglur_ip3_cyt_flux_glu = 0.0;
  double mglur_ip3_cyt_flux_dhpg = 0.0;
  
  if (glu_ext > 0)
    {
      mglur_ip3_cyt_flux_glu = (v_max_glu * std::pow(glu_ext,coop_glu)) / (std::pow(k_diss_glu,coop_glu) + std::pow(glu_ext,coop_glu));
  }
  // ------------------
  if (dhpg_ext > 0)
    {
      mglur_ip3_cyt_flux_dhpg = (v_max_dhpg * std::pow(dhpg_ext,coop_dhpg)) / (std::pow(k_diss_dhpg,coop_dhpg) + std::pow(dhpg_ext,coop_dhpg));
  }
  // -----------------
  mglur_ip3_cyt_flux = mglur_ip3_cyt_flux_glu + mglur_ip3_cyt_flux_dhpg;

  newinsilico::neuron_value(index, "mglur_hill_ip3_cyt_flux_glu", mglur_ip3_cyt_flux_glu);
  newinsilico::neuron_value(index, "mglur_hill_ip3_cyt_flux_dhpg", mglur_ip3_cyt_flux_dhpg);
  newinsilico::neuron_value(index, "mglur_hill_ip3_cyt_flux", mglur_ip3_cyt_flux);
}
