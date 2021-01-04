// Time-stamp: <2019-01-04 13:41:36 macbookair>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Description: The influence (feedback) of Calcium on ip3 production
// Ref 1: A. Di Garbo et al., Bio Systems (2007)
// Ref 2: T.Hofer, L. Venance et al., Jr. Neuro. Sci (2002)
// Ref 3: M. Stamatakis Jr. Theor. Bio. (2006) 
// Ref 4: De Pitta, M. Goldberg, V. Volman et al. (2009)
// The influence (feedback) of Calcium on ip3 production (Ref 1 & Ref 2) 

#include <vector>
#include <iostream>
#include <cmath>

#include "include/new_insilico.hpp"

#include "physical_constants.hpp"
#include "global_variables.hpp"
#include "data_types.hpp"
#include "plc_delta_hill.hpp"

void plc_delta_hill::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{

  // Get all variable indices
  unsigned ca_cyt_index = newinsilico::get_neuron_index(index, "ca_cyt");
  unsigned ip3_cyt_index = newinsilico::get_neuron_index(index, "ip3_cyt");

  // Get parameter values
  const double v_max = newinsilico::neuron_value(index, "plc_delta_hill_v_max");
  const double k_diss = newinsilico::neuron_value(index, "plc_delta_hill_k_diss");
  const double ip3_ihb = newinsilico::neuron_value(index, "plc_delta_hill_ip3_ihb");
  const double coop = newinsilico::neuron_value(index, "plc_delta_hill_coop");

  // Set lower limits on variable values
  variables[ca_cyt_index] = std::max(variables[ca_cyt_index],0.0);

  // Get variable values
  double ca_cyt = variables[ca_cyt_index];
  double ip3_cyt = std::max<double>(variables[ip3_cyt_index], 0.0);

 // Compute dxdt values

  // Ref 4: De Pitta, M. Goldberg, V. Volman et al. (2009)
  double plc_delta_hill_ip3_cyt_flux = (v_max/(1 + (ip3_cyt/ip3_ihb))) * (pow(ca_cyt,coop) / (pow(ca_cyt,coop) + pow(k_diss,coop)));
  
  // Ref 2: T.Hofer, L. Venance et al., Jr. Neuro. Sci (2002)
  // double plc_delta_hill_ip3_cyt_flux = (v_max) * (pow(ca_cyt,coop) / (pow(ca_cyt,coop) + pow(k_diss,coop)));

  newinsilico::neuron_value(index, "plc_delta_hill_ip3_cyt_flux", plc_delta_hill_ip3_cyt_flux);

}
