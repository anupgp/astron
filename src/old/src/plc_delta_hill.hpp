// Time-stamp: <2016-03-15 16:23:04 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Description: The influence (feedback) of Calcium on ip3 production
// Ref 1: A. Di Garbo et al., Bio Systems (2007)
// Ref 2: T.Hofer, L. Venance et al., Jr. Neuro. Sci (2002)
// Ref 3: M. Stamatakis Jr. Theor. Bio. (2006) 

// The influence (feedback) of Calcium on ip3 production (Ref 1 & Ref 2) 

#ifndef PLC_DELTA_HILL_HPP_INCLUDED
#define PLC_DELTA_HILL_HPP_INCLUDED

#include "data_types.hpp"

class plc_delta_hill
{
public:
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

#endif
