#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include "insilico/core.hpp"
typedef std::vector<double> state_type;


// na_pre declaration
class na_pre
{
public:
  void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

// na_pre definition
void na_pre::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{

  {
  
    unsigned voltage_index = insilico::engine::neuron_index(index, "voltage");
    unsigned m_index = insilico::engine::neuron_index(index, "m");
    unsigned h_index = insilico::engine::neuron_index(index, "h");

    const double rev = insilico::engine::neuron_value(index,"na_rev");   // Reversal potential for Sodium currents in Volts
    const double gmax = insilico::engine::neuron_value(index,"na_gmax");   // Maximum conductance for Sodium channels S/m^2
  
    variables[m_index] = std::max(variables[m_index],0.0);
    variables[m_index] = std::min(variables[m_index],1.0);
    variables[h_index] = std::max(variables[h_index],0.0);
    variables[h_index] = std::min(variables[h_index],1.0);
    
    double voltage = variables[voltage_index] * 1e03;
    double m = variables[m_index];
    double h = variables[h_index];

    double a_am = 93.8285e03;
    double b_am = -105.023;
    double c_am = 17.7094;
    double alpha_m = -a_am * (voltage + b_am) / (exp( -(voltage + b_am) / c_am) - 1 );

    double a_bm = 0.168396e03;
    double c_bm = 23.2707;
    double beta_m = a_bm  * exp( -voltage / c_bm);

    double a_ah = 0.000354e03;
    double c_ah = 18.706;
    double alpha_h = a_ah * exp( -voltage / c_ah);

    double a_bh = 6.62694e03;
    double b_bh = 17.6769;
    double c_bh = 13.3097;
    double beta_h = ( a_bh / ( exp( - (voltage + b_bh) / c_bh) + 1) );

    dxdt[m_index] =  ( (alpha_m * (1-m)) - (beta_m * m));
    dxdt[h_index] =  ( (alpha_h * (1-h)) - (beta_h * h));
  
    double i_na =  gmax * std::pow(m, 3) * h * ((voltage *1e-3) - rev);

    insilico::engine::neuron_value(index, "na_current",i_na);
  }
};

// k_pre declaration
class k_pre
{
public:
  void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

// k_pre definition
void k_pre::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{
  double rev = insilico::engine::neuron_value(index,"k_rev"); // Reversal potential for Potassium currents in Volts
  double gmax = insilico::engine::neuron_value(index,"k_gmax"); // Maximum conductance for Potassium channels S/m^2

  unsigned voltage_index = insilico::engine::neuron_index(index, "voltage");
  unsigned n_index = insilico::engine::neuron_index(index, "n");
  
  variables[n_index] = std::max(variables[n_index],0.0);
  variables[n_index] = std::min(variables[n_index],1.0);
  
  double voltage = variables[voltage_index] * 1e03;
  double n = variables[n_index];

  double alpha_n = ( -0.01e03 * (voltage + 55) / ( exp( -(voltage +  55) / 10) - 1.0 ) );
  double beta_n =  (0.125e03 * exp (- (voltage + 65) / 80) );
    
  dxdt[n_index] =  ( (alpha_n * (1-n)) - (beta_n * n) );
  double i_k = gmax * std::pow(n, 4) * ((voltage*1e-3) - rev);

  insilico::engine::neuron_value(index, "k_current", i_k);
};

// leak_pre declaration
class leak_pre
{
public:
  void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

// leak_pre definition
void leak_pre::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{

  {
    double rev = insilico::engine::neuron_value(index,"leak_rev"); // Reversal potential for Potassium currents in Volts
    double gmax = insilico::engine::neuron_value(index,"leak_gmax"); // Maximum conductance for Potassium channels S/m^2

    int voltage_index = insilico::engine::neuron_index(index, "voltage");

    double voltage = variables[voltage_index];
  
    double i_leak = gmax * (voltage -rev);

    insilico::engine::neuron_value(index, "leak_current", i_leak);
  }

};

// hh_pre declaration
class hh_neuron: public insilico::Neuron
{
private:
  na_pre na;
  k_pre k;
  leak_pre leak;
public:
  void ode_set(std::vector<double> &variables, std::vector<double> &dxdt, const double t, unsigned index);
};

// hh_pre definition
void hh_neuron::ode_set(std::vector<double> &variables, std::vector<double> &dxdt, const double t, unsigned index)
{
  const double area_cyt = insilico::engine::neuron_value(index, "area_cyt");
  const double spec_cap_cyt = insilico::engine::neuron_value(index, "spec_cap_cyt"); 

  // Intermidiate dxdt values: currents
  na.current(variables,dxdt, t, index);
  k.current(variables, dxdt, t, index);
  leak.current(variables, dxdt, t, index);

  double na_pre_current = insilico::engine::neuron_value(index, "na_current");
  double k_pre_current = insilico::engine::neuron_value(index, "k_current");
  double leak_pre_current = insilico::engine::neuron_value(index, "leak_current");
  // Get variable indices
  unsigned voltage_index = insilico::engine::neuron_index(index, "voltage");

  // Adding external current through external current function (injector)
  std::vector<double> external_currents = insilico::injector::external_current(index, t);
  double ext_current = 0.0;
  if(!external_currents.empty()){
    ext_current = external_currents[index];
  }    

  insilico::engine::neuron_value(index, "external_current",ext_current);

  dxdt[voltage_index] =  0.0
    + ((- area_cyt * na_pre_current) * (1.0/(area_cyt * spec_cap_cyt)))
    + ((- area_cyt * k_pre_current) * (1.0/(area_cyt * spec_cap_cyt))) 
    + ((- area_cyt * leak_pre_current) * (1.0/(area_cyt * spec_cap_cyt)))
    + ((area_cyt * ext_current * 1.0) * (1.0/(area_cyt * spec_cap_cyt)))
    ;
}
