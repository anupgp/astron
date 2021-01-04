// Time-stamp: <2017-05-30 17:43:06 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Description: This is script models calcium signaling in an astrocytic processes

#include <vector>
#include <iostream>
#include <cmath>

#include "insilico/core.hpp"

#include "astrocyte_process.hpp"

#include "data_types.hpp"
#include "physical_constants.hpp"
#include "global_variables.hpp"

// Header files for Astrocyte

#include "runtime_modifications_cell.hpp"

#include "ip3_degradation_simple.hpp"
#include "p2y_receptor_hill.hpp"
#include "serca_hill.hpp"
#include "er_leak.hpp"
#include "ip3_receptor_lr.hpp"

void astrocyte_process::ode_set(state_type &variables, state_type &dxdt, state_type &noise, const double t, unsigned index)
{  
  // Call runtime_modifications function for cell
  runtime_modifications_cell::current(variables, dxdt, t, index);

  // Update dxdt values from other classes by calling the appropriate function
  // glurel.current(variables, dxdt, t, index);
  
  serca_hill::current(variables, dxdt, t, index);
  er_leak::current(variables, dxdt, t, index);
  
  ip3rlr.current(variables, dxdt, noise, t, index);
  // ryrxw.current(variables, dxdt, noise, t, index);

  ip3_degradation_simple::current(variables, dxdt, t, index);

  p2y_receptor_hill::current(variables, dxdt, t, index);

  // get parameter values
  const double area_volume_ratio_cyt = newinsilico::neuron_value(index, "area_volume_ratio_cyt");
  const double volume_cyt = newinsilico::neuron_value(index, "volume_cyt");
  const double area_cyt = volume_cyt * area_volume_ratio_cyt;
  const double spec_cap_cyt = newinsilico::neuron_value(index, "spec_cap_cyt"); 
  const double volume_ratio_er_cyt = newinsilico::neuron_value(index, "volume_ratio_er_cyt");

  // Get variable indices
  unsigned ca_cyt_index = newinsilico::get_neuron_index(index, "ca_cyt"); // ca_cyt_astrocyte_process
  unsigned ca_er_index = newinsilico::get_neuron_index(index, "ca_er");
  unsigned ip3_cyt_index = newinsilico::get_neuron_index(index, "ip3_cyt");
  
  // Global cytosolic calcium fluxes
  double serca_hill_ca_cyt_flux = newinsilico::neuron_value(index, "serca_hill_ca_cyt_flux");
  double er_leak_ca_cyt_flux = newinsilico::neuron_value(index, "er_leak_ca_cyt_flux");
  double ip3r_lr_ca_cyt_flux = newinsilico::neuron_value(index, "ip3r_lr_ca_cyt_flux");
  double ryr_xw_ca_cyt_flux = newinsilico::neuron_value(index, "ryr_xw_ca_cyt_flux");
  
  // Processes cytosolic calcium fluxes
  double serca_hill_ca_cytp_flux = newinsilico::neuron_value(index, "serca_hill_ca_cytp_flux");
  double er_leak_ca_cytp_flux = newinsilico::neuron_value(index, "er_leak_ca_cyt_flux");
  double ip3r_lr_ca_cytp_flux = newinsilico::neuron_value(index, "ip3r_lr_ca_cytp_flux");
  double ryr_xw_ca_cytp_flux = newinsilico::neuron_value(index, "ryr_xw_ca_cytp_flux");
  
  // Cytosolic ip3 fluxes   
  double p2yr_hill_ip3_cyt_flux = newinsilico::neuron_value(index, "p2yr_hill_ip3_cyt_flux");
  double ip3_degradation_simple_ip3_cyt_flux = newinsilico::neuron_value(index, "ip3_degradation_simple_ip3_cyt_flux");
  
  // Set lower limits on variable values
  variables[ca_cyt_index] = std::max<double>(variables[ca_cyt_index],0.0);
  variables[ca_er_index] = std::max<double>(variables[ca_er_index],0.0);
  variables[ip3_cyt_index] = std::max<double>(variables[ip3_cyt_index],0.0);
  
  // ---------------------
  dxdt[ca_cyt_index] = 0.0
    // + ( + fluo4_ca_cyt_flux * (1))
    + ( - serca_hill_ca_cyt_flux * (1))
    + ( + er_leak_ca_cyt_flux * (1))
    + ( + ip3r_lr_ca_cyt_flux * (1))
    // + ( + ryr_xw_ca_cyt_flux * (1))
    ;
  // ------------------------------------
  dxdt[ca_er_index] = 0.0
    + ( + (1/volume_ratio_er_cyt) * serca_hill_ca_cyt_flux)
    + ( - (1/volume_ratio_er_cyt) * er_leak_ca_cyt_flux)
    + ( - (1/volume_ratio_er_cyt) * ip3r_lr_ca_cyt_flux)
    // + ( - (1/volume_ratio_er_cyt) * ryr_xw_ca_cyt_flux) 
    ;
  
  dxdt[ip3_cyt_index] = 0.0  
    + ( - ip3_degradation_simple_ip3_cyt_flux)
    ;

};
