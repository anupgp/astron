// Time-stamp: <2016-09-16 11:40:41 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Ref: De Young & Keizer PNAS(1992)
// Note: Number of IP3 receptors = 1. Number of IP3 receptors are taken into account by the maximum flux parameter.
// Note: Change in ip3_cyt concentration due to binding with IP3 receptor is not considered.

#include <vector>
#include <iostream>
#include <cmath>

#include "insilico/core.hpp"

#include "physical_constants.hpp"
#include "global_variables.hpp"
#include "data_types.hpp"
#include "ip3_receptor_yk.hpp"

void ip3_receptor_yk::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{

// Get parameter values
  
  const double a1 = newinsilico::neuron_value(index, "ip3r_yk_a1");
  const double a2 = newinsilico::neuron_value(index, "ip3r_yk_a2");
  const double a3 = newinsilico::neuron_value(index, "ip3r_yk_a3");
  const double a4 = newinsilico::neuron_value(index, "ip3r_yk_a4");
  const double a5 = newinsilico::neuron_value(index, "ip3r_yk_a5");

  const double b1 = newinsilico::neuron_value(index, "ip3r_yk_b1");
  const double b2 = newinsilico::neuron_value(index, "ip3r_yk_b2");
  const double b3 = newinsilico::neuron_value(index, "ip3r_yk_b3");
  const double b4 = newinsilico::neuron_value(index, "ip3r_yk_b4");
  const double b5 = newinsilico::neuron_value(index, "ip3r_yk_b5");

  const double ip3r_yk_flux_coef = newinsilico::neuron_value(index, "ip3r_yk_flux_coef");
  const double ip3r_yk_num = newinsilico::neuron_value(index, "ip3r_yk_num");

  // Get all variable indices
  unsigned ca_cyt_index = newinsilico::get_neuron_index(index, "ca_cyt");
  unsigned ca_er_index = newinsilico::get_neuron_index(index, "ca_er");
  unsigned ip3_cyt_index = newinsilico::get_neuron_index(index, "ip3_cyt");

  unsigned s000_index = newinsilico::get_neuron_index(index, "ip3r_yk_s000");
  unsigned s100_index = newinsilico::get_neuron_index(index, "ip3r_yk_s100");
  unsigned s101_index = newinsilico::get_neuron_index(index, "ip3r_yk_s101");
  unsigned s001_index = newinsilico::get_neuron_index(index, "ip3r_yk_s001");
  unsigned s010_index = newinsilico::get_neuron_index(index, "ip3r_yk_s010");
  unsigned s110_index = newinsilico::get_neuron_index(index, "ip3r_yk_s110");
  unsigned s111_index = newinsilico::get_neuron_index(index, "ip3r_yk_s111");
  unsigned s011_index = newinsilico::get_neuron_index(index, "ip3r_yk_s011");

  // Set lower limits on variable values

  variables[ca_cyt_index] = std::max<double>(variables[ca_cyt_index],0.0);
  variables[ca_er_index] = std::max<double>(variables[ca_er_index],0.0);
  variables[ip3_cyt_index] = std::max<double>(variables[ip3_cyt_index],0.0);

  variables[s000_index] = std::max<double>(variables[s000_index],0.0);
  variables[s100_index] = std::max<double>(variables[s100_index],0.0);
  variables[s101_index] = std::max<double>(variables[s101_index],0.0);
  variables[s001_index] = std::max<double>(variables[s001_index],0.0);
  variables[s010_index] = std::max<double>(variables[s010_index],0.0);
  variables[s110_index] = std::max<double>(variables[s110_index],0.0);
  variables[s111_index] = std::max<double>(variables[s111_index],0.0);
  variables[s011_index] = std::max<double>(variables[s011_index],0.0);
		
  // Special assignments
		    
  // Get variable values
  double ca_cyt = variables[ca_cyt_index];
  double ca_er = variables[ca_er_index];
  double ip3_cyt = variables[ip3_cyt_index];

  double s000 = variables[s000_index];
  double s100 = variables[s100_index];
  double s101 = variables[s101_index];
  double s001 = variables[s001_index];
  double s010 = variables[s010_index];
  double s110 = variables[s110_index];
  double s111 = variables[s111_index];
  double s011 = variables[s011_index];

  // Compute dxdt values
  dxdt[s000_index] = (-s000 * a4 * ca_cyt) + (s001 * b4) + (-s000 * a1 * ip3_cyt) + (s100 * b1) + (-s000 * a5 * ca_cyt) + (s010 * b5);
  dxdt[s100_index] = (-s100 * a2 * ca_cyt) + (s101 * b2) + (-s100 * b1) + (s000 * a1 * ip3_cyt) + (-s100 * a5 * ca_cyt) + (s110 * b5);
  dxdt[s101_index] = (-s101 * b3) + (s001 * a3 * ip3_cyt) + (-s101 * b2) + (s100 * a2 * ca_cyt) + (-s101 * a5 * ca_cyt) + (s111 * b5);
  dxdt[s001_index] = (-s001 * b4) + (s000 * a4 * ca_cyt) + (-s001 * a3 * ip3_cyt) + (s101 * b3) + (-s001 * a5 * ca_cyt) + (s011 * b5);
  dxdt[s010_index] = (-s010 * a4 * ca_cyt) + (s011 * b4) + (-s010 * a1 * ip3_cyt) + (s110 * b1) + (-s010 * b5) + (s000 * a5 * ca_cyt);
  dxdt[s110_index] = (-s110 * a2 * ca_cyt) + (s111 * b2) + (-s110 * b1) + (s010 * a1 * ip3_cyt) + (-s110 * b5) + (s100 * a5 * ca_cyt);
  dxdt[s111_index] = (-s111 * b3) + (s011 * a3 * ip3_cyt) + (-s111 * b2) + (s110 * a2 * ca_cyt) + (-s111 * b5) + (s101 * a5 * ca_cyt);
  dxdt[s011_index] = (-s011 * b4) + (s010 * a4 * ca_cyt) + (-s011 * a3 * ip3_cyt) + (s111 * b3) + (-s011 * b5) + (s001 * a5 * ca_cyt);

  // compute the flux
  double ip3r_yk_ca_cyt_flux =  (ca_er - ca_cyt) * ip3r_yk_flux_coef * pow(s110,3) * ip3r_yk_num;

  newinsilico::neuron_value(index, "ip3r_yk_ca_cyt_flux", ip3r_yk_ca_cyt_flux);
  newinsilico::neuron_value(index, "ip3r_yk_open_fraction", pow(s110,3));

}
