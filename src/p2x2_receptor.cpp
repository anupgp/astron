// Time-stamp: <2019-01-04 13:39:08 macbookair>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Description: A kinetic model for p2x2 receptor activation using from Moffatt & Hume 2007
// Ref: Moffatt & Hume Jr. Gen, Phys (2007)

#include <vector>
#include <iostream>
#include <cmath>

#include "include/new_insilico.hpp"

#include "physical_constants.hpp"
#include "global_variables.hpp"
#include "data_types.hpp"
#include "p2x2_receptor.hpp"

namespace consts=astron::phy_const;

void p2x2_receptor::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{

  // Get variable indices 
  auto atp_ext_indices = newinsilico::get_pre_neuron_indices(index, "atp_ext");

  // Sum up all ATP_Ext from all the pre_neuron synapses
  double atp_ext = 0.0;
  for(unsigned int iter = 0; iter < atp_ext_indices.size(); ++iter) {
    atp_ext = atp_ext + std::max(variables[atp_ext_indices[iter]],0.0);
  }

  // Get all variable indices
  unsigned ca_cyt_index = newinsilico::get_neuron_index(index, "ca_cyt");
  unsigned voltage_index = newinsilico::get_neuron_index(index, "voltage");

  unsigned C1_index = newinsilico::get_neuron_index(index, "p2x2r_c1");
  unsigned C2_index = newinsilico::get_neuron_index(index, "p2x2r_c2");
  unsigned C3_index = newinsilico::get_neuron_index(index, "p2x2r_c3");
  unsigned C4_index = newinsilico::get_neuron_index(index, "p2x2r_c4");
  unsigned F5_index = newinsilico::get_neuron_index(index, "p2x2r_f5");
  unsigned O6_index = newinsilico::get_neuron_index(index, "p2x2r_o6");
  unsigned O7_index = newinsilico::get_neuron_index(index, "p2x2r_o7");
  unsigned F8_index = newinsilico::get_neuron_index(index, "p2x2r_f8");

  // Set lower limits on variable values
  variables[ca_cyt_index] = std::max<double>(variables[ca_cyt_index],0.0);

  variables[C1_index] = std::max<double>(variables[C1_index],0.0);
  variables[C2_index] = std::max<double>(variables[C2_index],0.0);
  variables[C3_index] = std::max<double>(variables[C3_index],0.0);
  variables[C4_index] = std::max<double>(variables[C4_index],0.0);
  variables[F5_index] = std::max<double>(variables[F5_index],0.0);
  variables[O6_index] = std::max<double>(variables[O6_index],0.0);
  variables[O7_index] = std::max<double>(variables[O7_index],0.0);
  variables[F8_index] = std::max<double>(variables[F8_index],0.0);

  // Get variable values
  double voltage = variables[voltage_index];

  double C1 = variables[C1_index];
  double C2 = variables[C2_index];
  double C3 = variables[C3_index];
  double C4 = variables[C4_index];
  double F5 = variables[F5_index];
  double O6 = variables[O6_index];
  double O7 = variables[O7_index];
  double F8 = variables[F8_index];

  // Get parameter values
  const double volume_cyt = newinsilico::neuron_value(index, "volume_cyt"); // Volume_Cyt (m^3)

  const double gmax = newinsilico::neuron_value(index, "p2x2r_gmax");
  const double num = newinsilico::neuron_value(index, "p2x2r_num");
  const double rev = newinsilico::neuron_value(index, "p2x2r_rev");
  const double ca_frac = newinsilico::neuron_value(index,"p2x2r_ca_frac");
  const double density = newinsilico::neuron_value(index, "p2x2r_density"); // density of p2x2r
  
  const double kon = newinsilico::neuron_value(index,   "p2x2r_kon");
  const double koff = newinsilico::neuron_value(index,  "p2x2r_koff");
  const double kon2 = newinsilico::neuron_value(index,  "p2x2r_kon2");
  const double koff2 = newinsilico::neuron_value(index, "p2x2r_koff2");
  const double kon3 = newinsilico::neuron_value(index,  "p2x2r_kon3");
  const double koff3 = newinsilico::neuron_value(index, "p2x2r_koff3");

  const double gamma = newinsilico::neuron_value(index, "p2x2r_gamma");
  const double delta = newinsilico::neuron_value(index, "p2x2r_delta");
  const double alpha = newinsilico::neuron_value(index, "p2x2r_alpha");
  const double beta = newinsilico::neuron_value(index,  "p2x2r_beta");
  const double alpha2 = newinsilico::neuron_value(index,"p2x2r_alpha2");
  const double beta2 = newinsilico::neuron_value(index, "p2x2r_beta2");
  const double zeta1 = newinsilico::neuron_value(index, "p2x2r_zeta1");
  const double eps1 = newinsilico::neuron_value(index,  "p2x2r_eps1");
  const double zeta2 = newinsilico::neuron_value(index, "p2x2r_zeta2");
  const double eps2 = newinsilico::neuron_value(index,  "p2x2r_eps2");

  // Compute dxdt values
  dxdt[C1_index] = (-C1 * atp_ext * kon) + (C2 * koff);
  dxdt[C2_index] = (-C2 * atp_ext * kon2) + (C3 * koff2) + (-C2 * koff) + (C1 * atp_ext * kon);
  dxdt[C3_index] = (-C3 * atp_ext * kon3) + (C4 * koff3) + (-C3 * koff2) + (C2 * atp_ext * kon2);
  dxdt[C4_index] = (-C4 * delta) + (F5 * gamma) + (-C4 * koff3) + (C3 * atp_ext * kon3);
  dxdt[F5_index] = (-F5 * beta) + (O6 * alpha) + (-F5 * beta2) + (O7 * alpha2) + (-F5 * gamma) + (C4 * delta);
  dxdt[O6_index] = (-O6 * zeta1) + (F8 * eps1) + (-O6 * alpha) + (F5 * beta);
  dxdt[O7_index] = (-O7 * zeta2) + (F8 * eps2) + (-O7 * alpha2) + (F5 * beta2);
  dxdt[F8_index] = (-F8 * eps1) + (O6 * zeta1) + (-F8 * eps2) + (O7 * zeta2);

  double fraction_of_open_channels = (O6 + O7)/(C1 + C2 + C3 + C4 + F5 + O6 + O7 + F8); 

  double p2x2r_current = -fraction_of_open_channels * gmax * (voltage - rev) * num;

  double p2x2r_ca_cyt_flux = (ca_frac * p2x2r_current ) /  
    (consts::F * consts::Z_Ca * 1000 * volume_cyt);

  // std::cout << p2x2r_ca_cyt_dxdt << " " << p2x2r_current;

  newinsilico::neuron_value(index, "p2x2r_open_fraction",fraction_of_open_channels);
  newinsilico::neuron_value(index, "p2x2r_current", p2x2r_current);
  newinsilico::neuron_value(index, "p2x2r_ca_cyt_flux",p2x2r_ca_cyt_flux);
}
