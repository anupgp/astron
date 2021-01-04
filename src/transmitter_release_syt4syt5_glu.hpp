/* Last Revised Date: 03_AUG_2015 */
// UNITS: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads

#ifndef TRANSMITTER_RELEASE_SYT4SYT5_GLU_HPP_INCLUDED	
#define TRANSMITTER_RELEASE_SYT4SYT5_GLU_HPP_INCLUDED

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

#include "transmitter_release_syt4syt5.hpp"

namespace consts=astron::phy_const;
namespace gvars=astron::globals;

class transmitter_release_syt4syt5_glu
{
private:
  const stringmap varnames = 
    {
      {"syt45_k0","syt45_k0_glu"},
      {"syt45_k1","syt45_k1_glu"},
      {"syt45_k2","syt45_k2_glu"},

      {"syt45_f0","syt45_f0_glu"},
      {"syt45_f1","syt45_f1_glu"},
      {"syt45_f2","syt45_f2_glu"},
      {"syt45_f3","syt45_f3_glu"},
      {"syt45_f4","syt45_f4_glu"},
      {"syt45_f5","syt45_f5_glu"},
      
      {"syt45_vkdoc","syt45_vkdoc_glu"},
      {"syt45_vkrel","syt45_vkrel_glu"},
      {"syt45_vkend","syt45_vkend_glu"},
      {"syt45_vkacd","syt45_vkacd_glu"},
      
      {"syt45_vfmob","syt45_vfmob_glu"},
      {"syt45_vfrel","syt45_vfrel_glu"},
      {"syt45_vfend","syt45_vfend_glu"},
      {"syt45_vfacd","syt45_vfacd_glu"},
    };
  
  const stringmap parnames =  
    {
      {"syt45_kkf","syt45_kkf_glu"},
      {"syt45_kkb","syt45_kkb_glu"},
      {"syt45_kbb","syt45_kbb_glu"},
      {"syt45_k0exo","syt45_k0exo_glu"},
      {"syt45_kcaexo","syt45_kcaexo_glu"},

      {"syt45_fkf","syt45_fkf_glu"},
      {"syt45_fkb","syt45_fkb_glu"},
      {"syt45_fbb","syt45_fbb_glu"},
      {"syt45_f0exo","syt45_f0exo_glu"},
      {"syt45_fcaexo","syt45_fcaexo_glu"},

      {"syt45_rmob2doc","syt45_rmob2doc_glu"},
      {"syt45_rkend","syt45_rkend_glu"},
      {"syt45_rkacd","syt45_rkacd_glu"},
      {"syt45_rkacd2mob","syt45_rkacd2mob_glu"},

      {"syt45_rfend","syt45_rfend_glu"},
      {"syt45_rfacd","syt45_rfacd_glu"},
      {"syt45_rfacd2mob","syt45_rfacd2mob_glu"},

      {"syt45_fracmob2doc","syt45_fracmob2doc_glu"},
      
      {"syt45_initcheck","syt45_initcheck_glu"},
      {"syt45_reldelay","syt45_reldelay_glu"}
    };

  const stringmap valnames  = 
    {
      {"syt45_ca_cyt_flux","syt45_ca_cyt_flux_glu"},
      {"syt45_krrelrate","syt45_krrelrate_glu"},
      {"syt45_ffrelrate","syt45_ffrelrate_glu"},
      {"syt45_totalrelrate","syt45_totalrelrate_glu"},
      
      {"syt45_krrelflag","syt45_krrelflag_glu"},
      {"syt45_krreltime","syt45_krreltime_glu"},
      {"syt45_ffrelflag","syt45_ffrelflag_glu"},
      {"syt45_ffreltime","syt45_ffreltime_glu"},
      {"syt45_relflag","syt45_relflag_glu"},
      {"syt45_reltime","syt45_reltime_glu"},
      {"syt45_random","syt45_random_glu"}
    };

  astron::random::random_class rand1;
  astron::random::random_class rand2;
  astron::random::random_class rand3;
  
public:
  void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
  inline explicit transmitter_release_syt4syt5_glu(long long seed_):
    rand1(seed_*1,0,1),rand2(seed_*2,0,1),rand3(seed_*3,0,1)
  {};
};

#endif
