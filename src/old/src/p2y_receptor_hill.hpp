// Time-stamp: <2016-03-15 15:31:20 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Description: A simple phenomenological model for plc-beta activation via atp binding to p2y receptors
// Note: The change in ATP concentration at individual synapses due to p2y receptors is not taken into account
 
#ifndef P2Y_RECEPTOR_HILL_HPP_INCLUDED
#define P2Y_RECEPTOR_HILL_HPP_INCLUDED

class p2y_receptor_hill
{
public:
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

#endif
