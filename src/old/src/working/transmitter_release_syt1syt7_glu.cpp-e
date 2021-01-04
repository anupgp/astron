// Time-stamp: <2017-03-15 15:18:52 anup>

#include "transmitter_release_syt1syt7_glu.hpp"
#include "transmitter_release_syt1syt7.hpp"

#include "random_number_generator.hpp"

namespace ar = astron::random;

void transmitter_release_syt1syt7_glu::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{
  transmitter_release_syt1syt7::state_machine(variables, dxdt, t, index, varnames, parnames, valnames);
  transmitter_release_syt1syt7::update_release(variables, t, index, rand1, rand2, rand3, rand4, varnames, parnames, valnames);
}
