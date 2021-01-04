// Time-stamp: <2018-02-12 15:57:12 anup>
// Units: All SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Description: This file will contain all the codes which will modify the variables or parameters at run time
// This script will implement the call to dynamic parameters and external currents

#include <vector>
#include <iostream>
#include <cmath>

#include "insilico/core.hpp"

#include "runtime_modifications_cell.hpp"

#include "data_types.hpp"
#include "physical_constants.hpp"
#include "global_variables.hpp"

void runtime_modifications_cell::current(state_type &variables, const state_type &dxdt, const double t, const unsigned index)
{

  // Updates the RK4 counter function for cell
  astron::globals::RK4CELL.counter_update(index,t);
  // ------------------------------
  // Condition to limit the output file write
  // if(t >= 40 && t <=100){
  if(t >= 195 && t <=231){
    newinsilico::set_write_this_interval(true);
  }
  else{
    newinsilico::set_write_this_interval(false);
  }

  // Condition to change a variable with time
  // unsigned ca_cyt_index = newinsilico::get_neuron_index(index, "ca_cyt");
  // if(t >= 1 && t < 3){
  //   variables[ca_cyt_index] = 2e-6;
  // }
  // else{
  //   variables[ca_cyt_index] = 0.0;
  // }
  
  // ----------------------------------
  // Adding external current through external current function (injector)
  // std::vector<double> external_currents = insilico::injector::external_current(index, t);
  // double ext_current = 0.0;
  // if(!external_currents.empty()){
  //   ext_current = external_currents[index];
  // }
  // newinsilico::neuron_value(index, "external_current",ext_current);

  // -----------------------------------
  // Increase ca_cyt concentration based on dynamic parameter
  // Get variable indices
  // unsigned ca_cyt_index = newinsilico::get_neuron_index(index, "ca_cyt");
  // double ca_cyt_dyn = 0.0;
  // std::string ca_cyt_dyn_name = "ca_cyt_ext" + std::to_string(index);
  // ca_cyt_dyn = insilico::dynamic_params::value(ca_cyt_dyn_name,t);
  // bool founddynparname = insilico::dynamic_params::found_dynparam_name;
  // bool founddynparvalue = insilico::dynamic_params::found_dynparam_value;
  // if (founddynparname){
  //   variables[ca_cyt_index] = ca_cyt_dyn;
  //   std::cout << t << " " << ca_cyt_dyn_name << " " << ca_cyt_dyn << "\n";
  // };
  
  // Increase ip3_cyt concentration based on dynamic parameter
  // Get variable indices
  // unsigned ip3_cyt_index = newinsilico::get_neuron_index(index, "ip3_cyt");
  // double ip3_cyt_dyn = 0.0;
  // std::string ip3_cyt_dyn_name = "ip3_ext" + std::to_string(index);
  // ip3_cyt_dyn = insilico::dynamic_params::value(ip3_cyt_dyn_name,t);
  // std::cout << t << " " << ip3_cyt_dyn_name << " " << ip3_cyt_dyn << "\n";
  // if (ip3_cyt_dyn > 0.0){
  //   variables[ip3_cyt_index] = ip3_cyt_dyn;
  // };
}
