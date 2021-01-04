// Time-stamp: <2019-01-03 12:13:21 macbookair>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads

#ifndef LEAK_PRE_HPP_INCLUDED
#define LEAK_PRE_HPP_INCLUDED

typedef std::vector<double> state_type;

// leak_pre declaration
class leak_pre
{
public:
  void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

#endif
