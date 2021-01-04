// Time-stamp: <2016-04-15 12:07:18 anup>
// A detailed p2y receptor class

#ifndef P2Y_RECEPTOR_HPP_INCLUDED
#define P2Y_RECEPTOR_HPP_INCLUDED

class p2y_receptor
{
public:
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

#endif
