// Time-stamp: <2017-06-07 17:46:05 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Description: This is script models calcium signaling in an astrocytic processes

#ifndef ASTROCYTE_PROCESS_HPP_INCLUDED
#define ASTROCYTE_PROCESS_HPP_INCLUDED

#include "data_types.hpp"
#include "insilico/core.hpp"
#include "insilico/core/type.hpp"
#include <ctime>
#include <sys/types.h>
#include <chrono>

// #include "transmitter_release_syt1syt7_glu.hpp"
// #include "transmitter_release_syt7_glu.hpp"
// #include "transmitter_release_hybrid_glu.hpp"

#include "ip3_receptor_lr.hpp"
// #include "ryr_receptor_xw.hpp"

class astrocyte_process: public insilico::Neuron 
{
private:
  // transmitter_release_syt1syt7_glu glurel;
  ip3_receptor_lr ip3rlr;
  // ryr_receptor_xw ryrxw;

public:
  void ode_set(state_type &variables, state_type &dxdt, state_type &noise,  const double t, unsigned index);
  // void ode_set(state_type &variables, state_type &dxdt, const double t, unsigned index);
  // inline explicit astrocyte(void){}
  inline explicit astrocyte_process(void):
    // glurel(getpid()*std::chrono::system_clock::now().time_since_epoch().count()*6567),
    ip3rlr(getpid()*std::chrono::system_clock::now().time_since_epoch().count()*890740714)
    // ryrxw(getpid()*std::chrono::system_clock::now().time_since_epoch().count()*564319)  
  {};
};

#endif
