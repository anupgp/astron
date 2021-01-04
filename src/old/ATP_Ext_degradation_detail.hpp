/* Last Revised Date: 11_MAY_2015 */
/* Lastest status: not checked   */

/* NOTE: This header is used by Synapses only */

//UNITS: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads

#ifndef ATP_EXT_DEGRADATION_DETAIL_HPP_INCLUDED
#define ATP_EXT_DEGRADATION_DETAIL_HPP_INCLUDED

#include <vector>
#include <iostream>
#include <cmath>

#include "physical_constants.hpp"
#include "global_variables.hpp"
#include "utility_functions.hpp"
#include "data_types.hpp"

#include "insilico/core.hpp"

class ATP_Ext_degradation_detail
{
public:
  static double rate_mm(double Vmax, double Km, double sub_conc);
  static double rate_ecto_adenylate_kinase(double Vmaxf, double Kmf_ATP, double Kmf_AMP, double Vmaxb, double Kmb_ADP, double ATP_conc, double ADP_conc, double AMP_conc);
  static double rate_mm_comp_inhib(double Vmax, double Km, double Kin_ATP, double Kin_ADP, double ATP_conc, double ADP_conc, double AMP_conc);
  static double rate_uptake(double Vmax_main, double Km_main, double Km_sub, double main_conc, double sub_conc);
  
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

/* Mich_Ment function definition */
double ATP_Ext_degradation_detail::rate_mm(double Vmax, double Km, double sub_conc)
{
   double value = ( (Vmax * sub_conc ) / (Km + sub_conc) );
   return value;
}

/* Bi_Bi_Mech Ecto adenylate kinase function definition */
double ATP_Ext_degradation_detail::rate_ecto_adenylate_kinase(double Vmaxf, double Kmf_ATP, double Kmf_AMP, double Vmaxb, double Kmb_ADP, double ATP_conc, double ADP_conc, double AMP_conc)
{
   double V_fwd = Vmaxf / (1 + (Kmf_ATP/ATP_conc) + (Kmf_AMP/AMP_conc) + ((Kmf_ATP*Kmf_AMP)/(ATP_conc*AMP_conc)));
   double V_bk = Vmaxb / (1 + (2*Kmb_ADP/ADP_conc) + pow((Kmb_ADP/ADP_conc),2) );
   double value = V_fwd + V_bk;
   return value;
}

/* Mich_Ment_Inh function definition */
double ATP_Ext_degradation_detail::rate_mm_comp_inhib(double Vmax, double Km, double Kin_ATP, double Kin_ADP, double ATP_conc, double ADP_conc, double AMP_conc)
{
   double value = (Vmax * AMP_conc) / ( (Km * (1 + (ATP_conc / Kin_ATP) + (ADP_conc / Kin_ADP)) ) + AMP_conc );
   return value;
}

/* Uptake function definition */
double ATP_Ext_degradation_detail::rate_uptake(double Vmax_main, double Km_main, double Km_sub, double main_conc, double sub_conc)
{
   double value = (Vmax_main * main_conc) / ((Km_main * (1 + (sub_conc/Km_sub) )) + main_conc);
   return value;
}
