// Time-stamp: <2017-02-23 15:39:12 anup>

#include "astrocyte_atp_release.hpp"
#include "transmitter_release_astrocyte_hybrid.hpp"
#include "random_number_generator.hpp"

namespace ar = astron::random;

void astrocyte_atp_release::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{
  transmitter_release_astrocyte_hybrid::state_machine(variables, dxdt, t, index, varnames, parnames, valnames);
  transmitter_release_astrocyte_hybrid::update_release(variables, t, index, rand1, rand2, rand3, rand4, rand5,
					   rand6, rand7, rand8, varnames, parnames, valnames);
}
