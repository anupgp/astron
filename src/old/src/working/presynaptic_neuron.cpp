// Time-stamp: <2016-06-22 11:49:42 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads

#include <vector>
#include <iostream>
#include <cmath>
#include <ctime>

#include "insilico/core.hpp"

#include "data_types.hpp"
#include "physical_constants.hpp"
#include "global_variables.hpp"

// Header files for presynaptic_neuron

#include "na_pre.hpp"
#include "k_pre.hpp"
#include "leak_pre.hpp"
#include "vgcc_pre.hpp"

#include "ip3_degradation_simple.hpp"
#include "ip3_kinase_hill.hpp"
#include "plc_delta_hill.hpp"

#include "p2x2_receptor.hpp"
#include "p2x2_receptor_hill.hpp"
#include "p2y_receptor_hill.hpp"
#include "mglu_receptor_hill.hpp"

#include "pmca.hpp"
#include "calbindin.hpp"
#include "serca_hill.hpp"
#include "er_leak.hpp"
#include "ryanodine_receptor.hpp"
#include "ip3_receptor_yk.hpp"
#include "a1_receptor_hill.hpp"

#include "presynaptic_neuron.hpp"

void presynaptic_neuron::ode_set(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{
  // Updates the rk4 counter function for cell
  astron::globals::RK4CELL.counter_update(index,t); 
  
  // Update dxdt values from other classes by calling the appropriate function

  pmca::current(variables, dxdt, t, index);
  calbindin::current(variables, dxdt, t, index);
  serca_hill::current(variables, dxdt, t, index);
  er_leak::current(variables, dxdt, t, index);
  ryanodine_receptor::current(variables, dxdt, t, index);
  ip3_receptor_yk::current(variables, dxdt, t, index);

  napre.current(variables, dxdt, t, index);
  kpre.current(variables, dxdt, t, index);
  leakpre.current(variables, dxdt, t, index);
  vgcc_pre::current(variables, dxdt, t, index);  
  
  glurel.current(variables, dxdt, t, index);

  ip3_degradation_simple::current(variables, dxdt, t, index);
  ip3_kinase_hill::current(variables, dxdt, t, index);
  plc_delta_hill::current(variables, dxdt, t, index);    

  p2y_receptor_hill::current(variables, dxdt, t, index); 
  p2x2_receptor::current(variables, dxdt, t, index);
  p2x2_receptor_hill::current(variables, dxdt, t, index);
  mglu_receptor_hill::current(variables, dxdt, t, index);

  a1_receptor_hill::current(variables, dxdt, t, index);          

  // Get parameter values
  const double area_volume_ratio_cyt = newinsilico::neuron_value(index, "area_volume_ratio_cyt");
  const double volume_cyt = newinsilico::neuron_value(index, "volume_cyt");
  const double area_cyt = volume_cyt * area_volume_ratio_cyt;
  const double spec_cap_cyt = newinsilico::neuron_value(index, "spec_cap_cyt"); 
  const double volume_ratio_er_cyt = newinsilico::neuron_value(index, "volume_ratio_er_cyt");

  // Get variable indices
  unsigned voltage_index = newinsilico::get_neuron_index(index, "voltage");
  unsigned ca_cyt_index = newinsilico::get_neuron_index(index, "ca_cyt");
  unsigned ip3_cyt_index = newinsilico::get_neuron_index(index, "ip3_cyt");
  unsigned ca_er_index = newinsilico::get_neuron_index(index, "ca_er");
  
  // Intermidiate dxdt values: currents
  double na_pre_current = newinsilico::neuron_value(index, "na_pre_current");
  double k_pre_current = newinsilico::neuron_value(index, "k_pre_current");
  double leak_pre_current = newinsilico::neuron_value(index, "leak_pre_current");
  double vgcc_pre_current = newinsilico::neuron_value(index, "vgcc_pre_current");
  double p2x2r_current = newinsilico::neuron_value(index, "p2x2r_current");

  // calcium flux
  double pmca_ca_cyt_flux = newinsilico::neuron_value(index, "pmca_ca_cyt_flux");
  double calbindin_ca_cyt_flux = newinsilico::neuron_value(index, "calbindin_ca_cyt_flux");
  double serca_hill_ca_cyt_flux = newinsilico::neuron_value(index, "serca_hill_ca_cyt_flux");
  double er_leak_ca_cyt_flux = newinsilico::neuron_value(index, "er_leak_ca_cyt_flux");
  double ryr_ca_cyt_flux = newinsilico::neuron_value(index, "ryr_ca_cyt_flux");
  double ip3r_yk_ca_cyt_flux = newinsilico::neuron_value(index, "ip3r_yk_ca_cyt_flux");
  double p2x2r_hill_ca_cyt_flux = newinsilico::neuron_value(index, "p2x2r_hill_ca_cyt_flux");
  double p2x2r_ca_cyt_flux = newinsilico::neuron_value(index, "p2x2r_ca_cyt_flux");
  double vgcc_pre_ca_cyt_flux = newinsilico::neuron_value(index, "vgcc_pre_ca_cyt_flux");
  double gluves_ca_cyt_flux = newinsilico::neuron_value(index, "gluves_ca_cyt_flux");
  
  // ip3 fluxes  
  double p2yr_hill_ip3_cyt_flux = newinsilico::neuron_value(index, "p2yr_hill_ip3_cyt_flux");
  double mglur_hill_ip3_cyt_flux = newinsilico::neuron_value(index, "mglur_hill_ip3_cyt_flux");
  double ip3_degradation_simple_ip3_cyt_flux = newinsilico::neuron_value(index, "ip3_degradation_simple_ip3_cyt_flux");
  double ip3_kinase_hill_ip3_cyt_flux = newinsilico::neuron_value(index, "ip3_kinase_hill_ip3_cyt_flux");
  double plc_delta_hill_ip3_cyt_flux = newinsilico::neuron_value(index, "plc_delta_hill_ip3_cyt_flux");

  // Adding external current through external current function (injector)
  std::vector<double> external_currents = insilico::injector::external_current(index, t);
  double ext_current = 0.0;
  if(!external_currents.empty()){
    ext_current = external_currents[index];
  }
  newinsilico::neuron_value(index, "external_current",ext_current);

  // Set lower limits on variable values
  variables[ca_cyt_index] = std::max<double>(variables[ca_cyt_index],0.0);
  variables[ca_er_index] = std::max<double>(variables[ca_er_index],0.0);
  variables[ip3_cyt_index] = std::max<double>(variables[ip3_cyt_index],0.0);

  dxdt[voltage_index] =  0.0
    + ((- area_cyt * na_pre_current) * (1.0/(area_cyt * spec_cap_cyt)))
    + ((- area_cyt * k_pre_current) * (1.0/(area_cyt * spec_cap_cyt))) 
    + ((- area_cyt * leak_pre_current) * (1.0/(area_cyt * spec_cap_cyt)))
    + ((area_cyt * ext_current * 1.0) * (1.0/(area_cyt * spec_cap_cyt)))
    + (vgcc_pre_current)
    + (p2x2r_current)
    ;

  dxdt[ca_cyt_index] = 0.0
    + ( + pmca_ca_cyt_flux)
    + ( + calbindin_ca_cyt_flux)
    + ( - serca_hill_ca_cyt_flux)
    + ( + er_leak_ca_cyt_flux)

    + ( + gluves_ca_cyt_flux)

    + ( + vgcc_pre_ca_cyt_flux) 
    + ( + ryr_ca_cyt_flux) 
    + ( + ip3r_yk_ca_cyt_flux) 
    + ( + p2x2r_ca_cyt_flux)
    ;

  dxdt[ca_er_index] = 0.0
    + ( - ryr_ca_cyt_flux * (volume_ratio_er_cyt))
    + ( + serca_hill_ca_cyt_flux * (volume_ratio_er_cyt))
    + ( - er_leak_ca_cyt_flux * (volume_ratio_er_cyt))
    + ( - ip3r_yk_ca_cyt_flux * (volume_ratio_er_cyt))
    ;

  dxdt[ip3_cyt_index] = 0.0  
    + ( - ip3_degradation_simple_ip3_cyt_flux)
    + ( - ip3_kinase_hill_ip3_cyt_flux)
    + ( + plc_delta_hill_ip3_cyt_flux)
    + ( + mglur_hill_ip3_cyt_flux)
    + ( + p2yr_hill_ip3_cyt_flux)
    ;
};

