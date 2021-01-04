/* Last Revised Date: 03_AUG_2015 */
// UNITS: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads

#ifndef NEURON_GLUTAMATE_RELASE_HPP_INCLUDED	
#define NEURON_GLUTAMATE_RELASE_HPP_INCLUDED

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
#include "transmitter_release_neuron.hpp"

#include "insilico/core.hpp"

namespace consts=astron::phy_const;
namespace gvars=astron::globals;

class neuron_glutamate_release
{
private:
  const stringmap varnames = 
    {
      {"h0l0","gluves_h0l0"},
      {"h1l0","gluves_h1l0"},
      {"h2l0","gluves_h2l0"},
      {"h3l0","gluves_h3l0"},
      {"h4l0","gluves_h4l0"},
      {"h5l0","gluves_h5l0"},
      {"h0l1","gluves_h0l1"},
      {"h1l1","gluves_h1l1"},
      {"h2l1","gluves_h2l1"},
      {"h3l1","gluves_h3l1"},
      {"h4l1","gluves_h4l1"},
      {"h5l1","gluves_h5l1"},
      {"h0l2","gluves_h0l2"},
      {"h1l2","gluves_h1l2"},
      {"h2l2","gluves_h2l2"},
      {"h3l2","gluves_h3l2"},
      {"h4l2","gluves_h4l2"},
      {"h5l2","gluves_h5l2"},
      {"h0l0f","gluves_h0l0f"},
      {"h5l0f","gluves_h5l0f"},
      {"h5l1f","gluves_h5l1f"},
      {"h0l2f","gluves_h0l2f"},
      {"h1l2f","gluves_h1l2f"},
      {"h2l2f","gluves_h2l2f"},
      {"h3l2f","gluves_h3l2f"},
      {"h4l2f","gluves_h4l2f"},
      {"h5l2f","gluves_h5l2f"},
      {"relves_ff","gluves_relves_ff"},
      {"relves_kr","gluves_relves_kr"}
    };
  
  const stringmap parnames =  
    {
      {"hf","gluves_hf"},
      {"hb","gluves_hb"},
      {"lf","gluves_lf"},
      {"lb","gluves_lb"},
      {"b","gluves_b"},
      {"sponf","gluves_sponf"},
      {"synf","gluves_synf"},
      {"asynf","gluves_asynf"},
      {"freezeb","gluves_freezeb"},
      {"recycle_ff","gluves_recycle_ff"},
      {"recycle_kr","gluves_recycle_kr"},
      {"percent_ff","gluves_percent_ff"},
      {"ves_num","gluves_ves_num"},
      {"init_check","gluves_init_check"},
      {"rel_delay","gluves_rel_delay"},
      {"refract_on","gluves_refract_on"},
    };

  const stringmap valnames  = 
    {
      {"ca_cyt_flux","gluves_ca_cyt_flux"},
      {"spon_flag","gluves_spon_flag"},
      {"spon_time","gluves_spon_time"},
      {"syn_flag","gluves_syn_flag"},
      {"syn_time","gluves_syn_time"},
      {"asyn_flag","gluves_asyn_flag"},
      {"asyn_time","gluves_asyn_time"},
      {"rel_flag","gluves_rel_flag"},
      {"rel_time","gluves_rel_time"},
      {"ff_flag","gluves_ff_flag"},
      {"kr_flag","gluves_kr_flag"},
      {"spon_relrate","gluves_spon_relrate"},
      {"syn_relrate","gluves_syn_relrate"},
      {"asyn_relrate","gluves_asyn_relrate"},
      {"total_relrate","gluves_total_relrate"},
      {"random","gluves_random"},
      {"rrp","gluves_rrp"}
    };

  astron::random::random_class rand1;
  astron::random::random_class rand2;
  astron::random::random_class rand3;
  astron::random::random_class rand4;
  astron::random::random_class rand5;
  astron::random::random_class rand6;
  astron::random::random_class rand7;
  astron::random::random_class rand8;
  astron::random::random_class rand9;
  astron::random::random_class rand10;
  astron::random::random_class rand11;

public:
  void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
    inline explicit neuron_glutamate_release(long long seed_):
    rand1(seed_*1,0,1),rand2(seed_*2,0,1),rand3(seed_*3,0,1),rand4(seed_*4,0,1),
    rand5(seed_*5,0,1),rand6(seed_*6,0,1),rand7(seed_*7,0,1),rand8(seed_*8,0,1),
    rand9(seed_*9,0,1),rand10(seed_*10,0,1),rand11(seed_*11,0,1)
  {};
};

#endif
