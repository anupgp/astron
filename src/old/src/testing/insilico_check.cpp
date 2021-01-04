// Time-stamp: <2016-04-06 15:01:20 anup>

// C++ Header files
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

// Global header files
#include "insilico/core.hpp"
#include "boost/numeric/odeint.hpp"

#include "hh_neuron_short.hpp"

typedef std::vector<double> state_type;

int main(int argc, char **argv) {

  newinsilico::initialize(argc, argv);
  newinsilico::observe("voltage");
  newinsilico::observe("m");
  newinsilico::observe("h");
  newinsilico::observe("n");
  newinsilico::observe("na_current");
  newinsilico::observe("k_current");
  newinsilico::observe("leak_current");
  newinsilico::observe("external_current");

  newinsilico::generate_neuron<hh_neuron>();  

  state_type variables = newinsilico::get_variables();
  for (auto el:variables)
    std::cout << el << " ";
  integrate_const(boost::numeric::odeint::runge_kutta4<state_type>(),
                  newinsilico::driver(), variables,
                  0.0, 1.0, 50.0e-06, newinsilico::observer());
  newinsilico::finalize();
}
