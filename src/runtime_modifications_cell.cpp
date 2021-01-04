// Time-stamp: <2020-12-28 21:19:06 anup>
// Units: All SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Description: This file will contain all the codes which will modify the variables or parameters at run time
// This script will implement the call to dynamic parameters and external currents

#include <vector>
#include <iostream>
#include <cmath>

#include "include/new_insilico.hpp"

#include "runtime_modifications_cell.hpp"

#include "data_types.hpp"
#include "physical_constants.hpp"
#include "global_variables.hpp"

void runtime_modifications_cell::current(state_type &variables, const state_type &dxdt, const double t, const unsigned index)
{

  // Updates the RK4 counter function for cell
  // astron::globals::RK4CELL.counter_update(index,t);

  // ----------------------------------

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

  // Checks if ca_cyt_dyn variable is present in the synapse
  bool ca_cyt_absent = 1;
  unsigned ca_cyt_index = newinsilico::get_neuron_index(index, "ca_cyt",ca_cyt_absent);

  std::string dyparname;
  double dypar = 0.0;
  // -------------------------------------------
  // Increase ca_cyt concentration based on dynamic parameter     
  if(!ca_cyt_absent){
    dyparname = "ca_cyt" + std::to_string(index);
    dypar = newinsilico::value(dyparname,t);
    if (dypar > 0.0){
      variables[ca_cyt_index] = dypar;
    }
  }
  
}

