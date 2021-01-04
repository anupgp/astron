/* Last Revised Date: 03_AUG_2015 */
// UNITS: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads

#ifndef GLUTAMATE_RELASE_HPP_INCLUDED	
#define GLUTAMATE_RELASE_HPP_INCLUDED

#include <vector>
#include <iostream>
#include <cmath>

#include "insilico/include/data_types.hpp"
#include "insilico/include/physical_constants.hpp"
#include "insilico/include/astron_global_variables.hpp"
#include "insilico/include/astron_boost_random.hpp"

#include "insilico/include/vesicular_release.hpp"

#include "insilico-0.25/include/insilico/core.hpp"

namespace consts=astron::phy_const;
namespace gvars=astron::global_vars;

class glutamate_release
{
private:

  const std::vector<std::string> varnames = {"gluves_H0L0","gluves_H1L0","gluves_H2L0","gluves_H3L0","gluves_H4L0","gluves_H5L0",
					     "gluves_H0L1","gluves_H1L1","gluves_H2L1","gluves_H3L1","gluves_H4L1","gluves_H5L1",
					     "gluves_H0L2","gluves_H1L2","gluves_H2L2","gluves_H3L2","gluves_H4L2","gluves_H5L2",
					     "gluves_H0L0F","gluves_H5L0F","gluves_H5L1F","gluves_H0L2F","gluves_H1L2F","gluves_H2L2F","gluves_H3L2F","gluves_H4L2F","gluves_H5L2F",
					     "gluves_H0L0R","gluves_H5L0R","gluves_H5L1R","gluves_H0L2R","gluves_H1L2R","gluves_H2L2R","gluves_H3L2R","gluves_H4L2R","gluves_H5L2R"};
  const std::vector<std::string> valnames1 = {"gluves_A","gluves_B","gluves_S","gluves_D","gluves_b","gluves_Gspon","gluves_Gsyn","gluves_Gasyn","gluves_Kfast","gluves_Kslow"};
  const std::vector<std::string> valnames2 = {"gluves_ca_cyt_flux","gluves_total_vesicles","gluves_released","gluves_spon_rate","gluves_syn_rate","gluves_asyn_rate","gluves_total_rate",
					      "gluves_rel_flag","gluves_rel_time"};
  rand_new_unif rand_unif;
  BOOST_RNG rng;   

public:
  void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
  glutamate_release():rng(rand_unif.rand()){};
};

void glutamate_release::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{
  vesres::state_machine(variables, dxdt, t, index, varnames, valnames1, valnames2);
  vesres::update_rate(variables, t, index, varnames, valnames1, valnames2);
  vesres::update_release(variables, t, index, rng.unif_double(), varnames, valnames1, valnames2);
}

#endif // GLUTAMATE_RELASE_HPP_INCLUDED
