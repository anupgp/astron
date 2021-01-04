/* Last Revised Date: 08_APRIL_2015 */
// UNITS: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads

#ifndef I_K_HPP_INCLUDED
#define I_K_HPP_INCLUDED

#include <vector>
#include <iostream>
#include <cmath>

#include "insilico/include/data_types.hpp"

#include "insilico-0.25/include/insilico/core.hpp"

class I_K
{

public:
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};
void I_K::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{
  double E_K = -85.0E-03; // Reversal potential for Potassium currents in Volts
  double G_K = 36E01; // Maximum conductance for Potassium channels S/m^2

  int V_index = insilico::engine::neuron_index(index, "V");
  int n_index = insilico::engine::neuron_index(index, "n");

  double V = variables[V_index];
  double n = variables[n_index];

  //---Equations for bouton K Channel (Ref: Dominique Engel & Peter Jonas, 2005, Neuron)  
  double alpha_n = (-0.01E03 * (V + 60.33E-03) / ( exp( -(V +  60.33E-03) / 10E-03) - 1 ) );
  double beta_n = (0.125 * exp (- (V + 70.33E-03) / 80E-03) );
    
  dxdt[n_index] = 1E03 * ( (alpha_n * (1-n)) - (beta_n * n) );

  insilico::engine::neuron_value(index, "I_K", (-G_K * pow(n, 4) * (V - E_K)));
};

#endif // I_K_HPP_INCLUDED
