/* Last Revised Date: 08_APRIL_2015 */
/* Lastest status: not checked   */

//UNITS: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads

#ifndef SERCA_HPP_INCLUDED
#define SERCA_HPP_INCLUDED

#include <vector>
#include <iostream>
#include <cmath>

#include "data_types.hpp"
#include "physical_constants.hpp"
#include "astron_global_variables.hpp"
#include "insilico-0.25/include/insilico/core.hpp"
#include "utility_functions.hpp"

namespace consts=astron::phy_const;
namespace gvars=astron::global_vars;

class SERCA
{
public:
  // Static functions
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

void SERCA::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{

  // Get all variable indices
  unsigned Ca_Cyt_index = insilico::engine::neuron_index(index, "Ca_Cyt");
  unsigned Ca_Er_index = insilico::engine::neuron_index(index, "Ca_Er");
  
  unsigned E1_index = insilico::engine::neuron_index(index, "serca_E1");
  unsigned E1C1_index = insilico::engine::neuron_index(index, "serca_E1C1");
  unsigned E1C2_index = insilico::engine::neuron_index(index, "serca_E1C2");
  unsigned E2C2_index = insilico::engine::neuron_index(index, "serca_E2C2");
  unsigned E2C1_index = insilico::engine::neuron_index(index, "serca_E2C1");  
  unsigned E2_index = insilico::engine::neuron_index(index, "serca_E2");

  // Get all parameter values
  const double k1a = insilico::engine::neuron_value(index, "serca_k1a");
  const double k1b = insilico::engine::neuron_value(index, "serca_k1b");
  const double k2a = insilico::engine::neuron_value(index, "serca_k2a");
  const double k2b = insilico::engine::neuron_value(index, "serca_k2b");
 
  const double k3a = insilico::engine::neuron_value(index, "serca_k3a");
  const double k3b = insilico::engine::neuron_value(index, "serca_k3b");
  const double k4a = insilico::engine::neuron_value(index, "serca_k4a");
  const double k4b = insilico::engine::neuron_value(index, "serca_k4b");

  const double k5a = insilico::engine::neuron_value(index, "serca_k5a");
  const double k5b = insilico::engine::neuron_value(index, "serca_k5b");
  const double k6a = insilico::engine::neuron_value(index, "serca_k6a");
  const double k6b = insilico::engine::neuron_value(index, "serca_k6b");

 const double Ca_Er_baseline = insilico::engine::neuron_value(index, "serca_Ca_Er_baseline");

 // Set lower limits on variable values
  variables[Ca_Cyt_index] = std::max<double>(variables[Ca_Cyt_index],0.0);
  variables[Ca_Er_index] = std::max<double>(variables[Ca_Er_index],0.0);
  
  variables[E1_index] = std::max<double>(variables[E1_index],0.0);
  variables[E1C1_index] = std::max<double>(variables[E1C1_index],0.0);
  variables[E1C2_index] = std::max<double>(variables[E1C2_index],0.0);
  variables[E2C2_index] = std::max<double>(variables[E2C2_index],0.0);
  variables[E2C1_index] = std::max<double>(variables[E2C1_index],0.0);
  variables[E2_index] = std::max<double>(variables[E2_index],0.0);

  // Get all variable values
  double Ca_Cyt = variables[Ca_Cyt_index];
  double Ca_Er = variables[Ca_Er_index];

  double E1 = variables[E1_index];
  double E1C1 = variables[E1C1_index];
  double E1C2 = variables[E1C2_index];
  double E2C2 = variables[E2C2_index];  
  double E2C1 = variables[E2C1_index];
  double E2 = variables[E2_index];

  // --------------------------------------------

  dxdt[E1_index] = (-E1 * k1a * Ca_Cyt) + (E1C1 * k1b) + (-E1 * k6b) + (E2 * k6a);
  dxdt[E1C1_index] = (-E1C1 * k2a * Ca_Cyt) + (E1C2 * k2b) + (-E1C1 * k1b) + (E1 * Ca_Cyt * k1a);
  dxdt[E1C2_index] = (-E1C2 * k3a) + (E2C2 * k3b) + (-E1C2 * k2b) + (E1C1 * Ca_Cyt * k2a);
  dxdt[E2C2_index] = (-E2C2 * k4a) + (E2C1 * Ca_Er * k4b) + (-E2C2 * k3b) + (E1C2 * k3a);
  dxdt[E2C1_index] = (-E2C1 * k5a) + (E2 * Ca_Er * k5b) + (-E2C1 * Ca_Er * k4b) + (E2C2 * k4a);
  dxdt[E2_index] = (-E2 * k6a) + (E1 * k6b ) + (-E2 * Ca_Er * k5b) + (E2C1 * k5a);

  //double SERCA_Ca_Cyt_dxdt = (-E1 * k1a * Ca_Cyt) + (E1C1 * k1b) + (-E1C1 * k2a * Ca_Cyt) + (E1C2 * k2b) ;
  //double SERCA_Ca_Er_dxdt = (E2C2 * k4a) + (-E2C1 * Ca_Er * k4b) + (E2C1 * k5a) + (-E2 * Ca_Er * k5b);
  double SERCA_Ca_Er_dxdt  = 5.4 * (Ca_Cyt - (1E-4*Ca_Er)) / (0.007 + (0.06E06*Ca_Cyt) + (0.0014E06*Ca_Er) + (0.007E12*Ca_Cyt*Ca_Er));
  double SERCA_Ca_Cyt_dxdt = 0.0;
  // Update parameter values
  
  insilico::engine::neuron_value(index, "SERCA_Ca_Cyt_dxdt", SERCA_Ca_Cyt_dxdt);
  insilico::engine::neuron_value(index, "SERCA_Ca_Er_dxdt", SERCA_Ca_Er_dxdt);
  insilico::engine::neuron_value(index, "J_SERCA_Ca_Er", SERCA_Ca_Er_dxdt);
};

#endif // SERCA_HPP_INCLUDED
