// Time-stamp: <2017-06-07 16:21:29 anup>
// Doc: ryr receptor (Xiao Wang model)
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Ref: wang2015; shuai2002;
// Note: Implimented from the paper: Calcium homeostasis in a local/global whole cell model of permeabilized ventricular myocytes with a Langevin description of stochastic calcium release, Xiao Wang et al., Am J Physiol Heart Circ Physiol 308: H510–H523, 2015.
// Note: This is a two-state model of the ryanodine receptor

#include <vector>
#include <iostream>
#include <cmath>

#include "insilico/core.hpp"

#include "physical_constants.hpp"
#include "global_variables.hpp"
#include "data_types.hpp"
#include "ryr_receptor_xw.hpp"

namespace gvars=astron::globals;

void ryr_receptor_xw::current(state_type &variables, state_type &dxdt, const double t, unsigned index)
{
  state_type noise = newinsilico::get_noise();
  ryr_receptor_xw::current(variables, dxdt, noise, t, index);
}

void ryr_receptor_xw::current(state_type &variables, state_type &dxdt, state_type &noise, const double t, unsigned index) 
{
  // Get parameter values
  const double kf = newinsilico::neuron_value(index, "ryr_xw_kf");
  const double kb = newinsilico::neuron_value(index, "ryr_xw_kb");
  const double coop = newinsilico::neuron_value(index, "ryr_xw_coop");
  const double flux_coef = newinsilico::neuron_value(index, "ryr_xw_flux_coef");
  const double num = newinsilico::neuron_value(index, "ryr_xw_num");
  const double ca_incr_single = newinsilico::neuron_value(index, "ryr_xw_ca_incr_single");

  // Get all variable indices
  unsigned ca_cyt_index = newinsilico::get_neuron_index(index, "ca_cyt");
  unsigned ca_er_index = newinsilico::get_neuron_index(index, "ca_er");
  unsigned fo_index = newinsilico::get_neuron_index(index, "ryr_xw_fo");

  // Set upper limits on variable values
  variables[fo_index] = std::min<double>(variables[fo_index],1.0);

  // Set lower limits on variable values
  variables[fo_index] = std::max<double>(variables[fo_index],0.0);
  
  // Get variable values
  double ca_cyt = variables[ca_cyt_index];
  double ca_er = variables[ca_er_index];
  double fo = variables[fo_index];

  // Compute values
  double ca_incr_whole = num * ca_incr_single;
  double term1 = (kf * pow((ca_cyt + (ca_incr_whole * fo)),coop) * (1 - fo));
  double term2 = kb * fo;

  // Compute noise
  noise[fo_index] = sqrt(((term1 + term2)/num) * gvars::DELTA_T) * rand.uni_double();

  // Compute dxdt
  dxdt[fo_index] = term1 - term2; 
    
  // compute the flux
  double ryr_xw_ca_cyt_flux = (ca_er - ca_cyt) * flux_coef * fo;

  // Copy values
  newinsilico::neuron_value(index, "ryr_xw_ca_cyt_flux", ryr_xw_ca_cyt_flux);
}
