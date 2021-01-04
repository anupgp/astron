// Time-stamp: <2017-09-01 11:01:27 anup>

#include "transmitter_release_syt4_glu.hpp"
#include "transmitter_release_syt4.hpp"

#include "random_number_generator.hpp"

namespace ar = astron::random;

void transmitter_release_syt4_glu::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{
  transmitter_release_syt4::state_machine(variables, dxdt, t, index, varnames, parnames, valnames);
  transmitter_release_syt4::poisson_release(variables, t, index, rand1, rand2, rand3, varnames, parnames, valnames);
}
