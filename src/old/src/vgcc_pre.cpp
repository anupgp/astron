// Time-stamp: <2016-08-22 15:56:27 anup>
// Units: All SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Ref: li2007; bischofberger2002

#include <vector>
#include <iostream>
#include <cmath>

#include "insilico/core.hpp"

#include "data_types.hpp"
#include "physical_constants.hpp"
#include "vgcc_pre.hpp"

namespace consts=astron::phy_const;

void vgcc_pre::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{
  // Get variable indices
  unsigned voltage_index = newinsilico::get_neuron_index(index, "voltage");
  unsigned ca_cyt_index = newinsilico::get_neuron_index(index, "ca_cyt");

  unsigned v0_index = newinsilico::get_neuron_index(index, "vgcc_pre_v0");
  unsigned v1_index = newinsilico::get_neuron_index(index, "vgcc_pre_v1");
  unsigned v2_index = newinsilico::get_neuron_index(index, "vgcc_pre_v2");
  unsigned v3_index = newinsilico::get_neuron_index(index, "vgcc_pre_v3");
  unsigned v4_index = newinsilico::get_neuron_index(index, "vgcc_pre_v4");
 
  // Get parameter values
  const double num = newinsilico::neuron_value(index, "vgcc_pre_num");


  const double gmax = newinsilico::neuron_value(index, "vgcc_pre_gmax");
  const double rev = newinsilico::neuron_value(index, "vgcc_pre_rev");

  const double a1r_vgcc_frac = newinsilico::neuron_value(index, "a1r_vgcc_frac");
  
  const double volume_cyt = newinsilico::neuron_value(index, "volume_cyt"); // Volume_Cyt (m^3)
  const double ca_ext = newinsilico::neuron_value(index, "ca_ext");
  
  // Set limits on variable values
  variables[v0_index] = std::max<double>(variables[v0_index],0.0);
  variables[v1_index] = std::max<double>(variables[v1_index],0.0);
  variables[v2_index] = std::max<double>(variables[v2_index],0.0);
  variables[v3_index] = std::max<double>(variables[v3_index],0.0);
  variables[v4_index] = std::max<double>(variables[v4_index],0.0);

  variables[v0_index] = std::min<double>(variables[v0_index],1.0);
  variables[v1_index] = std::min<double>(variables[v1_index],1.0);
  variables[v2_index] = std::min<double>(variables[v2_index],1.0);
  variables[v3_index] = std::min<double>(variables[v3_index],1.0);
  variables[v4_index] = std::min<double>(variables[v4_index],1.0);

  // Get variable values
  double voltage = variables[voltage_index];
  double ca_cyt = variables[ca_cyt_index];
  
  double v0 = variables[v0_index];
  double v1 = variables[v1_index];
  double v2 = variables[v2_index];
  double v3 = variables[v3_index];
  double v4 = variables[v4_index];
  
  double a1 = std::max(4.04e03 *  exp(voltage/49.14e-03),0.0);
  double a2 = std::max(6.70e03 * exp(voltage/42.08e-03),0.0);
  double a3 = std::max(4.39e03 * exp(voltage/55.31e-03),0.0);
  double a4 = std::max(17.33e03 * exp(voltage/26.55e-03),0.0);

  double b1 = std::max(2.88e03 * exp(-voltage/49.14e-03),0.0);
  double b2 = std::max(6.30e03 * exp(-voltage/42.08e-03),0.0);
  double b3 = std::max(8.16e03 * exp(-voltage/55.31e-03),0.0);
  double b4 = std::max(1.84e03 * exp(-voltage/26.55e-03),0.0);
  
  // dxdt values
  dxdt[v0_index] = ((-v0 * a1) + (v1 * b1)); /* d[C0]/dt */
  dxdt[v1_index] = ((-v1 * a2) + (v2 * b2) +  (-v1 * b1) + (a1 * v0)); /* d[C1]/dt */
  dxdt[v2_index] = ((-v2 * a3) + (v3 * b3) +  (-v2 * b2 ) + (v1 * a2)); /* d[C2]/dt */
  dxdt[v3_index] = ((-v3 * a4) + (v4 * b4) +  (-v3 * b3) + (v2 * a3)); /* d[C3]/dt */
  dxdt[v4_index] = ((-v4 * b4) + (v3 * a4)); /* d[0]/dt */
 
  // double vgcc_pre_current = ( gmax *  v4 * num * (voltage - rev) * (1 - a1r_vgcc_frac) );
  double vgcc_pre_current = ( gmax *  v4 * num * (voltage - get_E_Ca(ca_cyt,ca_ext)) * (1 - a1r_vgcc_frac) );
  //if (I_Ca > -1E-13) I_Ca = 0.0;
  double vgcc_pre_ca_cyt_flux = (-vgcc_pre_current / (consts::F * consts::Z_Ca * 1000 * volume_cyt));

  newinsilico::neuron_value(index, "vgcc_pre_current", vgcc_pre_current);
  newinsilico::neuron_value(index, "vgcc_pre_ca_cyt_flux", vgcc_pre_ca_cyt_flux);

};

// Calculates reversal potential from Calcium concentrations (Cytoplasmic Vs External)
double vgcc_pre::get_E_Ca(double ca_cyt_, double ca_ext_) 
{
  return (( (consts::R * consts::T) / (consts::Z_Ca * consts::F) ) * log(ca_ext_ / ca_cyt_));
};
