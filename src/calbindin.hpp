// Time-stamp: <2016-03-15 13:35:13 anup> 
// Units: All SI units - seconds, Volts, Ampere, Meters, Simenes, Farads

#ifndef CALBINDIN_HPP_INCLUDED
#define CALBINDIN_HPP_INCLUDED

class calbindin
{
public:
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

#endif // CALBINDIN_HPP_INCLUDED
