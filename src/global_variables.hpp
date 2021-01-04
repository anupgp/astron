// Time-stamp: <2016-04-11 12:17:22 anup>
// Units: All SI units - seconds, Volts, Ampere, Meters, Simenes, Farads

#ifndef GLOBAL_VARIABLES_HPP_INCLUDED
#define GLOBAL_VARIABLES_HPP_INCLUDED

#include "rk4_counter.hpp"

namespace astron 
{
  namespace globals 
  {
    // Intergration time step 
    extern const double DELTA_T;
    extern rk4_counter RK4CELL, RK4SYN;
  }
}

#endif
