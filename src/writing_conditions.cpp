// Time-stamp: <2021-02-19 17:42:33 anup>
// Units: All SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Description: This file will contain all the codes which will modify the variables or parameters at run time
// This script will implement the call to dynamic parameters and external currents

#include <vector>
#include <iostream>
#include <cmath>

#include "include/new_insilico.hpp"

#include "writing_conditions.hpp"

#include "data_types.hpp"
#include "physical_constants.hpp"
#include "global_variables.hpp"

void writing_conditions::current(state_type &variables, const state_type &dxdt, const double t, const unsigned index)
{

  // Updates the RK4 counter function for cell
  astron::globals::RK4CELL.counter_update(index,t);

  // ------------------------------
  // limit writing the output file
  // double tstart = 200;
  double tstart = 185;
  double tstop = 300;
  // double tstop = 210;
  // --------------------------------
  if( ((t >= tstart) && (t <= tstop))){
    newinsilico::set_write_this_interval(true);
  }
  else{
    newinsilico::set_write_this_interval(false);
  }
  // compulsory write when a release event occurs
  // --------------------------------
  double relflag =  newinsilico::neuron_value(index, "syt45_relflag_glu");
  if( ((t >= tstart) && (t <= tstop)) && (relflag >0)){
    newinsilico::set_write_this_interval2(true);
  }
  else{
    newinsilico::set_write_this_interval2(false);
  }  
  // ----------------------------------
}
