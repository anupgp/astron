// Time-stamp: <2017-01-21 13:43:21 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Description: A simple generic ER calcium buffer
// Ref: higgins2006

#ifndef CA_ER_BUFFER_SIMPLE_HPP_INCLUDED
#define CA_ER_BUFFER_SIMPLE_HPP_INCLUDED

class ca_er_buffer_simple
{
public:
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

#endif
