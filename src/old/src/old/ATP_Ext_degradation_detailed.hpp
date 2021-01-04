/* Last Revised Date: 30_APRIL_2015 */
/* Lastest status: not checked   */

#ifndef ATP_EXT_DEGRADATION_DETAILED_HPP_INCLUDE
#define ATP_EXT_DEGRADATION_DETAILED_HPP_INCLUDE

#include <vector>
#include <iostream>
#include <cmath>

#include "physical_constants.hpp"
#include "astron_global_variables.hpp"
#include "utility_functions.hpp"
#include "data_types.hpp"
#include "insilico-0.21/include/core.hpp"

//UNITS: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads

class ATP_ext_degradation_detailed
{
private:
   double vol_ext = 0.0;               //Extra-cellular volume in cm^3
   //====== Parameters for ATP hydrolysing enzymes  => ATP ---> ADP + Pi
   //*******TNAPs_high or NSAP_high
   double Vmax_TNAPh_ATP = 2.2;   //micro M/sec.cm^3 actual value from literature = 6.3 nmol/min.cm^3
   double Km_TNAPh_ATP = 33.0;         //actual value from literature = 16.3 micro M
   //*******TNAPs_low
   double Vmax_TNAPl_ATP = 20.0/6E04;  //actual value from literature = 20.0 nmol/min/cm^3
   double Km_TNAPl_ATP = 418.0;        //actual value from literature = 418.0 micro M
   //*******NTPDase3
   double Vmax_NTPD3_ATP = 15.5/6E04;  //actual value from literature = 15.5 nmol/min/cm^3
   double Km_NTPD3_ATP = 114.9;        //actual value from literature = 114.9 micro M
   //*******Ecto nucleotide pyrophosphatase / phosphodiesterases (E-NPPs) => ATP ---> AMP + PPi
   double Vmax_ENPP_ATP = 1.2/6E04;    //actual value from literature = 1.2 nmol/min/cm^3
   double Km_ENPP_ATP = 28.3;          //actual value from literature = 28.3 micro M

   //------ Parameters for Ecto adenylate kinase reaction (ectoAK) =>  ATP + AMP <-----> 2ADP
   //*****Forward reaction
   double Vmaxf_eAK = 2.2/6E04;        //actual value from literature = 2.2 nmol/min/cm^3
   double Kf_eAK_ATP = 30.4;           //actual value from literature = 30.4 micro M
   double Kf_eAK_AMP = 24.7;           //actual value from literature = 24.7 micro M
   //*****Backward reaction
   double Vmaxb_eAK = 2.2/6E04;        //actual value from literature = 2.2 nmol/min/cm^3
   double Kb_eAK_ADP = 61.8;           //actual value from literature = 61.8 micro M

   //------ Parameters for ADP hydrolysing enzymes  => ADP ---> AMP + Pi
   //*******TNAPs_high
   double Vmax_TNAPh_ADP = 0.5/6E04;   //actual value from literature = 0.5 nmol/min/cm^3
   double Km_TNAPh_ADP = 2.8;          //actual value from literature = 2.8 micro M
   //*******TNAPs_low
   double Vmax_TNAPl_ADP = 10.7/6E04;  //actual value from literature = 10.7 nmol/min/cm^3
   double Km_TNAPl_ADP = 83.9;         //actual value from literature = 83.9 micro M

   //------ Parameters for AMP hydrolysing enzymes  => AMP ---> ADO + Pi  >> Competetive binding by ATP & ADP
   //Ecto 5'-nucleotidase (ecto5'-NT)
   double Vmax_e5NT_AMP = 1.7/6E04;    //actual value from literature = 1.7 nmol/min/cm^3
   double Km_e5NT_AMP = 13.0;          //actual value from literature = 13.0 micro M
   //TNAP_high : Tissue non-specific alkaline phosphatase (TNAPs : highTNAP & lowTNAP) or NTPDase1 (TNAPh) & NTPDase 3 (TNAPl)
   double Vmax_TNAPh_AMP = 6.2/6E04;   //actual value from literature = 6.2 nmol/min/cm^3
   double Km_TNAPh_AMP = 27.2;         //actual value from literature = 27.2 micro M
   //TNAPs_low
   double Vmax_TNAPl_AMP = 11.9/6E04;  //actual value from literature = 11.9 nmol/min/cm^3
   double Km_TNAPl_AMP = 694.9;        //actual value from literature = 694.9 micro M
   //Inhibition from ATP and ADP
   double Km_AMP_ATPin = 28.4;         //actual value from literature = 28.4 nmol/min/cm^3
   double Km_AMP_ADPin = 20.4;              //actual value from literature = 20.4 micro M
   //------ Parameters for ADO hydrolysing enzyme  ADO ---> INO
   //Adenosine deaminase 1 (ADA)
   double Vmax_ADA1_ADO = 0.3/6E04;    //actual value from literature = 0.3 nmol/min/cm^3
   double Km_ADA1_ADO = 17.0;          //actual value from literature = 17.0 micro M
   //------ Parameters for ADO and INO uptake mechanisms
   double Vmax_Uptk_ADO = 0.2/6E04;    //actual value from literature = 0.2 nmol/min/cm^3
   double Vmax_Uptk_INO = 0.2/6E04;    //actual value from literature = 0.2 nmol/min/cm^3
   double Km_Uptk_ADO = 1.2;           //actual value from literature = 1.2 micro M
   double Km_Uptk_INO = 1.2;           //actual value from literature = 1.2 micro M

public:
   //Function declarations
   static double rate_mm(double Vmax, double Km, double sub_conc);
   static double rate_ecto_adenylate_kinase(double Vmaxf, double Kmf_ATP, double Kmf_AMP, double Vmaxb, double Kmb_ADP, double ATP_conc, double ADP_conc, double AMP_conc);
   static double rate_mm_comp_inhib(double Vmax, double Km, double Kin_ATP, double Kin_ADP, double ATP_conc, double ADP_conc, double AMP_conc);
   static double rate_uptake(double Vmax_main, double Km_main, double Km_sub, double main_conc, double sub_conc);
};
/* Mich_Ment function definition */
double ATP_ext_degradatio::rate_mm(double Vmax, double Km, double sub_conc)
{
   double value = ( (Vmax * sub_conc ) / (Km + sub_conc) );
   return value;
}
/* Bi_Bi_Mech Ecto adenylate kinase function definition */
double ATP_ext_degradatio::rate_ecto_adenylate_kinase(double Vmaxf, double Kmf_ATP, double Kmf_AMP, double Vmaxb, double Kmb_ADP, double ATP_conc, double ADP_conc, double AMP_conc)
{
   double V_fwd = Vmaxf / (1 + (Kmf_ATP/ATP_conc) + (Kmf_AMP/AMP_conc) + ((Kmf_ATP*Kmf_AMP)/(ATP_conc*AMP_conc)));
   double V_bk = Vmaxb / (1 + (2*Kmb_ADP/ADP_conc) + pow((Kmb_ADP/ADP_conc),2) );
   double value = V_fwd + V_bk;
   return value;
}
/* Mich_Ment_Inh function definition */
double ATP_ext_degradatio::rate_mm_comp_inhib(double Vmax, double Km, double Kin_ATP, double Kin_ADP, double ATP_conc, double ADP_conc, double AMP_conc)
{
   double value = (Vmax * AMP_conc) / ( (Km * (1 + (ATP_conc / Kin_ATP) + (ADP_conc / Kin_ADP)) ) + AMP_conc );
   return value;
}
/* Uptake function definition */
double ATP_ext_degradatio::rate_uptake(double Vmax_main, double Km_main, double Km_sub, double main_conc, double sub_conc)
{
   double value = (Vmax_main * main_conc) / ((Km_main * (1 + (sub_conc/Km_sub) )) + main_conc);
   return value;
}


   //--------------------------------ATP x[0]
   double Vatp_AK =  - Bi_Bi_Mech_AK(Vmaxf_eAK, Kf_eAK_ATP, Kf_eAK_AMP, Vmaxb_eAK, Kb_eAK_ADP, x[0], x[1], x[2]);// [Sf] = ATP & AMP; [Sb] = 2ADP
   double Vatp_TNAPh = - Mich_Ment(Vmax_TNAPh_ATP, Km_TNAPh_ATP, x[0]);// [S] = ATP
   //double Vatp_TNAPl = - Mich_Ment(Vmax_TNAPl_ATP, Km_TNAPl_ATP, x[0]);// [S] = ATP
   //double Vatp_NTPD3 = - Mich_Ment(Vmax_NTPD3_ATP, Km_NTPD3_ATP, x[0]);// [S] = ATP
   //double Vatp_ENPP =  - Mich_Ment(Vmax_ENPP_ATP, Km_ENPP_ATP, x[0]);// [S] = ATP
   //dxdt[0] = Vatp_AK + Vatp_TNAPh + Vatp_TNAPl + Vatp_NTPD3 + Vatp_ENPP;   // dATP/dt
   dxdt[0] = Vatp_TNAPh;  // dATP/dt
   //---------------------------------ADP x[1]
   double Vadp_AK =   Bi_Bi_Mech_AK(Vmaxf_eAK, Kf_eAK_ATP, Kf_eAK_AMP, Vmaxb_eAK, Kb_eAK_ADP, x[0], x[1], x[2]);// [Sf] = ATP & AMP; [Sb] = 2ADP
   double Vadp_TNAPh =  Mich_Ment(Vmax_TNAPh_ATP, Km_TNAPh_ATP, x[0]);// [S] = [ATP]
   double Vadp_TNAPl =  Mich_Ment(Vmax_TNAPl_ATP, Km_TNAPl_ATP, x[0]);// [S] = [ATP]
   double Vadp_NTPD3 =  Mich_Ment(Vmax_NTPD3_ATP, Km_NTPD3_ATP, x[0]);// [S] = [ATP]

   double Vadp_TNAPh2 =  - Mich_Ment(Vmax_TNAPh_ADP, Km_TNAPh_ADP, x[1]);// [S] = [ADP]
   double Vadp_TNAPl2 =  - Mich_Ment(Vmax_TNAPl_ADP, Km_TNAPl_ADP, x[1]);// [S] = [ADP]
   //dxdt[1] = (2* Vadp_AK) + Vadp_TNAPh +Vadp_TNAPl + Vadp_NTPD3 + Vadp_TNAPh2 + Vadp_TNAPl2; //  dADP/dt
   dxdt[1] = Vadp_TNAPh; //  dADP/dt
   //--------------------------------AMP x[2]
   double Vamp_AK =  - Bi_Bi_Mech_AK(Vmaxf_eAK, Kf_eAK_ATP, Kf_eAK_AMP, Vmaxb_eAK, Kb_eAK_ADP, x[0], x[1], x[2]);// [Sf] = ATP & AMP; [Sb] = 2ADP

   double Vamp_e5NT =  - Mich_Ment_Inh(Vmax_e5NT_AMP, Km_e5NT_AMP, Km_AMP_ATPin, Km_AMP_ADPin, x[0],x[1], x[2]);// [S] = ATP,ADP,AMP
   double Vamp_TNAPh = - Mich_Ment_Inh(Vmax_TNAPh_AMP, Km_TNAPh_AMP, Km_AMP_ATPin, Km_AMP_ADPin, x[0], x[1], x[2]);// [S] = ATP,ADP,AMP
   double Vamp_TNAPl = - Mich_Ment_Inh(Vmax_TNAPl_AMP, Km_TNAPl_AMP, Km_AMP_ATPin, Km_AMP_ADPin, x[0], x[1], x[2]);// [S] = ATP,ADP,AMP

   double Vamp_TNAPh2 =   Mich_Ment(Vmax_TNAPh_ADP, Km_TNAPh_ADP, x[1]);// [S] = ADP
   double Vamp_TNAPl2 =   Mich_Ment(Vmax_TNAPl_ADP, Km_TNAPl_ADP, x[1]);// [S] = ADP

   double Vamp_ENPP =   Mich_Ment(Vmax_ENPP_ATP, Km_ENPP_ATP, x[0]);// [S] = ATP

   //dxdt[2] = Vamp_AK + Vamp_e5NT + Vamp_TNAPh + Vamp_TNAPl + Vamp_TNAPh2 + Vamp_TNAPl2 + Vamp_ENPP; //  dAMP/dt
   dxdt[2] = 0; //  dAMP/dt
   //------------------------------ADO x[3]
   double Vado_e5NT =   Mich_Ment_Inh(Vmax_e5NT_AMP, Km_e5NT_AMP, Km_AMP_ATPin, Km_AMP_ADPin, x[0],x[1], x[2]);// [S] = ATP,ADP,AMP
   double Vado_TNAPh =  Mich_Ment_Inh(Vmax_TNAPh_AMP, Km_TNAPh_AMP, Km_AMP_ATPin, Km_AMP_ADPin, x[0], x[1], x[2]);// [S] = ATP,ADP,AMP
   double Vado_TNAPl =  Mich_Ment_Inh(Vmax_TNAPl_AMP, Km_TNAPl_AMP, Km_AMP_ATPin, Km_AMP_ADPin, x[0], x[1], x[2]);// [S] = ATP,ADP,AMP

   double Vado_ADA1 =  - Mich_Ment(Vmax_ADA1_ADO, Km_ADA1_ADO, x[3]);// [S] = ADO
   double Vado_Uptk = - Uptake(Vmax_Uptk_ADO, Km_Uptk_ADO, Km_Uptk_INO, x[3], x[4]);// [S] = ADO, INO
   dxdt[3] = Vado_e5NT + Vado_TNAPh + Vado_TNAPl + Vado_ADA1 + Vado_Uptk; //dADO/dt
   dxdt[3] = 0;
   //-----------------------------INO x[4]
   double Vino_ADA1 =   Mich_Ment(Vmax_ADA1_ADO, Km_ADA1_ADO, x[3]);// [S] = ADO
   double Vino_Uptk = - Uptake(Vmax_Uptk_INO, Km_Uptk_INO, Km_Uptk_ADO, x[4], x[3]);// [S] = INO, ADO
   dxdt[4]=  Vino_ADA1 + Vino_Uptk; //dINO/dt
   dxdt[4] = 0;
   //-------------------------------
};

#endif // ASTRON_ATPext_MODEL_HPP_INCLUDED
