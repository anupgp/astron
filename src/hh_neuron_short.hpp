#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include "insilico/core.hpp"
typedef std::vector<double> state_type;

#include "na_pre.hpp"
#include "k_pre.hpp"
#include "leak_pre.hpp"

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
