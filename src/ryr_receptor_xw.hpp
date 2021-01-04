// Time-stamp: <2017-05-24 10:31:56 anup>
// Doc: ryr receptor (Xiao Wang model)
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Ref: wang2015; shuai2002;
// Note: Implimented from the paper: Calcium homeostasis in a local/global whole cell model of permeabilized ventricular myocytes with a Langevin description of stochastic calcium release, Xiao Wang et al., Am J Physiol Heart Circ Physiol 308: H510–H523, 2015.

#ifndef RYR_RECEPTOR_XW_HPP_INCLUDED
#define RYR_RECEPTOR_XW_HPP_INCLUDED

#include "data_types.hpp"
#include "random_number_generator.hpp"

class ryr_receptor_xw
{
private:
  astron::random::random_class rand;
public:
  void current(state_type &variables, state_type &dxdt, state_type &noise, const double t, unsigned index);
  void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
  inline explicit ryr_receptor_xw(long long seed_):rand(seed_,-1,1){};
};

#endif
