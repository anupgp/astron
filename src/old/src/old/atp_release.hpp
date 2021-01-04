// Time-stamp: <2016-03-23 15:01:59 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads

#ifndef ATP_RELASE_HPP_INCLUDED	
#define ATP_RELASE_HPP_INCLUDED

#include <vector>
#include <iostream>
#include <cmath>

#include "data_types.hpp"
#include "physical_constants.hpp"
#include "global_variables.hpp"
#include "random_number_generator.hpp"

#include "neuron_vesicle_release.hpp"

#include "insilico/core.hpp"

namespace consts=astron::phy_const;
namespace gvars=astron::globals;

class atp_release
{
private:
  const std::vector<std::string> varnames = {"atpves_H0L0","atpves_H1L0","atpves_H2L0","atpves_H3L0","atpves_H4L0","atpves_H5L0",
					     "atpves_H0L1","atpves_H1L1","atpves_H2L1","atpves_H3L1","atpves_H4L1","atpves_H5L1",
					     "atpves_H0L2","atpves_H1L2","atpves_H2L2","atpves_H3L2","atpves_H4L2","atpves_H5L2",
					     "atpves_H0L0F","atpves_H5L0F","atpves_H5L1F","atpves_H0L2F","atpves_H1L2F","atpves_H2L2F","atpves_H3L2F","atpves_H4L2F","atpves_H5L2F",
					     "atpves_H0L0R","atpves_H5L0R","atpves_H5L1R","atpves_H0L2R","atpves_H1L2R","atpves_H2L2R","atpves_H3L2R","atpves_H4L2R","atpves_H5L2R"};
  const std::vector<std::string> valnames1 = {"atpves_A","atpves_B","atpves_S","atpves_D","atpves_b","atpves_Gspon","atpves_Gsyn","atpves_Gasyn","atpves_Kfast","atpves_Kslow"};
  const std::vector<std::string> valnames2 = {"atpves_ca_cyt_flux","atpves_total_vesicles","atpves_released","atpves_spon_rate","atpves_syn_rate","atpves_asyn_rate","atpves_total_rate",
					      "atpves_rel_flag","atpves_rel_time"};
  rand_new_unif rand_unif;
  BOOST_RNG rng;   

public:
  void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
  atp_release():rng(rand_unif.rand()){};
};

void atp_release::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{
  vesres::state_machine(variables, dxdt, t, index, varnames, valnames1, valnames2);
  vesres::update_rate(variables, t, index, varnames, valnames1, valnames2);
  vesres::update_release(variables, t, index, rng.unif_double(), varnames, valnames1, valnames2);
}

#endif // ATP_RELASE_HPP_INCLUDED
