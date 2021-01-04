/* Last Revised Date: 08_APRIL_2015 */
// UNITS: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads

#ifndef NeuronPost_HPP_INCLUDED
#define NeuronPost_HPP_INCLUDED


#include <vector>
#include <iostream>
#include <cmath>

#include "insilico-0.25/include/insilico/core.hpp"

#include "insilico/include/data_types.hpp"
#include "insilico/include/physical_constants.hpp"
#include "insilico/include/astron_global_variables.hpp"

// Header files for NeuronPre

#include "insilico/include/I_Na_Pre.hpp"
#include "insilico/include/I_K_Pre.hpp"
#include "insilico/include/I_Leak_Pre.hpp"
#include "insilico/include/ampa_receptor.hpp"

namespace consts=astron::phy_const;
namespace gvars=astron::global_vars;

class NeuronPost: public insilico::Neuron 
{
private:

  static double I_inj;
  static double t1_inj;
  static double t2_inj;

public:
  void ode_set(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

double NeuronPost::I_inj = 0.0;
double NeuronPost::t1_inj = 0.0;
double NeuronPost::t2_inj = 0.0;

void NeuronPost::ode_set(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{
  // std::cout <<"NeuronPost Index = " << index << std::endl;
  
  // Updates the RK4 counter function for cell
  gvars::rk4cell.rk4_count_update(index,t); 

  // Get dxdt values from other classes
  I_Na_Pre::current(variables, dxdt, t, index);
  I_K_Pre::current(variables, dxdt, t, index);
  I_Leak_Pre::current(variables, dxdt, t, index);
  ampa_receptor::current(variables, dxdt, t, index);

  // Get parameter values
  const double area_cyt = insilico::engine::neuron_value(index, "area_cyt"); 
  const double volume_cyt = insilico::engine::neuron_value(index, "volume_cyt"); 
  const double spec_cap_cyt = insilico::engine::neuron_value(index, "spec_cap_cyt"); 
  const double I_Ext = insilico::engine::neuron_value(index, "I_Ext");

  // Get variable indices
  unsigned V_index = insilico::engine::neuron_index(index, "V");

  // Get intermediate dxdt values
  double I_Na_Pre = insilico::engine::neuron_value(index, "I_Na_Pre");
  double I_K_Pre = insilico::engine::neuron_value(index, "I_K_Pre");
  double I_Leak_Pre = insilico::engine::neuron_value(index, "I_Leak_Pre");
  double I_ampar = insilico::engine::neuron_value(index, "I_ampar");

// Adding external current through injector
  std::vector<double> I_ext = insilico::injector::external_current(index, t);

  double current = 0;
  if(!I_ext.empty()) {
    t2_inj = I_ext[0];
    I_inj = I_ext[1];
  }
  if (1){
    if (t>t2_inj){
      I_inj = 0.0;
    }
  }

  double I_Inj = I_Ext; // (I_Ext + (gvars::NORM_RAND * 1.5E-02)) * prev_time; 
  
  // Compute dxdt in this class

  dxdt[V_index] =  0.0
    + (area_cyt * I_Na_Pre)
    + (area_cyt * I_K_Pre) 
    + (area_cyt * I_Leak_Pre)
    + (area_cyt * I_inj * 0.0) 
    + -I_ampar    
    ;
  dxdt[V_index] = dxdt[V_index] * (1/(area_cyt * spec_cap_cyt));

};

#endif // NeuronPost_HPP_INCLUDED
