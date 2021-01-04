// Time-stamp: <2019-01-03 16:57:17 macbookair>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Ref: engel2005

#include <vector>
#include <iostream>
#include <cmath>

#include "include/new_insilico.hpp"

#include "na_pre.hpp"

typedef std::vector<double> state_type;

// na_pre definition
void na_pre::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 

{
  unsigned voltage_index = newinsilico::get_neuron_index(index, "voltage");
  unsigned m_index = newinsilico::get_neuron_index(index, "na_pre_m");
  unsigned h_index = newinsilico::get_neuron_index(index, "na_pre_h");

  const double rev = newinsilico::neuron_value(index,"na_pre_rev");   // Reversal potential for Sodium currents in Volts
  const double gmax = newinsilico::neuron_value(index,"na_pre_gmax");   // Maximum conductance for Sodium channels S/m^2
  
  variables[m_index] = std::max(variables[m_index],0.0);
  variables[m_index] = std::min(variables[m_index],1.0);
  variables[h_index] = std::max(variables[h_index],0.0);
  variables[h_index] = std::min(variables[h_index],1.0);
    
  double voltage = variables[voltage_index] * 1e03;
  double m = variables[m_index];
  double h = variables[h_index];
  // ----------------------------------------------------
  // activation & deactivation of m gate
  const double aalpham = newinsilico::neuron_value(index,"na_pre_aalpham");   // activation rate S^-1 (1/S)
  const double balpham = newinsilico::neuron_value(index,"na_pre_balpham");   // voltage shift V^-3 (mV)
  const double calpham = newinsilico::neuron_value(index,"na_pre_calpham");   // voltage scale V^-3 (mV)
  double alpha_m = -aalpham * (voltage + balpham) / (exp( -(voltage + balpham) / calpham) - 1 );
  const double abetam = newinsilico::neuron_value(index,"na_pre_abetam");   // activation rate S^-1 (1/S)
  const double cbetam = newinsilico::neuron_value(index,"na_pre_cbetam");   // voltage scale V^-3 (mV)
  double beta_m = abetam  * exp( -voltage / cbetam);
  // ----------------------------------------------------
  // activation & deactivation of h gate
  const double aalphah = newinsilico::neuron_value(index,"na_pre_aalphah");   // activation rate S^-1 (1/S)
  const double calphah = newinsilico::neuron_value(index,"na_pre_calphah");   // voltage scale V^-3 (mV)
  double alpha_h = aalphah * exp( -voltage / calphah);
  const double abetah = newinsilico::neuron_value(index,"na_pre_abetah");   // activation rate S^-1 (1/S)
  const double bbetah = newinsilico::neuron_value(index,"na_pre_bbetah");   // voltage shift V^-3 (mV)
  const double cbetah = newinsilico::neuron_value(index,"na_pre_cbetah");   // voltage scale V^-3 (mV)
  double beta_h = ( abetah / ( exp( - (voltage + bbetah) / cbetah) + 1) );
  // ---------------------------------------------------
  dxdt[m_index] =  ( (alpha_m * (1-m)) - (beta_m * m));
  dxdt[h_index] =  ( (alpha_h * (1-h)) - (beta_h * h));
  // ---------------------------------------------------
  double i_na =  gmax * std::pow(m, 3) * h * ((voltage *1e-3) - rev);

  newinsilico::neuron_value(index, "na_pre_current",i_na);
};
