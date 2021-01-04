// Time-stamp: <2019-01-04 13:51:09 macbookair>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Ref: Young & Keizer PNAS 1992; J Wade et al. PloS One 2011,

#include <vector>
#include <iostream>
#include <cmath>

#include "include/new_insilico.hpp"

#include "data_types.hpp"
#include "physical_constants.hpp"
#include "global_variables.hpp"
#include "serca_hill.hpp"

namespace consts=astron::phy_const;
namespace gvars=astron::globals;

void serca_hill::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{

  // Get all variable indices
  unsigned ca_cyt_index = newinsilico::get_neuron_index(index, "ca_cyt");
  unsigned ca_er_index = newinsilico::get_neuron_index(index, "ca_er");
  
  // Get all parameter values
  const double v_max = newinsilico::neuron_value(index, "serca_hill_v_max");
  const double k_half = newinsilico::neuron_value(index, "serca_hill_k_half");
  const double coeff = newinsilico::neuron_value(index, "serca_hill_coeff");

  variables[ca_cyt_index] = std::max<double>(variables[ca_cyt_index],0.0);
  variables[ca_er_index] = std::max<double>(variables[ca_er_index],0.0);

  // Get all variable values
  double ca_cyt = variables[ca_cyt_index];
  double ca_er = variables[ca_er_index];

  // --------------------------------------------

  double serca_hill_ca_cyt_flux = v_max * (pow(ca_cyt,coeff) / (pow(ca_cyt,coeff) + pow(k_half,coeff)));

  // Update parameter values  
  newinsilico::neuron_value(index, "serca_hill_ca_cyt_flux", serca_hill_ca_cyt_flux);

};
