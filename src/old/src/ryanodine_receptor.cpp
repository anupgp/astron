// Time-stamp: <2016-03-15 17:00:19 anup>
// Units: All SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Ref: Saftenku, William & Sitsapesan, Biophysical Jr. (2001)
// Note: Number of RYR receptors = 1. Number of RYR receptors are taken into account by the maximum flux parameter.
// Note: Change in ca_cyt concentration due to binding with RYR receptor is not considered.

#include <vector>
#include <iostream>
#include <cmath>

#include "insilico/core.hpp"

#include "data_types.hpp"
#include "ryanodine_receptor.hpp"

void ryanodine_receptor::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{
  // Get all variable indices
  unsigned ca_cyt_index = newinsilico::get_neuron_index(index, "ca_cyt");
  unsigned ca_er_index = newinsilico::get_neuron_index(index, "ca_er");

  unsigned C1_index = newinsilico::get_neuron_index(index, "ryr_C1");
  unsigned C2_index = newinsilico::get_neuron_index(index, "ryr_C2");
  unsigned C3_index = newinsilico::get_neuron_index(index, "ryr_C3");
  unsigned C4_index = newinsilico::get_neuron_index(index, "ryr_C4");
  unsigned C5_index = newinsilico::get_neuron_index(index, "ryr_C5");

  unsigned O1_index = newinsilico::get_neuron_index(index, "ryr_O1");
  unsigned O2_index = newinsilico::get_neuron_index(index, "ryr_O2");
  unsigned O3_index = newinsilico::get_neuron_index(index, "ryr_O3");
  
  //// Set lower limits on variable values
  variables[C1_index] = std::max<double>(variables[C1_index],0.0);
  variables[C2_index] = std::max<double>(variables[C2_index],0.0);
  variables[C3_index] = std::max<double>(variables[C3_index],0.0);
  variables[C4_index] = std::max<double>(variables[C4_index],0.0);
  variables[C5_index] = std::max<double>(variables[C5_index],0.0);
  
  variables[O1_index] = std::max<double>(variables[O1_index],0.0);
  variables[O2_index] = std::max<double>(variables[O2_index],0.0);
  variables[O3_index] = std::max<double>(variables[O3_index],0.0);
  
  // Set upper limits on variable values
  variables[C1_index] = std::min<double>(variables[C1_index],1.0);
  variables[C2_index] = std::min<double>(variables[C2_index],1.0);
  variables[C3_index] = std::min<double>(variables[C3_index],1.0);
  variables[C4_index] = std::min<double>(variables[C4_index],1.0);
  variables[C5_index] = std::min<double>(variables[C5_index],1.0);
  
  variables[O1_index] = std::min<double>(variables[O1_index],1.0);
  variables[O2_index] = std::min<double>(variables[O2_index],1.0);
  variables[O3_index] = std::min<double>(variables[O3_index],1.0);

  // Get variable values
  double ca_cyt = variables[ca_cyt_index];
  double ca_er = variables[ca_er_index];

  double C1 = variables[C1_index];
  double C2 = variables[C2_index];
  double C3 = variables[C3_index];
  double C4 = variables[C4_index];
  double C5 = variables[C5_index];

  double O1 = variables[O1_index];
  double O2 = variables[O2_index];
  double O3 = variables[O3_index];

  // Get parameter values
  double ryr_flux_coef = newinsilico::neuron_value(index, "ryr_flux_coef");
  double ryr_num = newinsilico::neuron_value(index, "ryr_num");

  double kc1c2 = newinsilico::neuron_value(index, "ryr_kc1c2");
  double kc2c1 = newinsilico::neuron_value(index, "ryr_kc2c1");
  double kc2c3 = newinsilico::neuron_value(index, "ryr_kc2c3");
  double kc3c2 = newinsilico::neuron_value(index, "ryr_kc3c2");
  double kc3o2 = newinsilico::neuron_value(index, "ryr_kc3o2");
  double ko2c3 = newinsilico::neuron_value(index, "ryr_ko2c3");
  double ko2c4 = newinsilico::neuron_value(index, "ryr_ko2c4");
  double kc4o2 = newinsilico::neuron_value(index, "ryr_kc4o2");
  double kc3o3 = newinsilico::neuron_value(index, "ryr_kc3o3");
  double ko3c3 = newinsilico::neuron_value(index, "ryr_ko3c3");
  double ko3c4 = newinsilico::neuron_value(index, "ryr_ko3c4");
  double kc4o3 = newinsilico::neuron_value(index, "ryr_kc4o3");
  double kc3o1 = newinsilico::neuron_value(index, "ryr_kc3o1");
  double ko1c3 = newinsilico::neuron_value(index, "ryr_ko1c3");
  double kc2c5 = newinsilico::neuron_value(index, "ryr_kc2c5");
  double kc5c2 = newinsilico::neuron_value(index, "ryr_kc5c2");

  // dxdt values

  dxdt[C1_index] = (-C1 * ca_cyt * kc1c2) + (C2 * kc2c1);

  dxdt[C2_index] = (-C2 * ca_cyt * kc2c3) + (C3 * kc3c2) + (-C2 * kc2c1) 
    + (C1 * ca_cyt * kc1c2) + (-C2 * kc2c5) + (C5 * kc5c2);

  dxdt[C5_index] = (-C5 * kc5c2) + (C2 * kc2c5);

  dxdt[C3_index] = (-C3 * kc3c2) + (C2 * ca_cyt * kc2c3) + (-C3 * kc3o1) 
    + (O1 * ko1c3) + (-C3 * kc3o2) + (O2 * ko2c3) + (-C3 * kc3o3) + (O3 * ko3c3);

  dxdt[O1_index] = (-O1 * ko1c3) + (C3 * kc3o1);
  dxdt[O2_index] = (-O2 * ko2c3) + (C3 * kc3o2) + (-O2 * ko2c4) + (C4 * kc4o2);
  dxdt[O3_index] = (-O3 * ko3c3) + (C3 * kc3o3) + (-O3 * ko3c4) + (C4 * kc4o3);
  dxdt[C4_index] = (-C4 * kc4o2) + (O2 * ko2c4) + (-C4 * kc4o3) + (O3 * ko3c4);

  double ryr_open_prob = (O1 + O2 + O3)/(C1+C2+C3+C4+C5+O1+O2+O3);
  double ryr_ca_cyt_flux = (ca_er - ca_cyt) * ryr_open_prob * ryr_flux_coef * ryr_num;
  
  newinsilico::neuron_value(index, "ryr_ca_cyt_flux", ryr_ca_cyt_flux);
  newinsilico::neuron_value(index, "ryr_open_prob", ryr_open_prob);
};
