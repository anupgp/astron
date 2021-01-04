// Time-stamp: <2018-01-24 18:43:15 anup>

#include "global_variables.hpp"
#include "rk4_counter.hpp"

const double astron::globals::DELTA_T = 50e-6; /* 200e-6, 50e-6, 300e-6, 100e-6 */
rk4_counter astron::globals::RK4CELL(0.0);
rk4_counter astron::globals::RK4SYN(0.0);

