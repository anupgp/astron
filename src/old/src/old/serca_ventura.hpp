/* Last Revised Date: 19_APRIL_2015 */
/* Lastest status: not checked   */

//UNITS: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads

#ifndef SERCA_VENTURA_HPP_INCLUDED
#define SERCA_VENTURA_HPP_INCLUDED

#include <vector>
#include <iostream>
#include <cmath>

#include "data_types.hpp"
#include "physical_constants.hpp"
#include "global_variables.hpp"
#include "insilico-0.25/include/insilico/core.hpp"
#include "utility_functions.hpp"

namespace consts=astron::phy_const;
namespace gvars=astron::globals;

class SERCA_ventura
{
public:
  // Static functions
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

void SERCA_ventura::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{

  // Get all variable indices
  unsigned Ca_Cyt_index = insilico::engine::neuron_index(index, "Ca_Cyt");
  unsigned Ca_Er_index = insilico::engine::neuron_index(index, "Ca_Er");
  
  unsigned E0_index = insilico::engine::neuron_index(index, "serca_ventura_E0");
  unsigned E1_index = insilico::engine::neuron_index(index, "serca_ventura_E1");
  unsigned I1_index = insilico::engine::neuron_index(index, "serca_ventura_I1");
  unsigned I0_index = insilico::engine::neuron_index(index, "serca_ventura_I0");

  // Get all parameter values
  const double r1a = insilico::engine::neuron_value(index, "serca_ventura_r1a");
  const double r1b = insilico::engine::neuron_value(index, "serca_ventura_r1b");
  const double r2a = insilico::engine::neuron_value(index, "serca_ventura_r2a");
  const double r2b = insilico::engine::neuron_value(index, "serca_ventura_r2b");
 
  const double r3a = insilico::engine::neuron_value(index, "serca_ventura_r3a");
  const double r3b = insilico::engine::neuron_value(index, "serca_ventura_r3b");
  const double r4a = insilico::engine::neuron_value(index, "serca_ventura_r4a");
  const double r4b = insilico::engine::neuron_value(index, "serca_ventura_r4b");

  const double g = insilico::engine::neuron_value(index, "serca_ventura_gamma");
  const double Tot = insilico::engine::neuron_value(index, "serca_ventura_T");

 // Set lower limits on variable values
  variables[Ca_Cyt_index] = std::max<double>(variables[Ca_Cyt_index],0.0);
  variables[Ca_Er_index] = std::max<double>(variables[Ca_Er_index],0.0);
  
  variables[E0_index] = std::max<double>(variables[E0_index],0.0);
  variables[E1_index] = std::max<double>(variables[E1_index],0.0);
  variables[I1_index] = std::max<double>(variables[I1_index],0.0);
  variables[I0_index] = std::max<double>(variables[I0_index],0.0);

  // Get all variable values
  double Ca_Cyt = variables[Ca_Cyt_index];
  double Ca_Er = variables[Ca_Er_index];

  double E0 = variables[E0_index];
  double E1 = variables[E1_index];
  double I1 = variables[I1_index];
  double I0 = variables[I0_index];  

  // --------------------------------------------

  dxdt[E0_index] = (-E0 * r1a * Ca_Er)  + (E1 * r1b) + (-E0 * r4b) + (I0 * r4a);
  dxdt[E1_index] = (-E1 * r2a) + (I1 * r2b) + (-E1 * r1b) + (E0 * r1a * Ca_Er);
  dxdt[I1_index] = (-I1 * r3a) + (I0 * r3b * Ca_Cyt) + (-I1 * r2b) + (E1 * r2a);
  dxdt[I0_index] = (-I0 * r4a) + (E0 * r4b) + (-I0 * r3b * Ca_Cyt) + (I1 * r3a);

  double SERCA_ventura_Ca_Cyt_dxdt = (-Ca_Cyt * r3b * I0) + (I1 * r3a);
  double SERCA_ventura_Ca_Er_dxdt = (-Ca_Er * r1a * E0) + (E1 * r1b); 
  double SERCA_ventura_J_dxdt = (E0 * r4b) + (-I0 * r4a);

  // Update values

  insilico::engine::neuron_value(index, "SERCA_ventura_Ca_Cyt_dxdt", SERCA_ventura_Ca_Cyt_dxdt);
  insilico::engine::neuron_value(index, "SERCA_ventura_Ca_Er_dxdt", SERCA_ventura_Ca_Er_dxdt);

  //insilico::engine::neuron_value(index, "SERCA_ventura_Ca_Cyt_dxdt", -SERCA_ventura_J_dxdt);
  //insilico::engine::neuron_value(index, "SERCA_ventura_Ca_Er_dxdt", g * SERCA_ventura_J_dxdt);

  insilico::engine::neuron_value(index, "J_SERCA_ventura", SERCA_ventura_J_dxdt);

};

#endif // SERCA_VENTURA_HPP_INCLUDED
