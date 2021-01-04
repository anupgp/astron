/* Last Revised Date: 03_AUG_2015 */
// UNITS: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads

#ifndef TRANSMITTER_RELEASE_HYBRID_GLU_HPP_INCLUDED	
#define TRANSMITTER_RELEASE_HYBRID_GLU_HPP_INCLUDED

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

#include "transmitter_release_hybrid.hpp"

#include "insilico/core.hpp"

namespace consts=astron::phy_const;
namespace gvars=astron::globals;

class transmitter_release_hybrid_glu
{
  private:
  const stringmap varnames = 
    {
      {"h0l0","gluves_h0l0"},
      {"h1l0","gluves_h1l0"},
      {"h2l0","gluves_h2l0"},
      {"h0l1","gluves_h0l1"},
      {"h1l1","gluves_h1l1"},
      {"h2l1","gluves_h2l1"},
      {"h0l2","gluves_h0l2"},
      {"h1l2","gluves_h1l2"},
      {"h2l2","gluves_h2l2"},
      {"href","gluves_href"},
      {"hff","gluves_hff"},
      {"hkr","gluves_hkr"}
    };
  
  const stringmap parnames =  
    {
      {"hf","gluves_hf"},
      {"hb","gluves_hb"},
      {"lf","gluves_lf"},
      {"lb","gluves_lb"},
      {"b","gluves_b"},
      {"sponf","gluves_sponf"},
      {"slowf","gluves_slowf"},
      {"sslowf","gluves_sslowf"},
      {"refb","gluves_refb"},
      {"recfff","gluves_recfff"},
      {"reckrf","gluves_reckrf"},
      {"probff","gluves_probff"},
      {"vesnum","gluves_vesnum"},
      {"initcheck","gluves_initcheck"},
      {"reldelay","gluves_reldelay"},
      {"refon","gluves_refon"}
    };

  const stringmap valnames  = 
    {
      {"ca_cyt_flux","gluves_ca_cyt_flux"},
      {"sponflag","gluves_sponflag"},
      {"spontime","gluves_spontime"},
      {"slowflag","gluves_slowflag"},
      {"slowtime","gluves_slowtime"},
      {"sslowflag","gluves_sslowflag"},
      {"sslowtime","gluves_sslowtime"},
      {"relflag","gluves_relflag"},
      {"reltime","gluves_reltime"},
      {"ffflag","gluves_ffflag"},
      {"krflag","gluves_krflag"},
      {"sponrelrate","gluves_sponrelrate"},
      {"slowrelrate","gluves_slowrelrate"},
      {"sslowrelrate","gluves_sslowrelrate"},
      {"totalrelrate","gluves_totalrelrate"},
      {"rrp","gluves_rrp"},
      {"random","gluves_random"}
    };

  astron::random::random_class rand1;
  astron::random::random_class rand2;
  astron::random::random_class rand3;
  astron::random::random_class rand4;
  
  
public:
  void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
  inline explicit transmitter_release_hybrid_glu(long long seed_):
    rand1(seed_*1,0,1),rand2(seed_*2,0,1),rand3(seed_*3,0,1),rand4(seed_*4,0,1)
  {};
};

#endif
