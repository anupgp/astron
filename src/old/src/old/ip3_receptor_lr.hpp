// Time-stamp: <2016-01-11 16:15:29 anup>
// UNITS: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Note: The Li-Rinzel model of ip3_receptors

#ifndef IP3_RECEPTOR_LR_HPP_INCLUDED
#define IP3_RECEPTOR_LR_HPP_INCLUDED

#include <vector>
#include <iostream>
#include <cmath>

#include "insilico-0.25/include/insilico/core.hpp"

#include "insilico/include/physical_constants.hpp"
#include "insilico/include/astron_global_variables.hpp"
#include "insilico/include/data_types.hpp"

class ip3_receptor_lr
{
public:
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

//-----------------
void ip3_receptor_lr::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{

// Get parameter values

  const double a2 = insilico::engine::neuron_value(index, "ip3r_lr_a2");
  const double d1 = insilico::engine::neuron_value(index, "ip3r_lr_d1");
  const double d2 = insilico::engine::neuron_value(index, "ip3r_lr_d2");
  const double d3 = insilico::engine::neuron_value(index, "ip3r_lr_d3");
  const double d4 = insilico::engine::neuron_value(index, "ip3r_lr_d4");
  const double d5 = insilico::engine::neuron_value(index, "ip3r_lr_d5");

  const double ip3r_lr_flux_coef = insilico::engine::neuron_value(index, "ip3r_lr_flux_coef");
  const double ip3r_lr_h_inf = insilico::engine::neuron_value(index, "ip3r_lr_h_inf");
  const double ip3r_lr_h_tau = insilico::engine::neuron_value(index, "ip3r_lr_h_tau");
  const double ip3r_lr_q2 = insilico::engine::neuron_value(index, "ip3r_lr_q2");
  const double ip3r_lr_m_inf = insilico::engine::neuron_value(index, "ip3r_lr_m_inf");
  const double ip3r_lr_n_inf = insilico::engine::neuron_value(index, "ip3r_lr_n_inf");

  const double volume_ratio_er_cyt = insilico::engine::neuron_value(index, "volume_ratio_er_cyt");

  // Get all variable indices
  unsigned ca_cyt_index = insilico::engine::neuron_index(index, "ca_cyt");
  unsigned ip3_cyt_index = insilico::engine::neuron_index(index, "ip3_cyt");
  unsigned ca_er_index = insilico::engine::neuron_index(index, "ca_er");

  unsigned s000_index = insilico::engine::neuron_index(index, "ip3r_yk_s000");
  unsigned s100_index = insilico::engine::neuron_index(index, "ip3r_yk_s100");
  unsigned s101_index = insilico::engine::neuron_index(index, "ip3r_yk_s101");
  unsigned s001_index = insilico::engine::neuron_index(index, "ip3r_yk_s001");
  unsigned s010_index = insilico::engine::neuron_index(index, "ip3r_yk_s010");
  unsigned s110_index = insilico::engine::neuron_index(index, "ip3r_yk_s110");
  unsigned s111_index = insilico::engine::neuron_index(index, "ip3r_yk_s111");
  unsigned s011_index = insilico::engine::neuron_index(index, "ip3r_yk_s011");

  // Set lower limits on variable values

  variables[ca_cyt_index] = std::max<double>(variables[ca_cyt_index],0.0);
  variables[ip3_cyt_index] = std::max<double>(variables[ip3_cyt_index],0.0);
  variables[ca_er_index] = std::max<double>(variables[ca_er_index],0.0);

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
  double ip3_cyt = variables[ip3_cyt_index];
  double ca_er = variables[ca_er_index];

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

  double ca_flux =  (ca_er - ca_cyt) * ip3r_yk_flux_coef * pow(s110,3) * ip3r_yk_num;
  double ip3r_yk_ca_cyt_dxdt =  ca_flux * volume_ratio_er_cyt; 
  double ip3r_yk_ca_er_dxdt = - ca_flux;

  insilico::engine::neuron_value(index, "ip3r_yk_ca_cyt_dxdt", ip3r_yk_ca_cyt_dxdt);
  insilico::engine::neuron_value(index, "ip3r_yk_ca_er_dxdt", ip3r_yk_ca_er_dxdt);

  insilico::engine::neuron_value(index, "ip3r_yk_flux", ip3r_yk_ca_cyt_dxdt);
  insilico::engine::neuron_value(index, "ip3r_yk_open_fraction", pow(s110,3));

}

#endif // IP3_RECEPTOR_YK_HPP_INCLUDED
