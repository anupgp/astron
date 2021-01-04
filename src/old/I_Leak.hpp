/* Last Revised Date: 08_APRIL_2015 */
/* Lastest status: unchecked    */
#ifndef I_Leak_HPP_INCLUDED
#define I_Leak_HPP_INCLUDED

#include <vector>
#include <iostream>
#include <cmath>

#include "insilico-0.25/include/insilico/core.hpp"
#include "data_types.hpp"

//UNITS: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads

class I_Leak
{

public:

  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);  
};
void I_Leak::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{

  const double E_Leak = insilico::engine::neuron_value(index, "E_Leak"); // Reversal potential for Leak currents in Volts
  const double G_Leak = insilico::engine::neuron_value(index, "G_Leak");  // Maximum conductance for Leak channels S/m^2

  int V_index = insilico::engine::neuron_index(index, "V");
    
  double V = variables[V_index];
    
  insilico::engine::neuron_value(index, "I_Leak", (-G_Leak * (V - E_Leak)));
};

#endif // I_Leak_HPP_INCLUDED
