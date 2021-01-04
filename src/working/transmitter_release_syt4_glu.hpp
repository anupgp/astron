/* Last Revised Date: 03_AUG_2015 */
// UNITS: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads

#ifndef TRANSMITTER_RELEASE_SYT4_GLU_HPP_INCLUDED	
#define TRANSMITTER_RELEASE_SYT4_GLU_HPP_INCLUDED

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

#include "transmitter_release_syt4.hpp"

#include "insilico/core.hpp"

namespace consts=astron::phy_const;
namespace gvars=astron::globals;

class transmitter_release_syt4_glu
{
private:
  const stringmap varnames = 
    {
      {"h0","syt4_glu_h0"},
      {"h1","syt4_glu_h1"},
      {"h2","syt4_glu_h2"},
      {"vrelrsd","syt4_glu_vrelrsd"},
      {"vrecrsd","syt4_glu_vrecrsd"},
      {"vrelnew","syt4_glu_vrelnew"},
      {"vrecnew","syt4_glu_vrecnew"},
      {"relfrac","syt4_glu_relfrac"}
    };
  
  const stringmap parnames =  
    {
      {"hf","syt4_glu_hf"},
      {"hb","syt4_glu_hb"},
      {"b","syt4_glu_b"},
      {"sponf","syt4_glu_sponf"},
      {"fastf","syt4_glu_fastf"},
      {"vesnum","syt4_glu_vesnum"},
      {"krecff","syt4_glu_krecff"},
      {"kreckr","syt4_glu_kreckr"},
      {"knr","syt4_glu_knr"},
      {"krelfrac","syt4_glu_krelfrac"},
      {"newvesfrac","syt4_glu_newvesfrac"},
      {"newrelfrac","syt4_glu_newrelfrac"},
      {"initcheck","syt4_glu_initcheck"},
      {"reldelay","syt4_glu_reldelay"}
    };

  const stringmap valnames  = 
    {
      {"ca_cyt_flux","syt4_glu_ca_cyt_flux"},
      {"sponflag","syt4_glu_sponflag"},
      {"spontime","syt4_glu_spontime"},
      {"fastflag","syt4_glu_fastflag"},
      {"fasttime","syt4_glu_fasttime"},
      {"relflag","syt4_glu_relflag"},
      {"reltime","syt4_glu_reltime"},
      {"sponrelrate","syt4_glu_sponrelrate"},
      {"fastrelrate","syt4_glu_fastrelrate"},
      {"totalrelrate","syt4_glu_totalrelrate"},
      {"resrelrate","syt4_glu_resrelrate"},
      {"newrelrate","syt4_glu_newrelrate"},
      {"rrp","syt4_glu_rrp"},
      {"random","syt4_glu_random"}
    };

  astron::random::random_class rand1;
  astron::random::random_class rand2;
  astron::random::random_class rand3;
  
public:
  void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
  inline explicit transmitter_release_syt4_glu(long long seed_):
    rand1(seed_*1,0,1),rand2(seed_*2,0,1),rand3(seed_*3,0,1)
  {};
};

#endif
