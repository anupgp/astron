// Time-stamp: <2019-01-06 15:29:00 macbookair>
// UNITS: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads

#ifndef ASTROCYTE_HPP_INCLUDED
#define ASTROCYTE_HPP_INCLUDED


#include <ctime>
#include <sys/types.h>
#include <chrono>

#include "include/new_insilico.hpp"

#include "data_types.hpp"
#include "na_pre.hpp"
#include "k_pre.hpp"
#include "leak_pre.hpp"

#include "transmitter_release_syt4syt5_glu.hpp"
// #include "transmitter_release_syt4_glu.hpp"
// #include "transmitter_release_hybrid_glu.hpp"

#include "ip3_receptor_lr.hpp"
// #include "ryr_receptor_xw.hpp"

class astrocyte: public newinsilico::Neuron 
{
private:
  na_pre napre;
  k_pre kpre;
  leak_pre leakpre;
  transmitter_release_syt4syt5_glu glurel;
  // transmitter_release_syt1syt7_glu glurel;
  // transmitter_release_hybrid_glu glurel;
  ip3_receptor_lr ip3rlr;
  // ryr_receptor_xw ryrxw;

public:
  void ode_set(state_type &variables, state_type &dxdt, state_type &noise,  const double t, unsigned index);
  // void ode_set(state_type &variables, state_type &dxdt, const double t, unsigned index);
  // inline explicit astrocyte(void){}
  astrocyte();
};

#endif
