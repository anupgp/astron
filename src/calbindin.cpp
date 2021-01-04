// Time-stamp: <2019-01-05 16:49:17 macbookair> 
// Units: All SI units - seconds, Volts, Ampere, Meters, Simenes, Farads

#include <vector>
#include <iostream>
#include <cmath>

#include "include/new_insilico.hpp"

#include "data_types.hpp"
#include "calbindin.hpp"

void calbindin::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{

  // Get all variable indices
  unsigned ca_cyt_index = newinsilico::get_neuron_index(index, "ca_cyt");
  unsigned cbH0L0_index = newinsilico::get_neuron_index(index, "cb_H0L0");
  unsigned cbH1L0_index = newinsilico::get_neuron_index(index, "cb_H1L0");
  unsigned cbH2L0_index = newinsilico::get_neuron_index(index, "cb_H2L0");
  unsigned cbH3L0_index = newinsilico::get_neuron_index(index, "cb_H3L0");

  unsigned cbH0L1_index = newinsilico::get_neuron_index(index, "cb_H0L1");
  unsigned cbH1L1_index = newinsilico::get_neuron_index(index, "cb_H1L1");
  unsigned cbH2L1_index = newinsilico::get_neuron_index(index, "cb_H2L1");
  unsigned cbH3L1_index = newinsilico::get_neuron_index(index, "cb_H3L1");

  // Get parameter values  
  const double kon_f = newinsilico::neuron_value(index, "cb_kon_f");
  const double koff_f = newinsilico::neuron_value(index, "cb_koff_f");
  const double kon_s = newinsilico::neuron_value(index, "cb_kon_s");
  const double koff_s = newinsilico::neuron_value(index, "cb_koff_s");

  variables[cbH0L0_index] = std::max<double>(variables[cbH0L0_index],0.0);
  variables[cbH1L0_index] = std::max<double>(variables[cbH1L0_index],0.0);
  variables[cbH2L0_index] = std::max<double>(variables[cbH2L0_index],0.0);
  variables[cbH3L0_index] = std::max<double>(variables[cbH3L0_index],0.0);

  variables[cbH0L1_index] = std::max<double>(variables[cbH0L1_index],0.0);
  variables[cbH1L1_index] = std::max<double>(variables[cbH1L1_index],0.0);
  variables[cbH2L1_index] = std::max<double>(variables[cbH2L1_index],0.0);
  variables[cbH3L1_index] = std::max<double>(variables[cbH3L1_index],0.0);
  
  // Get variable values
  double ca_cyt = variables[ca_cyt_index];
  double cbH0L0 = variables[cbH0L0_index];
  double cbH1L0 = variables[cbH1L0_index];
  double cbH2L0 = variables[cbH2L0_index];
  double cbH3L0 = variables[cbH3L0_index];

  double cbH0L1 = variables[cbH0L1_index];
  double cbH1L1 = variables[cbH1L1_index];
  double cbH2L1 = variables[cbH2L1_index];
  double cbH3L1 = variables[cbH3L1_index];

  // Compute dxdt values
  dxdt[cbH0L0_index] = (-cbH0L0 * ca_cyt * 3 * kon_f) + (cbH1L0 * koff_f) + (-cbH0L0 * ca_cyt * kon_s) + (cbH0L1 * koff_s);
  dxdt[cbH1L0_index] = (-cbH1L0 * ca_cyt * 2 * kon_f) + (cbH2L0 * 2 * koff_f) + (-cbH1L0 * ca_cyt * kon_s) + (cbH1L1 * koff_s) + (-cbH1L0 * koff_f) + (cbH0L0 * ca_cyt * 3 * kon_f);
  dxdt[cbH2L0_index] = (-cbH2L0 * ca_cyt * kon_f) + (cbH3L0 * 3 * koff_f) + (-cbH2L0 * ca_cyt * kon_s) + (cbH2L1 * koff_s) + (-cbH2L0 * 2 * koff_f) + (cbH1L0 * ca_cyt * 2 * kon_f);
  dxdt[cbH3L0_index] = (-cbH3L0 * ca_cyt * kon_s) + (cbH3L1 * koff_s) + (-cbH3L0 * 3 * koff_f) + (cbH2L0 * ca_cyt * kon_f);
  
  dxdt[cbH0L1_index] = (-cbH0L1 * ca_cyt * 3 * kon_f) + (cbH1L1 * koff_f) + (-cbH0L1 * koff_s) + (cbH0L0 * ca_cyt * kon_s);
  dxdt[cbH1L1_index] = (-cbH1L1 * ca_cyt * 2 * kon_f) + (cbH2L1 * 2 * koff_f) + (-cbH1L1 * koff_s) + (cbH1L0 * ca_cyt * kon_s) + (-cbH1L1 * koff_f) + (cbH0L1 * ca_cyt * 3 * kon_f);
  dxdt[cbH2L1_index] = (-cbH2L1 * ca_cyt * kon_f) + (cbH3L1 * 3 * koff_f) + (-cbH2L1 * koff_s) + (cbH2L0 * ca_cyt * kon_s) + (-cbH2L1 * 2 * koff_f) + (cbH1L1 * ca_cyt * 2 * kon_f);
  dxdt[cbH3L1_index] = (-cbH3L1 * koff_s) + (cbH3L0 * ca_cyt * kon_s) + (-cbH3L1 * 3 * koff_f) + (cbH2L1 * ca_cyt * kon_f);

  double cb_ca_cyt_flux = (-cbH0L0 * ca_cyt * 3 * kon_f) + (cbH1L0 * koff_f) + (-cbH1L0 * ca_cyt * 2 * kon_f) + (cbH2L0 * 2 * koff_f) + (-cbH2L0 * ca_cyt * kon_f) + (cbH3L0 * 3 * koff_f) +
    (-cbH0L0 * ca_cyt * kon_s) + (cbH0L1 * koff_s) + (-cbH1L0 * ca_cyt * kon_s) + (cbH1L1 * koff_s) + (-cbH2L0 * ca_cyt * kon_s) + (cbH2L1 * koff_s) + (-cbH3L0 * ca_cyt * kon_s) + (cbH3L1 * koff_s) +
    (-cbH0L1 * ca_cyt * 3 * kon_f) + (cbH1L1 * koff_f) + (-cbH1L1 * ca_cyt * 2 * kon_f) + (cbH2L1 * 2 * koff_f) + (-cbH2L1 * ca_cyt * kon_f) + (cbH3L1 * 3 * koff_f);

  // Update values

  double cb_total = cbH0L0 + cbH1L0 + cbH2L0 + cbH3L0 + cbH0L1 + cbH1L1 + cbH2L1 + cbH3L1;

  newinsilico::neuron_value(index, "calbindin_ca_cyt_flux", cb_ca_cyt_flux);
  newinsilico::neuron_value(index, "calbindin_total", cb_total);
};
