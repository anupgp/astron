// Time-stamp: <2018-01-24 18:45:56 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Ref: lv2015

#include <vector>
#include <iostream>
#include <cmath>

#include "insilico/core.hpp"

#include "data_types.hpp"
#include "physical_constants.hpp"
#include "global_variables.hpp"

// Header files for Astrocyte

#include "runtime_modifications_cell.hpp"

#include "na_pre.hpp"
#include "k_pre.hpp"
#include "leak_pre.hpp"

#include "ip3_degradation_simple.hpp"
#include "ip3_kinase_hill.hpp"
#include "plc_delta_hill.hpp"

// #include "p2y_receptor_hill.hpp"
// #include "p2x2_receptor.hpp" /* NOT INCLUDED */
#include "mglu_receptor_hill.hpp" /* NOT INCLUDED */

#include "pmca.hpp"
#include "ca_cyt_buffer_simple.hpp"
#include "ca_er_buffer_simple.hpp"
#include "serca_hill.hpp"
#include "er_leak.hpp"
#include "ip3_receptor_lr.hpp"
// #include "calbindin.hpp" /* NOT INCLUDED */
// #include "ryr_receptor_xw.hpp" /* NOT INCLUDED */
// #include "cap_ca_entry.hpp" /* NOT INCLUDED */
// #include "serca_higg.hpp" /* NOT INCLUDED */
// #include "ip3_receptor_yk.hpp" /* NOT INCLUDED */
// #include "ryanodine_receptor.hpp" /* NOT INCLUDED */
// #include "ca_cyt_dye.hpp" /* NOT INCLUDED */

#include "astrocyte.hpp"

void astrocyte::ode_set(state_type &variables, state_type &dxdt, state_type &noise, const double t, unsigned index)
// void astrocyte::ode_set(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{  

  // Call runtime_modifications function for cell
  runtime_modifications_cell::current(variables, dxdt, t, index);

  // Update dxdt values from other classes by calling the appropriate function
  glurel.current(variables, dxdt, t, index);
  
  pmca::current(variables, dxdt, t, index);
  ca_cyt_buffer_simple::current(variables, dxdt, t, index);
  ca_er_buffer_simple::current(variables, dxdt, t, index);
  serca_hill::current(variables, dxdt, t, index);

  er_leak::current(variables, dxdt, t, index);
  // calbindin::current(variables, dxdt, t, index);          /* NOT INCLUDED */
  // cap_ca_entry::current(variables, dxdt, t, index);       /* NOT INCLUDED */
  // serca_higg::current(variables, dxdt, t, index);         /* NOT INCLUDED */
  // ip3_receptor_yk::current(variables, dxdt, t, index);    /* NOT INCLUDED */
  // ryanodine_receptor::current(variables, dxdt, t, index); /* NOT INCLUDED */ 
  // ca_cyt_dye::current(variables, dxdt, t, index);         /* NOT INCLUDED */
    
  napre.current(variables, dxdt, t, index);
  kpre.current(variables, dxdt, t, index);
  leakpre.current(variables, dxdt, t, index);
  
  ip3rlr.current(variables, dxdt, noise, t, index);
  // ryrxw.current(variables, dxdt, noise, t, index);         /* NOT INCLUDED */

  ip3_degradation_simple::current(variables, dxdt, t, index);
  ip3_kinase_hill::current(variables, dxdt, t, index);
  plc_delta_hill::current(variables, dxdt, t, index);    
  mglu_receptor_hill::current(variables, dxdt, t, index);     /* NOT INCLUDED */
  // p2y_receptor_hill::current(variables, dxdt, t, index);   /* NOT INCLUDED */  
  // p2x2_receptor::current(variables, dxdt, t, index);       /* NOT INCLUDED */

  // get parameter values
  const double area_volume_ratio_cyt = newinsilico::neuron_value(index, "area_volume_ratio_cyt");
  const double volume_cyt = newinsilico::neuron_value(index, "volume_cyt");
  const double area_cyt = volume_cyt * area_volume_ratio_cyt;
  const double spec_cap_cyt = newinsilico::neuron_value(index, "spec_cap_cyt"); 
  const double volume_ratio_er_cyt = newinsilico::neuron_value(index, "volume_ratio_er_cyt");

  // Get variable indices
  unsigned voltage_index = newinsilico::get_neuron_index(index, "voltage");
  unsigned ca_cyt_index = newinsilico::get_neuron_index(index, "ca_cyt"); // ca_cyt_global
  unsigned ca_er_index = newinsilico::get_neuron_index(index, "ca_er");
  unsigned ip3_cyt_index = newinsilico::get_neuron_index(index, "ip3_cyt");
  
  // Currents
  double na_pre_current = newinsilico::neuron_value(index, "na_pre_current");
  double k_pre_current = newinsilico::neuron_value(index, "k_pre_current");
  double leak_pre_current = newinsilico::neuron_value(index, "leak_pre_current");
  double external_current = newinsilico::neuron_value(index, "external_current");
  // double p2x2r_current = newinsilico::neuron_value(index, "p2x2r_current"); /* NOT INCLUDED */
  
  // Global cytosolic calcium fluxes
  double pmca_ca_cyt_flux = newinsilico::neuron_value(index, "pmca_ca_cyt_flux");
  double ca_cyt_buffer_simple_flux = newinsilico::neuron_value(index, "ca_cyt_buffer_simple_flux");
  double serca_hill_ca_cyt_flux = newinsilico::neuron_value(index, "serca_hill_ca_cyt_flux");
  double er_leak_ca_cyt_flux = newinsilico::neuron_value(index, "er_leak_ca_cyt_flux");
  double ip3r_lr_ca_cyt_flux = newinsilico::neuron_value(index, "ip3r_lr_ca_cyt_flux");
  double syt45_ca_cyt_flux_glu = newinsilico::neuron_value(index, "syt45_ca_cyt_flux_glu");
  
  // double calbindin_ca_cyt_flux = newinsilico::neuron_value(index, "ca_cyt_buffer_simple_flux");
  // double cap_ca_entry_ca_cyt_flux = newinsilico::neuron_value(index, "cap_ca_entry_ca_cyt_flux");
  // double ryr_xw_ca_cyt_flux = newinsilico::neuron_value(index, "ryr_xw_ca_cyt_flux");
  // double serca_higg_ca_cyt_flux = newinsilico::neuron_value(index, "serca_higg_ca_cyt_flux"); /* NOT INCLUDED */
  // double serca_higg_ca_er_flux = newinsilico::neuron_value(index, "serca_higg_ca_er_flux"); /* NOT INCLUDED */
  // double ryr_ca_cyt_flux = newinsilico::neuron_value(index, "ryr_ca_cyt_flux"); /* NOT INCLUDED */
  // double ip3r_yk_ca_cyt_flux = newinsilico::neuron_value(index, "ip3r_yk_ca_cyt_flux"); /* NOT INCLUDED */
  // double ca_cyt_dye_ca_cyt_flux = newinsilico::neuron_value(index, "ca_cyt_dye_ca_cyt_flux"); /*Fluorescent calcium indicator*/
  
  // Global er calcium fluxes
  double ca_er_buffer_simple_flux = newinsilico::neuron_value(index, "ca_er_buffer_simple_flux");
  
  // Cytosolic ip3 fluxes   
  double ip3_degradation_simple_ip3_cyt_flux = newinsilico::neuron_value(index, "ip3_degradation_simple_ip3_cyt_flux");
  double ip3_kinase_hill_ip3_cyt_flux = newinsilico::neuron_value(index, "ip3_kinase_hill_ip3_cyt_flux");
  double plc_delta_hill_ip3_cyt_flux = newinsilico::neuron_value(index, "plc_delta_hill_ip3_cyt_flux");
  double mglur_hill_ip3_cyt_flux = newinsilico::neuron_value(index, "mglur_hill_ip3_cyt_flux"); 
  // double p2yr_hill_ip3_cyt_flux = newinsilico::neuron_value(index, "p2yr_hill_ip3_cyt_flux"); /* NOT INCLUDED */
  // double p2x2r_ca_cyt_flux = newinsilico::neuron_value(index, "p2x2r_ca_cyt_flux");           /* NOT INCLUDED */
  
  // Set lower limits on variable values
  variables[ca_cyt_index] = std::max<double>(variables[ca_cyt_index],0.0);
  variables[ca_er_index] = std::max<double>(variables[ca_er_index],0.0);
  variables[ip3_cyt_index] = std::max<double>(variables[ip3_cyt_index],0.0);

  dxdt[voltage_index] =  0.0
    + ((- area_cyt * na_pre_current) * (1.0/(area_cyt * spec_cap_cyt)))
    + ((- area_cyt * k_pre_current) * (1.0/(area_cyt * spec_cap_cyt))) 
    + ((- area_cyt * leak_pre_current) * (1.0/(area_cyt * spec_cap_cyt)))
    + ((+ area_cyt * external_current * 0.0) * (1.0/(area_cyt * spec_cap_cyt)))
    // + (p2x2r_current) /* NOT INCLUDED */
    ;
  
  // ---------------------
  dxdt[ca_cyt_index] = 0.0
    + ( + pmca_ca_cyt_flux * (1))
    + ( + ca_cyt_buffer_simple_flux * (1))
    + ( - serca_hill_ca_cyt_flux * (1))
    + ( + er_leak_ca_cyt_flux * (1))
    + ( + ip3r_lr_ca_cyt_flux * (1))
    + ( + syt45_ca_cyt_flux_glu * (1))
    // + ( + calbindin_ca_cyt_flux * (1))    /* NOT INCLUDED */
    // + ( + cap_ca_entry_ca_cyt_flux * (1)) /* NOT INCLUDED */
    // + ( + ryr_xw_ca_cyt_flux * (1))       /* NOT INCLUDED */
    // + ( + ca_cyt_dye_ca_cyt_flux * (1))   /* NOT INCLUDED */
    // + ( + p2x2r_ca_cyt_flux)              /* NOT INCLUDED */
    // + ( + ip3r_yk_ca_cyt_flux * (0))      /* NOT INCLUDED */
    // + ( + ryr_ca_cyt_flux * (0))          /* NOT INCLUDED */
    // + ( + serca_higg_ca_cyt_flux * (0))   /* NOT INCLUDED */
    ;

  // ------------------------------------
  dxdt[ca_er_index] = 0.0
    + ( + (1/volume_ratio_er_cyt) * serca_hill_ca_cyt_flux)
    + ( - (1/volume_ratio_er_cyt) * er_leak_ca_cyt_flux)
    + ( - (1/volume_ratio_er_cyt) * ip3r_lr_ca_cyt_flux)
    + ( + (1) * ca_er_buffer_simple_flux )
    // + ( - (1/volume_ratio_er_cyt) * ryr_xw_ca_cyt_flux) /* NOT INCLUDED */
    // + ( + (1) * serca_higg_ca_er_flux)                  /* NOT INCLUDED */
    ;
  
  // ------------------------  
  dxdt[ip3_cyt_index] = 0.0  
    + ( - ip3_degradation_simple_ip3_cyt_flux)
    + ( - ip3_kinase_hill_ip3_cyt_flux)
    + ( + plc_delta_hill_ip3_cyt_flux)
    + ( + mglur_hill_ip3_cyt_flux)
    // + ( + p2yr_hill_ip3_cyt_flux)  /* NOT INCLUDED */
    ;

};
