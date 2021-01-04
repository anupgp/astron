// Time-stamp: <2017-01-27 14:02:10 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Ref: higgins2006; bartol2015

#include <vector>
#include <iostream>
#include <cmath>

#include "insilico/core.hpp"

#include "data_types.hpp"
#include "physical_constants.hpp"
#include "global_variables.hpp"

#include "serca_higg.hpp"

namespace consts=astron::phy_const;
namespace gvars=astron::globals;

void serca_higg::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{

  // Get all variable indices
  unsigned ca_cyt_index = newinsilico::get_neuron_index(index, "ca_cyt");
  unsigned ca_er_index = newinsilico::get_neuron_index(index, "ca_er");
  
  unsigned x0_index = newinsilico::get_neuron_index(index, "serca_higg_x0");
  unsigned x1_index = newinsilico::get_neuron_index(index, "serca_higg_x1");
  unsigned x2_index = newinsilico::get_neuron_index(index, "serca_higg_x2");
  unsigned y0_index = newinsilico::get_neuron_index(index, "serca_higg_y0");
  unsigned y1_index = newinsilico::get_neuron_index(index, "serca_higg_y1");
  unsigned y2_index = newinsilico::get_neuron_index(index, "serca_higg_y2");

  // Get all parameter values
  const double kx0x1 = newinsilico::neuron_value(index, "serca_higg_kx0x1");
  const double kx1x0 = newinsilico::neuron_value(index, "serca_higg_kx1x0");
  const double kx1x2 = newinsilico::neuron_value(index, "serca_higg_kx1x2");
  const double kx2x1 = newinsilico::neuron_value(index, "serca_higg_kx2x1");
  const double kx2y2 = newinsilico::neuron_value(index, "serca_higg_kx2y2");
  const double ky2x2 = newinsilico::neuron_value(index, "serca_higg_ky2x2");
  const double kx0y0 = newinsilico::neuron_value(index, "serca_higg_kx0y0");
  const double ky0x0 = newinsilico::neuron_value(index, "serca_higg_ky0x0");
  const double ky0y1 = newinsilico::neuron_value(index, "serca_higg_ky0y1");
  const double ky1y0 = newinsilico::neuron_value(index, "serca_higg_ky1y0");
  const double ky1y2 = newinsilico::neuron_value(index, "serca_higg_ky1y2");
  const double ky2y1 = newinsilico::neuron_value(index, "serca_higg_ky2y1");

  const double density = newinsilico::neuron_value(index, "serca_higg_density");
  const double area_ratio_er_cyt = newinsilico::neuron_value(index, "area_ratio_er_cyt");
  const double area_volume_ratio_cyt = newinsilico::neuron_value(index, "area_volume_ratio_cyt");
  const double volume_cyt = newinsilico::neuron_value(index, "volume_cyt");
  const double volume_ratio_er_cyt = newinsilico::neuron_value(index, "volume_ratio_er_cyt");

  double area_er = volume_cyt * area_volume_ratio_cyt * area_ratio_er_cyt;
  double volume_er = volume_cyt * volume_ratio_er_cyt;
  
  // std::cout << "area_er: " << area_er << " volume_er: " << volume_er <<"\n";

  // Load initial values of serca
  const double init_check  = newinsilico::neuron_value(index, "serca_higg_init_check");
  if (init_check <= 0) {  
    // variables[x0_index] = (density * area_er) / (consts::Av * volume_er * 1000);
    variables[x0_index] = variables[x0_index] * (density * area_er);
    variables[x1_index] = variables[x1_index] * (density * area_er);
    variables[x2_index] = variables[x2_index] * (density * area_er);
    variables[y0_index] = variables[y0_index] * (density * area_er);
    variables[y1_index] = variables[y1_index] * (density * area_er);
    variables[y2_index] = variables[y2_index] * (density * area_er);
    // Update serca initialization check value
    newinsilico::neuron_value(index, "serca_higg_init_check", 1.0);
  }

  // Set lower limits on variable values  
  variables[ca_cyt_index] = std::max<double>(variables[ca_cyt_index],0.0);
  variables[ca_er_index] = std::max<double>(variables[ca_er_index],0.0);

  variables[x0_index] = std::max<double>(variables[x0_index],0.0);
  variables[x1_index] = std::max<double>(variables[x1_index],0.0);
  variables[x2_index] = std::max<double>(variables[x2_index],0.0);
  variables[y0_index] = std::max<double>(variables[y0_index],0.0);
  variables[y1_index] = std::max<double>(variables[y1_index],0.0);
  variables[y2_index] = std::max<double>(variables[y2_index],0.0);
  
  // Get all variable values
  double ca_cyt = variables[ca_cyt_index];
  double ca_er = variables[ca_er_index];

  double x0 = variables[x0_index];
  double x1 = variables[x1_index];
  double x2 = variables[x2_index];
  double y0 = variables[y0_index];  
  double y1 = variables[y1_index];
  double y2 = variables[y2_index];
  
  // --------------------------------------------

  dxdt[x0_index] = (-x0 * kx0x1 * ca_cyt) + (x1 * kx1x0) + (-x0 * kx0y0) + (y0 * ky0x0);
  dxdt[x1_index] = (-x1 * kx1x0) + (x0 * kx0x1 * ca_cyt) + (-x1 * kx1x2 * ca_cyt) + (x2 * kx2x1);
  dxdt[x2_index] = (-x2 * kx2x1) + (x1 * kx1x2 * ca_cyt) + (-x2 * kx2y2) + (y2 * ky2x2);
  
  dxdt[y0_index] = (-y0 * ky0x0) + (x0 * kx0y0) + (-y0 * ky0y1 * ca_er) + (y1 * ky1y0);
  dxdt[y1_index] = (-y1 * ky1y0) + (y0 * ky0y1 * ca_er) + (-y1 * ky1y2 * ca_er) + (y2 * ky2y1);
  dxdt[y2_index] = (-y2 * ky2y1) + (y1 * ky1y2 * ca_er) + (-y2 * ky2x2) + (x2 * kx2y2);

  double serca_higg_ca_cyt_flux = ((-x0 * kx0x1 * ca_cyt) + (x1 * kx1x0) + (-x1 * kx1x2 * ca_cyt) + (x2 * kx2x1))
    / (consts::Av * volume_cyt * 1000);
  double serca_higg_ca_er_flux = ((-y0 * ky0y1 * ca_er) + (y1 * ky1y0) + (-y1 * ky1y2 * ca_er) + (y2 * ky2y1))
    / (consts::Av * volume_er * 1000);

  // std::cout << "serca_higg_ca_cyt_flux: " << serca_higg_ca_cyt_flux << " serca_higg_ca_er_flux: " << serca_higg_ca_er_flux << "\n";

  // Update values
  newinsilico::neuron_value(index, "serca_higg_ca_cyt_flux", serca_higg_ca_cyt_flux);
  newinsilico::neuron_value(index, "serca_higg_ca_er_flux", serca_higg_ca_er_flux);
};
