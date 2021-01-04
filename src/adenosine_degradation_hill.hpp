// Time-stamp: <2016-02-24 10:57:43 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Description: This class updates the ado_ext_deg_dxdt synapse variable
// Reference: M. Stamatakis & N. Mantzaris JTB 2006

#ifndef ADO_DEGRADATION_HILL_HPP_INCLUDED
#define ADO_DEGRADATION_HILL_HPP_INCLUDED

class ado_degradation_hill
{
public:
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

#endif	// ADO_DEGRADATION_HILL_HPP_INCLUDED
