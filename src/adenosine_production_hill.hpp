// Time-stamp: <2016-03-23 10:44:14 anup>

#ifndef ADO_PRODUCTION_HILL_HPP_INCLUDED
#define ADO_PRODUCTION_HILL_HPP_INCLUDED

class ado_production_hill
{
public:
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

#endif	// ADO_PRODUCTION_HILL_HPP_INCLUDED
