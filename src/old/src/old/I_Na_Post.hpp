/* Last Revised Date: 05_APRIL_2015 */
// UNITS: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads

//  Na+ channels implimented from classical HH (1952)

#ifndef I_Na_Post_HPP_INCLUDED
#define I_Na_Post_HPP_INCLUDED

#include <vector>
#include <iostream>
#include <cmath>

#include "data_types.hpp"
#include "insilico-0.25/include/insilico/core.hpp"


class I_Na_Post
{
public:
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

void I_Na_Post::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{
  const double E_Na = insilico::engine::neuron_value(index,"E_Na_Post");   // Reversal potential for Sodium currents in Volts
  const double G_Na = insilico::engine::neuron_value(index,"G_Na_Post");   // Maximum conductance for Sodium channels S/m^2
  
  unsigned V_index = insilico::engine::neuron_index(index, "V");
  unsigned m_index = insilico::engine::neuron_index(index, "m");
  unsigned h_index = insilico::engine::neuron_index(index, "h");
  
  variables[m_index] = std::max(variables[m_index],0.0);
  variables[m_index] = std::min(variables[m_index],1.0);
  variables[h_index] = std::max(variables[h_index],0.0);
  variables[h_index] = std::min(variables[h_index],1.0);
    
  double V = variables[V_index];
  double m = variables[m_index];
  double h = variables[h_index];



  double alpha_m = std::max((- 0.1E03 * ( (V + 45E-03) / (exp( -(V + 45E-03) / 10E-03 ) - 1 ) )),0.0);
  double beta_m = std::max(( 4 * ( exp( - (V + 70.33E-03) / 18E-03 )) ),0.0);
  double alpha_h = std::max(( 0.07 * exp( -(V + 70.33E-03) / 20E-03 )),0.0);
  double beta_h = std::max((1 / ( exp( - (V + 40.33E-03) / 10E-03) + 1) ),0.0);

  dxdt[m_index] = 1E03 * ( (alpha_m * (1-m)) - (beta_m * m) );
  dxdt[h_index] = 1E03 * ( (alpha_h * (1-h)) - (beta_h * h) );

  insilico::engine::neuron_value(index, "I_Na_Post", (-G_Na * pow(m, 3) * h * (V - E_Na)));
}
#endif // I_Na_Post_HPP_INCLUDED
