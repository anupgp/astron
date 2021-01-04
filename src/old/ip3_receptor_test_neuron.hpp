
/* Last Revised Date: 22_MAY_2015 */

//UNITS: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads

#ifndef IP3_RECEPTOR_TEST_NEURON_HPP_INCLUDED
#define IP3_RECEPTOR_TEST_NEURON_HPP_INCLUDED

#include "insilico-test/data_types.hpp"
#include "insilico-test/physical_constants.hpp"
#include "insilico-test/astron_global_variables.hpp"
#include "insilico-0.25/include/insilico/core.hpp"

#include <vector>
#include <iostream>
#include <cmath>

// Header files for NeuronPre

#include "insilico-test/pmca.hpp"
#include "insilico-test/calbindin.hpp"
#include "insilico-test/serca_hill.hpp"
#include "insilico-test/er_leak.hpp"
#include "insilico-test/ryanodine_receptor.hpp"
#include "insilico-test/ip3_receptor_yk.hpp"

namespace consts=astron::phy_const;
namespace gvars=astron::global_vars;

class ip3_receptor_test_neuron: public insilico::Neuron 
{
public:
  void ode_set(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

void ip3_receptor_test_neuron::ode_set(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{
  // Get dxdt values from other classes

  pmca::current(variables, dxdt, t, index);
  calbindin::current(variables, dxdt, t, index);
  serca_hill::current(variables, dxdt, t, index);
  er_leak::current(variables, dxdt, t, index);
  ryanodine_receptor::current(variables, dxdt, t, index);
  //ip3_receptor_uj::current(variables, dxdt, t, index);
  ip3_receptor_yk::current(variables, dxdt, t, index);

  // Get parameter values


  // Get variable indices

  unsigned ca_cyt_index = insilico::engine::neuron_index(index, "ca_cyt");
  unsigned ip3_cyt_index = insilico::engine::neuron_index(index, "ip3_cyt");
  unsigned ca_er_index = insilico::engine::neuron_index(index, "ca_er");
  
  // Get intermediate dxdt: ca_cyt
  double pmca_ca_cyt_dxdt = insilico::engine::neuron_value(index, "pmca_ca_cyt_dxdt");
  double calbindin_ca_cyt_dxdt = insilico::engine::neuron_value(index, "calbindin_ca_cyt_dxdt");
  double serca_hill_ca_cyt_dxdt = insilico::engine::neuron_value(index, "serca_hill_ca_cyt_dxdt");
  double er_leak_ca_cyt_dxdt = insilico::engine::neuron_value(index, "er_leak_ca_cyt_dxdt");
  double ryr_ca_cyt_dxdt = insilico::engine::neuron_value(index, "ryr_ca_cyt_dxdt");
  double ip3r_yk_ca_cyt_dxdt = insilico::engine::neuron_value(index, "ip3r_yk_ca_cyt_dxdt");
  
  // Get intermediate dxdt: ca_er
  double serca_hill_ca_er_dxdt = insilico::engine::neuron_value(index, "serca_hill_ca_er_dxdt");
  double er_leak_ca_er_dxdt = insilico::engine::neuron_value(index, "er_leak_ca_er_dxdt");
  double ip3r_yk_ca_er_dxdt = insilico::engine::neuron_value(index, "ip3r_yk_ca_er_dxdt");
  double ryr_ca_er_dxdt = insilico::engine::neuron_value(index, "ryr_ca_er_dxdt");

  // Get intermediate dxdt: ip3_cyt
  double ip3r_yk_ip3_cyt_dxdt = insilico::engine::neuron_value(index, "ip3r_yk_ip3_cyt_dxdt");

  // Adding external current through injector
  //vector<double> I_Ext = injector::external_current(index, t);

  //double current = 0;
  //if(!I_Ext.empty()) {
  //  current = I_Ext[0];
  //} 
  
  variables[ca_cyt_index] = std::max<double>(variables[ca_cyt_index],0.0);
  variables[ca_er_index] = std::max<double>(variables[ca_er_index],0.0);

  dxdt[ca_cyt_index] = 0.0 
    //+ pmca_ca_cyt_dxdt 
    + calbindin_ca_cyt_dxdt 
    //+ SERCA_higgins_Ca_Cyt_dxdt
    //+ SERCA_ventura_Ca_Cyt_dxdt
    //+ SERCA_Ca_Cyt_dxdt
    + serca_hill_ca_cyt_dxdt
    + er_leak_ca_cyt_dxdt
    //+ gluves_Ca_Cyt_dxdt
    //+ atpves_Ca_Cyt_dxdt
    //+ I_Ca_vgcc_pre_Ca_Cyt_dxdt 
    + ryr_ca_cyt_dxdt 
    + ip3r_yk_ca_cyt_dxdt
    //+ P2X2_receptor_Ca_Cyt_dxdt
    ;

  dxdt[ca_er_index] = 0.0 
    //+ SERCA_higgins_Ca_Er_dxdt
    //+ SERCA_ventura_Ca_Er_dxdt
    + serca_hill_ca_er_dxdt
    + er_leak_ca_er_dxdt
    + ryr_ca_er_dxdt 
    + ip3r_yk_ca_er_dxdt
    ;
  //variables[ca_er_index] = (2.0E-06 - variables[ca_cyt_index])/0.185; 
 
  dxdt[ip3_cyt_index] = 0; 
    //+ ip3r_yk_ip3_cyt_dxdt
    //+ IP3_Cyt_deg_simple_IP3_Cyt_dxdt 
    //+ mGluR_simple_IP3_Cyt_dxdt
    //+ P2YR_simple_IP3_Cyt_dxdt
    ;

};

#endif // NeuronPre_HPP_INCLUDED
