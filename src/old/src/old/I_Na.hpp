/* Last Revised Date: 08_APRIL_2015 */
/* Lastest status: not checked   */
#ifndef I_Na_HPP_INCLUDED
#define I_Na_HPP_INCLUDED

#include <vector>
#include <iostream>
#include <cmath>

#include "data_types.hpp"
#include "insilico-0.25/include/insilico/core.hpp"

//UNITS: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads

class I_Na
{
public:
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

void I_Na::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{
  const double E_Na = 50.0E-03;   // Reversal potential for Sodium currents in Volts
  const double G_Na = 130E01;   // Maximum conductance for Sodium channels S/m^2
  
  int V_index = insilico::engine::neuron_index(index, "V");
  int m_index = insilico::engine::neuron_index(index, "m");
  int h_index = insilico::engine::neuron_index(index, "h");
    
  double V = variables[V_index];
  double m = variables[m_index];
  double h = variables[h_index];

  //---Equations for bouton Na Channel (Ref: Dominique Engel & Peter Jonas, 2005, Neuron) 
  double alpha_m = (- 0.1E03 * ( (V + 45.33E-03) / (exp( -(V + 45.33E-03) / 10E-03 ) - 1 ) ));
  double beta_m = ( 4 * ( exp( - (V + 70.33E-03) / 18E-03 )) );
  double alpha_h = ( 0.07 * exp( -(V + 70.33E-03) /20E-03 ));
  double beta_h = ( 1 / ( exp( - (V + 40.33E-03) / 10E-03) + 1) );

  dxdt[m_index] = 1E03 * ( (alpha_m * (1-m)) - (beta_m * m) );
  dxdt[h_index] = 1E03 * ( (alpha_h * (1-h)) - (beta_h * h) );

  insilico::engine::neuron_value(index, "I_Na", (-G_Na * pow(m, 3) * h * (V - E_Na)));
}
#endif // I_Na_HPP_INCLUDED
