// Time-stamp: <2017-03-30 15:03:23 anup>
// Doc: ip3 receptor (Li-Rinzel model)
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Ref: li1994; shuai2002; riera2011b
// Note: Change in ip3_cyt concentration due to binding with IP3 receptor is not considered.

#ifndef IP3_RECEPTOR_LR_HPP_INCLUDED
#define IP3_RECEPTOR_LR_HPP_INCLUDED

#include "data_types.hpp"
#include "random_number_generator.hpp"

class ip3_receptor_lr
{
private:
  astron::random::random_class rand;
public:
  void current(state_type &variables, state_type &dxdt, state_type &noise, const double t, unsigned index);
  void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
  inline explicit ip3_receptor_lr(long long seed_):rand(seed_,-1,1){};
};

#endif
