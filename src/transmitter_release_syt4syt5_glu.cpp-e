// Time-stamp: <2017-10-18 13:56:37 anup>

#include "transmitter_release_syt4syt5_glu.hpp"
#include "transmitter_release_syt4syt5.hpp"

#include "random_number_generator.hpp"

namespace ar = astron::random;

void transmitter_release_syt4syt5_glu::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{
  transmitter_release_syt4syt5::state_machine(variables, dxdt, t, index, varnames, parnames, valnames);
  transmitter_release_syt4syt5::poisson_release(variables, t, index, rand1, rand2, rand3, varnames, parnames, valnames);
}
