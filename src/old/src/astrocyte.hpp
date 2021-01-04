// Time-stamp: <2017-10-18 15:10:27 anup>
// UNITS: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads

#ifndef ASTROCYTE_HPP_INCLUDED
#define ASTROCYTE_HPP_INCLUDED

#include "data_types.hpp"
#include "insilico/core.hpp"
#include "insilico/core/type.hpp"
#include <ctime>
#include <sys/types.h>
#include <chrono>

#include "na_pre.hpp"
#include "k_pre.hpp"
#include "leak_pre.hpp"

#include "transmitter_release_syt4syt5_glu.hpp"
// #include "transmitter_release_syt4_glu.hpp"
// #include "transmitter_release_hybrid_glu.hpp"

#include "ip3_receptor_lr.hpp"
// #include "ryr_receptor_xw.hpp"

class astrocyte: public insilico::Neuron 
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
  inline explicit astrocyte(void):
    glurel(getpid()*std::chrono::system_clock::now().time_since_epoch().count()*6567),
    ip3rlr(getpid()*std::chrono::system_clock::now().time_since_epoch().count()*890740714)
    // ryrxw(getpid()*std::chrono::system_clock::now().time_since_epoch().count()*564319)  
  {};
};

#endif
