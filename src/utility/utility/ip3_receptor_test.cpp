/* Last Revised Date: 22_MAY_2015 */
/* Lastest status: not checked   */

// Package include header files

#include "insilico-0.25/include/insilico/core.hpp"
#include <boost/numeric/odeint.hpp>

// Global custom header files

#include "insilico-test/Global_variable_declarations.hpp"

// Main header files for Neurons & Astrocyte

#include "insilico-test/ip3_receptor_test/ip3_receptor_test_neuron.hpp"

// C++ Header files

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

namespace gvars=astron::globals;

int main(int argc, char **argv) {

  newinsilico::initialize(argc, argv);


  newinsilico::observe("ca_cyt");
  newinsilico::observe("ca_er");
  newinsilico::observe("ip3_cyt");
  //newinsilico::observe("ip3r_yk_s110");
  //newinsilico::observe("ip3r_yk_flux");
  newinsilico::generate_neuron<ip3_receptor_test_neuron>(1);

  state_type variables = newinsilico::get_variables();
  integrate_const(boost::numeric::odeint::runge_kutta4<state_type>(),
                  newinsilico::driver(), variables,
                  0.0, 100.0, gvars::DELTA_T, newinsilico::observer());

  newinsilico::finalize();
}
