// Time-stamp: <2017-02-23 16:02:25 anup>

#include "neuron_glutamate_release.hpp"
#include "transmitter_release_neuron.hpp"
#include "random_number_generator.hpp"

namespace ar = astron::random;

void neuron_glutamate_release::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{
  transmitter_release_neuron::state_machine(variables, dxdt, t, index, varnames, parnames, valnames);
  transmitter_release_neuron::update_release(variables, t, index, rand1, rand2, rand3, rand4, rand5, rand6, rand7, rand8, rand9, rand10, rand11, varnames, parnames, valnames);
}

