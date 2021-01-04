// Time-stamp: <2016-04-06 13:45:00 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads

#ifndef K_PRE_HPP_INCLUDED
#define K_PRE_HPP_INCLUDED

typedef std::vector<double> state_type;

// k_pre declaration
class k_pre
{
public:
  void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

#endif
