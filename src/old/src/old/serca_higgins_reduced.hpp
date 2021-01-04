/* Last Revised Date: 18_APRIL_2015 */
/* Lastest status: not checked   */

//UNITS: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads

#ifndef SERCA_HIGGINS_REDUCED_HPP_INCLUDED
#define SERCA_HIGGINS_REDUCED_HPP_INCLUDED

#include <vector>
#include <iostream>
#include <cmath>

#include "data_types.hpp"
#include "physical_constants.hpp"
#include "global_variables.hpp"

#include "insilico/core.hpp"
#include "utility_functions.hpp"

namespace consts=astron::phy_const;
namespace gvars=astron::globals;

class SERCA_higgins_reduced
{
public:
  // Static functions
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

void SERCA_higgins_reduced::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{

  // Get all variable indices
  unsigned Ca_Cyt_index = insilico::engine::neuron_index(index, "Ca_Cyt");
  unsigned Ca_Er_index = insilico::engine::neuron_index(index, "Ca_Er");
  
  unsigned X_index = insilico::engine::neuron_index(index, "serca_higgins_reduced_X");
  
  // Get all parameter values
  const double Pt = insilico::engine::neuron_value(index, "serca_higgins_reduced_Pt");
  const double K1ab = insilico::engine::neuron_value(index, "serca_higgins_reduced_K1ab");
  const double K3ab = insilico::engine::neuron_value(index, "serca_higgins_reduced_K3ab");
  const double k2a = insilico::engine::neuron_value(index, "serca_higgins_reduced_k2a");
  const double k2b = insilico::engine::neuron_value(index, "serca_higgins_reduced_k2b");
  const double k4a = insilico::engine::neuron_value(index, "serca_higgins_reduced_k4a");
  const double k4b = insilico::engine::neuron_value(index, "serca_higgins_reduced_k4b");
  const double g = insilico::engine::neuron_value(index, "serca_higgins_reduced_gamma");
  const double v = insilico::engine::neuron_value(index, "serca_higgins_reduced_v");

 // Set lower limits on variable values
  variables[Ca_Cyt_index] = std::max<double>(variables[Ca_Cyt_index],0.0);
  variables[Ca_Er_index] = std::max<double>(variables[Ca_Er_index],0.0);
  
  variables[X_index] = std::max<double>(variables[X_index],0.0);
 
  // Get all variable values
  double Ca_Cyt = variables[Ca_Cyt_index];
  double Ca_Er = variables[Ca_Er_index];

  double X = variables[X_index];
 
  // --------------------------------------------

  double A1 = (pow(K1ab,2) + pow(Ca_Cyt,2));	    // (K1ab^2 + Ca_Cyt^2)
  double A2 = pow(A1,2); // (K1ab^2 + Ca_Cyt^2)^2
  double B1 = (1 + (pow(K3ab,2)*pow(Ca_Er,2))); // (1 + K3ab^2 * Ca_Er^2)
  double B2 = pow(B1,2); // (1 + K3ab^2 * Ca_Er^2)^2

  dxdt[X_index] = (((k2b * pow(K3ab,2) * pow(Ca_Er,2)) + k4a) * (Pt - X) / B1) - (((k2a * pow(Ca_Cyt,2)) + (k4b * pow(K1ab,2))) * X / A1);

  double SERCA_higgins_reduced_Ca_Cyt_dxdt_extra = 1 + ( 4 * Ca_Cyt * pow(K1ab,2) * X / A2);  
  double SERCA_higgins_reduced_Ca_Er_dxdt_extra = 1 + ( 4 * Ca_Er * pow(K3ab,2) * g * (Pt - X) / B2);

  double SERCA_higgins_reduced_Ca_Cyt_dxdt = -(2 * pow(Ca_Cyt,2) * pow(K1ab,2) * (k2a - k4b) * X / A2) 
    - (2 * ((pow(Ca_Cyt,2) * k4a) - (k2b * pow(K3ab,2) * pow(K1ab,2) * pow(Ca_Er,2))) * (Pt - X) / (A1 * B1));
  double SERCA_higgins_reduced_Ca_Er_dxdt = -(((2 * g * pow(K3ab,2) * pow(Ca_Er,2) * pow(K1ab,2) * k4b) - (2 * g * k2a * pow(Ca_Cyt,2))) * X / (A1 * B1)) 
    + (2 * g * pow(K3ab,2) * pow(Ca_Er,2) * (k4a - k2b) * (Pt - X) / B2); 

  insilico::engine::neuron_value(index, "SERCA_higgins_reduced_Ca_Cyt_dxdt", SERCA_higgins_reduced_Ca_Cyt_dxdt);
  insilico::engine::neuron_value(index, "SERCA_higgins_reduced_Ca_Er_dxdt", SERCA_higgins_reduced_Ca_Er_dxdt);
  insilico::engine::neuron_value(index, "SERCA_higgins_reduced_Ca_Cyt_dxdt_extra", SERCA_higgins_reduced_Ca_Cyt_dxdt_extra);
  insilico::engine::neuron_value(index, "SERCA_higgins_reduced_Ca_Er_dxdt_extra", SERCA_higgins_reduced_Ca_Er_dxdt_extra);
  insilico::engine::neuron_value(index, "J_SERCA_higgins_reduced_Ca_Er", SERCA_higgins_reduced_Ca_Er_dxdt);

};

#endif // SERCA_HIGGINS_REDUCED_HPP_INCLUDED
