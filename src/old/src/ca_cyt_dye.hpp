// Time-stamp: <2017-06-07 16:01:50 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Description: A simple generic cytosolic calcium dye

#ifndef CA_CYT_DYE_HPP_INCLUDED
#define CA_CYT_DYE_HPP_INCLUDED

class ca_cyt_dye
{
public:
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

#endif
