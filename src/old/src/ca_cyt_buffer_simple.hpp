// Time-stamp: <2016-12-16 13:56:20 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Description: A simple generic cytosolic calcium buffer

#ifndef CA_CYT_BUFFER_SIMPLE_HPP_INCLUDED
#define CA_CYT_BUFFER_SIMPLE_HPP_INCLUDED

class ca_cyt_buffer_simple
{
public:
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

#endif
