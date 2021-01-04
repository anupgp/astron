// Time-stamp: <2017-09-21 17:59:25 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Ref:bartol2015 

#include <vector>
#include <iostream>
#include <cmath>

#include "insilico/core.hpp"

#include "data_types.hpp"
#include "physical_constants.hpp"
#include "pmca.hpp"

namespace consts=astron::phy_const;

void pmca::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{
 
   // Get all variable indices
  int ca_cyt_index = newinsilico::get_neuron_index(index, "ca_cyt");  
  int pmca0_index = newinsilico::get_neuron_index(index, "pmca0");
  int pmca1_index = newinsilico::get_neuron_index(index, "pmca1");
  int pmca2_index = newinsilico::get_neuron_index(index, "pmca2");

  // Set lower limits on variable values
  const double kf1 = newinsilico::neuron_value(index, "pmca_kf1");
  const double kb1 = newinsilico::neuron_value(index, "pmca_kb1");
  const double kf2 = newinsilico::neuron_value(index, "pmca_kf2");
  const double kf3 = newinsilico::neuron_value(index, "pmca_kf3");
  const double kl = newinsilico::neuron_value(index, "pmca_kl");
  const double pmca_density = newinsilico::neuron_value(index, "pmca_density");


  const double area_volume_ratio_cyt = newinsilico::neuron_value(index, "area_volume_ratio_cyt");
  const double volume_cyt = newinsilico::neuron_value(index, "volume_cyt"); // volume_cyt (m^3)
  const double area_cyt = volume_cyt * area_volume_ratio_cyt;

  // Initialize pmca values at the start of the simulation from the pmca density
  const double pmca_init_check = newinsilico::neuron_value(index, "pmca_init_check");
  if (pmca_init_check <= 0){
    variables[pmca0_index] = variables[pmca0_index] * (pmca_density * area_cyt)/(astron::phy_const::Av * volume_cyt * 1000);
    variables[pmca1_index] = variables[pmca1_index] * (pmca_density * area_cyt)/(astron::phy_const::Av * volume_cyt * 1000);
    variables[pmca2_index] = variables[pmca2_index] * (pmca_density * area_cyt)/(astron::phy_const::Av * volume_cyt * 1000);
    newinsilico::neuron_value(index, "pmca_init_check", 1);
  }

  // Set lower limits on variable values
  variables[pmca0_index] = std::max<double>(variables[pmca0_index],0.0);
  variables[pmca1_index] = std::max<double>(variables[pmca1_index],0.0);
  variables[pmca2_index] = std::max<double>(variables[pmca2_index],0.0); 
  variables[ca_cyt_index] = std::max<double>(variables[ca_cyt_index],0.0);
  
  // Get variable values
  double ca_cyt = variables[ca_cyt_index];
  double pmca0 = variables[pmca0_index];
  double pmca1 = variables[pmca1_index];
  double pmca2 = variables[pmca2_index];

  dxdt[pmca0_index] = (-ca_cyt * pmca0 * kf1) + (pmca1 * kb1) + (pmca2 * kf3);
  dxdt[pmca1_index] = (-pmca1 * kb1) + (pmca0 * ca_cyt * kf1) + (-pmca1 * kf2);
  dxdt[pmca2_index] = (-pmca2 * kf3) + (pmca1 * kf2);

  double pmca_ca_cyt_flux = ((-ca_cyt * pmca0 * kf1) + (pmca1 * kb1) + (kl * pmca0));
  newinsilico::neuron_value(index, "pmca_ca_cyt_flux", pmca_ca_cyt_flux);
  
};
