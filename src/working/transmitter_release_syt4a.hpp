// Time-stamp: <2017-09-22 15:07:59 anup>
// Units: All SI units - seconds, Volts, Ampere, Meters, Simenes, Farads

#ifndef TRANSMITTER_RELEASE_SYT4A_HPP_INCLUDED	
#define TRANSMITTER_RELEASE_SYT4A_HPP_INCLUDED

#include "data_types.hpp"
#include "random_number_generator.hpp"

namespace ar = astron::random;
namespace transmitter_release_syt4a {

  void state_machine(state_type &variables, state_type &dxdt, const double t, unsigned index, 
		     stringmap varnames,
		     stringmap parnames,
		     stringmap valnames); 

  void poisson_release(state_type &variables, const double t, unsigned index, 
		      ar::random_class &rnum1, ar::random_class &rnum2, ar::random_class &rnum3,
		      stringmap varnames,
		      stringmap parnames,
		      stringmap valnames);
}

#endif
