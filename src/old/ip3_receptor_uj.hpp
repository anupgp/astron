/* Last Revised Date: 29_APRIL_2015 */
/* Lastest status: not checked   */

#ifndef IP3_RECEPTOR_UJ_HPP_INCLUDED
#define IP3_RECEPTOR_UJ_HPP_INCLUDED

#include <vector>
#include <iostream>
#include <cmath>

#include "physical_constants.hpp"
#include "astron_global_variables.hpp"
#include "utility_functions.hpp"
#include "data_types.hpp"
#include "insilico-0.25/include/insilico/core.hpp"

//UNITS: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads

class ip3_receptor_uj
{
public:
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
  static double phi1(double ca_conc, unsigned index);
  static double phi2(double ca_conc, unsigned index);
  static double phi2b(double ca_conc, unsigned index);
  static double phi3(double ca_conc, unsigned index);
  static double phi4(double ca_conc, unsigned index);
  static double phi4b(double ca_conc, unsigned index);
  static double phi5(double ca_conc, unsigned index);
};

double ip3_receptor_uj::phi1(double ca_conc, unsigned index)
{
  // Get parameter values
  const double k1 = insilico::engine::neuron_value(index, "ip3r_uj_k1");
  const double k5 = insilico::engine::neuron_value(index, "ip3r_uj_k5");
  const double L1 = insilico::engine::neuron_value(index, "ip3r_uj_L1");
  const double L3 = insilico::engine::neuron_value(index, "ip3r_uj_L3");
  // Compute phi1
  double value = (((k5 * ca_conc) + (L1 * k1)) * ca_conc)/( L1 + (ca_conc * (1 + (L1/L3))));
  return (value);
}

//----------------
double ip3_receptor_uj::phi2(double ca_conc, unsigned index)
{
  // Get parameter values
  const double k2 = insilico::engine::neuron_value(index, "ip3r_uj_k2");
  const double l4 = insilico::engine::neuron_value(index, "ip3r_uj_l4");
  const double L1 = insilico::engine::neuron_value(index, "ip3r_uj_L1");
  const double L3 = insilico::engine::neuron_value(index, "ip3r_uj_L3");
  // Compute phi2
  double value = ( ((l4 * ca_conc) + (L3 * k2)) )/( L3 + (ca_conc * (1 + (L3/L1))));
  return (value);
}

//-----------------
double ip3_receptor_uj::phi2b(double ca_conc, unsigned index)
{
  // Get parameter values
  const double k2b = insilico::engine::neuron_value(index, "ip3r_uj_k2b");
  const double l4b = insilico::engine::neuron_value(index, "ip3r_uj_l4b");
  const double L3 = insilico::engine::neuron_value(index, "ip3r_uj_L3");
  const double L5 = insilico::engine::neuron_value(index, "ip3r_uj_L5");
  // Compute phi2b
  double value = ((l4b + k2b) * (ca_conc + L3)) / ( L3 + (ca_conc * (1 + (L3/L5))));
  return (value);
}

//-----------------
double ip3_receptor_uj::phi3(double ca_conc, unsigned index)
{
  // Get parameter values
  double k3 = insilico::engine::neuron_value(index, "ip3r_uj_k3");
  double L3 = insilico::engine::neuron_value(index, "ip3r_uj_L3");
  double L5 = insilico::engine::neuron_value(index, "ip3r_uj_L5");
  // Compute phi3
  double value = (k3 * L5) / ( L5 + (ca_conc * (1 + (L5/L3))));
  return (value);
}

//-----------------
double ip3_receptor_uj::phi4(double ca_conc, unsigned index)
{
  // Get parameter values
  double k4 = insilico::engine::neuron_value(index, "ip3r_uj_k4");
  double l6 = insilico::engine::neuron_value(index, "ip3r_uj_l6");
  double L3 = insilico::engine::neuron_value(index, "ip3r_uj_L3");
  double L5 = insilico::engine::neuron_value(index, "ip3r_uj_L5");
  // Compute phi4
  double value = (((k4 * L5) + l6) * ca_conc) / ( L5 + (ca_conc * (1 + (L5/L3))));
  return (value);
}

//-----------------
double ip3_receptor_uj::phi4b(double ca_conc, unsigned index)
{
  // Get parameter values
  double k4b = insilico::engine::neuron_value(index, "ip3r_uj_k4b");
  double l6b = insilico::engine::neuron_value(index, "ip3r_uj_l6b");
  double L1 = insilico::engine::neuron_value(index, "ip3r_uj_L1");
  // Compute phi4b
  double value = (k4b + l6b) / (1 + (ca_conc/L1));
  return (value);
}

//-----------------
double ip3_receptor_uj::phi5(double ca_conc, unsigned index)
{
  // Get parameter values
  double k1 = insilico::engine::neuron_value(index, "ip3r_uj_k1");
  double k5 = insilico::engine::neuron_value(index, "ip3r_uj_k5");
  double L1 = insilico::engine::neuron_value(index, "ip3r_uj_L1");
  // Compute phi5
  double value = (((k5 * ca_conc) + (L1 * k1)) * ca_conc) / (L1 + ca_conc);
  return (value);
}

//-----------------
void ip3_receptor_uj::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{

  // Get all variable indices
  unsigned ca_cyt_index = insilico::engine::neuron_index(index, "ca_cyt");
  unsigned ip3_cyt_index = insilico::engine::neuron_index(index, "ip3_cyt");
  unsigned ca_er_index = insilico::engine::neuron_index(index, "ca_er");

  unsigned R_index = insilico::engine::neuron_index(index, "ip3r_uj_R");
  unsigned I1_index = insilico::engine::neuron_index(index, "ip3r_uj_I1");
  unsigned O_index = insilico::engine::neuron_index(index, "ip3r_uj_O");
  unsigned A_index = insilico::engine::neuron_index(index, "ip3r_uj_A");
  unsigned I2_index = insilico::engine::neuron_index(index, "ip3r_uj_I2");
  unsigned S_index = insilico::engine::neuron_index(index, "ip3r_uj_S");

  // Set lower limits on variable values
  variables[ca_cyt_index] = std::max<double>(variables[ca_cyt_index],0.0);
  variables[ip3_cyt_index] = std::max<double>(variables[ip3_cyt_index],0.0);
  variables[ca_er_index] = std::max<double>(variables[ca_er_index],0.0);

  variables[R_index] = std::max<double>(variables[R_index],0.0);
  variables[I1_index] = std::max<double>(variables[I1_index],0.0);
  variables[O_index] = std::max<double>(variables[O_index],0.0);
  variables[A_index] = std::max<double>(variables[A_index],0.0);
  variables[I2_index] = std::max<double>(variables[I2_index],0.0);
  variables[S_index] = std::max<double>(variables[S_index],0.0);
				    
  // Get parameter values
  const double ip3r_uj_flux_coef = insilico::engine::neuron_value(index, "ip3r_uj_flux_coef");
  const double ip3r_uj_num = insilico::engine::neuron_value(index, "ip3r_uj_num");
  const double ip3_cyt_baseline = insilico::engine::neuron_value(index, "ip3_cyt_baseline");

  const double k1b = insilico::engine::neuron_value(index, "ip3r_uj_k1b");
  const double l2b = insilico::engine::neuron_value(index, "ip3r_uj_l2b");
  const double k3b = insilico::engine::neuron_value(index, "ip3r_uj_k3b");

  // Get variable values
  double ca_cyt = variables[ca_cyt_index];
  double ip3_cyt = variables[ip3_cyt_index];
  double ca_er = variables[ca_er_index];

  double R = variables[R_index];
  double I1 = variables[I1_index];
  double O = variables[O_index];
  double A = variables[A_index];
  double I2 = variables[I2_index];
  double S = variables[S_index];

  // Compute dxdt values
  dxdt[R_index] = (-R * phi1(ca_cyt,index)) + (I1 * (k1b + l2b)) + (-R * phi2(ca_cyt,index) * ip3_cyt) + (O * phi2b(ca_cyt,index));
  dxdt[I1_index] = (R * phi1(ca_cyt,index)) + (-I1 * (k1b + l2b));
  dxdt[O_index] = (-O * phi4(ca_cyt,index)) + (A * phi4b(ca_cyt,index)) + (-O * phi3(ca_cyt,index)) + (S * k3b) + (-O * phi2b(ca_cyt,index)) + (R * phi2(ca_cyt,index) * ip3_cyt);
  dxdt[A_index] = (-A * phi5(ca_cyt,index)) + (I2 * (k1b + l2b)) + (-A * phi4b(ca_cyt,index)) + (O * phi4(ca_cyt,index));
  dxdt[I2_index] = (-I2 * (k1b + l2b)) + (A * phi5(ca_cyt,index));
  dxdt[S_index] = (-S * k3b) + (O * phi3(ca_cyt,index));

  double ip3r_uj_ca_cyt_dxdt =  (ca_er - ca_cyt) * ip3r_uj_flux_coef * O * ip3r_uj_num; 
  double ip3r_uj_ca_er_dxdt = -ip3r_uj_ca_cyt_dxdt;
  double ip3r_uj_ip3_cyt_dxdt = (-ip3_cyt * R * phi2(ca_cyt,index)) + (O * phi2b(ca_cyt,index));

  insilico::engine::neuron_value(index, "ip3r_uj_ca_cyt_dxdt", ip3r_uj_ca_cyt_dxdt);
  insilico::engine::neuron_value(index, "ip3r_uj_ca_er_dxdt", ip3r_uj_ca_er_dxdt);
  insilico::engine::neuron_value(index, "ip3r_uj_ip3_cyt_dxdt", ip3r_uj_ip3_cyt_dxdt);

  insilico::engine::neuron_value(index, "ip3r_uj_flux", ip3r_uj_ca_cyt_dxdt);
  insilico::engine::neuron_value(index, "ip3r_flux", ip3r_uj_ca_cyt_dxdt);
}

#endif // IP3_RECEPTOR_UJ_HPP_INCLUDED
