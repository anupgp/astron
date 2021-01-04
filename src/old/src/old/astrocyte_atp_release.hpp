/* Last Revised Date: 03_AUG_2015 */
// UNITS: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads

#ifndef ASTROCYTE_ATP_RELASE_HPP_INCLUDED	
#define ASTROCYTE_ATP_RELASE_HPP_INCLUDED

#include <vector>
#include <iostream>
#include <cmath>
#include <unordered_map>
#include <string>
#include <ctime>

#include "data_types.hpp"
#include "physical_constants.hpp"
#include "global_variables.hpp"
#include "random_number_generator.hpp"
#include "transmitter_release_astrocyte_hybrid.hpp"

#include "insilico/core.hpp"

namespace consts=astron::phy_const;
namespace gvars=astron::globals;

class astrocyte_atp_release
{
private:
  const stringmap varnames = 
    {
      {"h0l0","atpves_h0l0"},
      {"h1l0","atpves_h1l0"},
      {"h2l0","atpves_h2l0"},
      {"h0l1","atpves_h0l1"},
      {"h1l1","atpves_h1l1"},
      {"h2l1","atpves_h2l1"},
      {"h0l2","atpves_h0l2"},
      {"h1l2","atpves_h1l2"},
      {"h2l2","atpves_h2l2"},
      {"h0l0f","atpves_h0l0f"},
      {"h2l0f","atpves_h2l0f"},
      {"h2l1f","atpves_h2l1f"},
      {"h2l2f","atpves_h2l2f"},
      {"h0l2f","atpves_h0l2f"},
      {"h1l2f","atpves_h1l2f"},
      {"relves_ff","atpves_relves_ff"},
      {"relves_kr","atpves_relves_kr"}
    };
  
  const stringmap parnames =  
    {
      {"hf","atpves_hf"},
      {"hb","atpves_hb"},
      {"lf","atpves_lf"},
      {"lb","atpves_lb"},
      {"b","atpves_b"},
      {"sponf","atpves_sponf"},
      {"slowf","atpves_slowf"},
      {"sslowf","atpves_sslowf"},
      {"freezeb","atpves_freezeb"},
      {"recycle_ff","atpves_recycle_ff"},
      {"recycle_kr","atpves_recycle_kr"},
      {"percent_ff","atpves_percent_ff"},
      {"ves_num","atpves_ves_num"},
      {"init_check","atpves_init_check"},
      {"rel_delay","atpves_rel_delay"},
      {"refract_on","atpves_refract_on"},
    };

  const stringmap valnames  = 
    {
      {"ca_cyt_flux","atpves_ca_cyt_flux"},
      {"spon_flag","atpves_spon_flag"},
      {"spon_time","atpves_spon_time"},
      {"slow_flag","atpves_slow_flag"},
      {"slow_time","atpves_slow_time"},
      {"sslow_flag","atpves_sslow_flag"},
      {"sslow_time","atpves_sslow_time"},
      {"rel_flag","atpves_rel_flag"},
      {"rel_time","atpves_rel_time"},
      {"ff_flag","atpves_ff_flag"},
      {"kr_flag","atpves_kr_flag"},
      {"spon_relrate","atpves_spon_relrate"},
      {"slow_relrate","atpves_slow_relrate"},
      {"sslow_relrate","atpves_sslow_relrate"},
      {"total_relrate","atpves_total_relrate"},
      {"rrp","atpves_rrp"},
      {"random","atpves_random"}
    };

  astron::random::random_class rand1;
  astron::random::random_class rand2;
  astron::random::random_class rand3;
  astron::random::random_class rand4;
  astron::random::random_class rand5;
  astron::random::random_class rand6;
  astron::random::random_class rand7;
  astron::random::random_class rand8;
  
public:
  void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
  inline explicit astrocyte_atp_release(long long seed_):
    rand1(seed_*1,0,1),rand2(seed_*2,0,1),rand3(seed_*3,0,1),rand4(seed_*4,0,1),rand5(seed_*5,0,1),rand6(seed_*6,0,1),rand7(seed_*7,0,1),rand8(seed_*8,0,1)
  {};
};

#endif // ASTROCYTE_ATP_RELASE_HPP_INCLUDED
