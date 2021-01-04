// Time-stamp: <2016-03-23 14:43:24 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Ref: Stamastakis & Mantzaris 2006

#include <vector>
#include <iostream>
#include <cmath>

#include "physical_constants.hpp"
#include "global_variables.hpp"
#include "data_types.hpp"

#include "insilico/core.hpp"
#include "ip3_degradation_simple.hpp"

void ip3_degradation_simple::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{

  // Get all variable indices
  unsigned ip3_cyt_index = newinsilico::get_neuron_index(index, "ip3_cyt");

  // Set lower limits on variable values
  variables[ip3_cyt_index] = std::max<double>(variables[ip3_cyt_index],0.0);

  // Get variable values
  double ip3_cyt = variables[ip3_cyt_index];

  // Get parameter values
  const double v_max = newinsilico::neuron_value(index, "ip3_degradation_simple_v_max");
  const double ip3_cyt_baseline = newinsilico::neuron_value(index, "ip3_cyt_baseline");

  // Compute dxdt values
  double ip3_degradation_simple_ip3_cyt_flux = v_max * (ip3_cyt - ip3_cyt_baseline);

  newinsilico::neuron_value(index, "ip3_degradation_simple_ip3_cyt_flux", ip3_degradation_simple_ip3_cyt_flux);
};
