// Time-stamp: <2017-03-17 17:58:00 anup>

#include "transmitter_release_hybrid_glu.hpp"
#include "transmitter_release_hybrid.hpp"

#include "random_number_generator.hpp"
#include "data_types.hpp"

namespace ar = astron::random;

void transmitter_release_hybrid_glu::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{
  transmitter_release_hybrid::state_machine(variables, dxdt, t, index, varnames, parnames, valnames);
  transmitter_release_hybrid::update_release(variables, t, index, rand1, rand2, rand3, rand4,
					     varnames, parnames, valnames);
}
