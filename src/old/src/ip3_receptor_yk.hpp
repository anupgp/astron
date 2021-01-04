// Time-stamp: <2016-09-16 13:31:28 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Ref: De Young & Keizer PNAS(1992)
// Note: Number of IP3 receptors = 1. Number of IP3 receptors are taken into account by the maximum flux parameter.
// Note: Change in ip3_cyt concentration due to binding with IP3 receptor is not considered.

#ifndef IP3_RECEPTOR_YK_HPP_INCLUDED
#define IP3_RECEPTOR_YK_HPP_INCLUDED

#include "data_types.hpp"

class ip3_receptor_yk
{
public:
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

#endif
