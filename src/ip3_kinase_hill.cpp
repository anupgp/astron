// Time-stamp: <2019-01-04 13:34:58 macbookair>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Ref: De Pitta 2009

#include <vector>
#include <iostream>
#include <cmath>

#include "include/new_insilico.hpp"

#include "physical_constants.hpp"
#include "global_variables.hpp"
#include "data_types.hpp"
#include "ip3_kinase_hill.hpp"

void ip3_kinase_hill::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{

  // Get all variable indices
  unsigned ca_cyt_index = newinsilico::get_neuron_index(index, "ca_cyt");
  unsigned ip3_cyt_index = newinsilico::get_neuron_index(index, "ip3_cyt");

  // Set lower limits on variable values
  variables[ca_cyt_index] = std::max<double>(variables[ca_cyt_index],0.0);
  variables[ip3_cyt_index] = std::max<double>(variables[ip3_cyt_index],0.0);

  // Get parameter values
  const double v_max = newinsilico::neuron_value(index, "ip3_kinase_hill_v_max");
  const double k_diss_ca = newinsilico::neuron_value(index, "ip3_kinase_hill_k_diss_ca");
  const double k_diss_ip3 = newinsilico::neuron_value(index, "ip3_kinase_hill_k_diss_ip3");
  const double coop_ca = newinsilico::neuron_value(index, "ip3_kinase_hill_coop_ca");
  const double coop_ip3 = newinsilico::neuron_value(index, "ip3_kinase_hill_coop_ip3");

  // Get variable values
  double ca_cyt = std::max<double>(variables[ca_cyt_index], 0.0);
  double ip3_cyt = std::max<double>(variables[ip3_cyt_index], 0.0);

  // Compute dxdt values
  double ip3_kinase_hill_ip3_cyt_flux = v_max * (pow(ca_cyt,coop_ca) 
						 / (pow(ca_cyt,coop_ca) + pow(k_diss_ca,coop_ca))) *
    (pow(ip3_cyt,coop_ip3) / (pow(ip3_cyt,coop_ip3) + 
			      pow(k_diss_ip3,coop_ip3)));

  newinsilico::neuron_value(index, "ip3_kinase_hill_ip3_cyt_flux", ip3_kinase_hill_ip3_cyt_flux); 
}
