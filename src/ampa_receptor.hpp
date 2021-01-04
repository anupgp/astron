// Time-stamp: <2016-03-15 10:48:14 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Description: Generates AMPA receptor currents for a given glutamate concentration
// Note: The binding and unbinding of glutamate at the receptor will change local glutamate concentration. Currently this is not taken into account.  
// Ref: Peter Jonas & Sakmann 1993

#ifndef AMPA_RECEPTOR_HPP_INCLUDED
#define AMPA_RECEPTOR_HPP_INCLUDED

class ampa_receptor
{
public:
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

#endif // AMPA_RECEPTOR_HPP_INCLUDED
