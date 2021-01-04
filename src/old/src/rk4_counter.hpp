// Time-stamp: <2016-03-23 15:10:22 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads

// #pragma once
#ifndef RK4_COUNTER_HPP_INCLUDED
#define RK4_COUNTER_HPP_INCLUDED

#include "data_types.hpp"

class rk4_counter 
{
private:
  double prev_time;
public:
  std::vector<int> counter;
  // rk4counter constructor initialized with starting time and initialized the counter with length one and value zero
  explicit inline rk4_counter (double init_time_): prev_time(init_time_), counter(1,0) {};
  void counter_update(const unsigned int idx, const double t);
};

#endif

