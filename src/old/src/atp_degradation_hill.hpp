// Time-stamp: <2016-03-15 12:29:33 anup>
// Units: All SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Description: This class updates the atp_ext_deg_dxdt synapse variable: rate of chnage of atp_ext in the extracellular space using classic Michealis-Menten enzymatic kinetics
// Reference: M. Stamatakis & N. Mantzaris JTB 2006

#ifndef ATP_DEGRADATION_HILL_HPP_INCLUDED
#define ATP_DEGRADATION_HILL_HPP_INCLUDED

class atp_degradation_hill
{
public:
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

#endif	// ATP_DEGRADATION_HILL_HPP_INCLUDED
