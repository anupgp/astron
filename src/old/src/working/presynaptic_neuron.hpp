// Time-stamp: <2017-03-02 11:28:11 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads

#ifndef PRESYNAPTIC_NEURON_HPP_INCLUDED
#define PRESYNAPTIC_NEURON_HPP_INCLUDED

#include "data_types.hpp"
#include "insilico/core.hpp"
#include "insilico/core/type.hpp"
#include <ctime>
#include <sys/types.h>
#include <chrono>

#include "na_pre.hpp"
#include "k_pre.hpp"
#include "leak_pre.hpp"

#include "transmitter_release_syt1syt7_glu.hpp"

class presynaptic_neuron: public insilico::Neuron
{
private:
  na_pre napre;
  k_pre kpre;
  leak_pre leakpre;
  transmitter_release_syt1syt7_glu glurel;
public:
  void ode_set(state_type &variables, state_type &dxdt, const double t, unsigned index);
  inline explicit presynaptic_neuron(void):
    glurel(getpid()*std::chrono::system_clock::now().time_since_epoch().count())
  {};
  // inline explicit presynaptic_neuron(void){};
};

#endif
