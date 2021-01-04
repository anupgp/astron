/*
 * =====================================================================================
 *
 *       Filename:  ip3_atp_model.hpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Sunday 20 July 2014 10:44:10  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Anup Pillai (), anupgpillai@gmail.com
 *   Organization:  IISER Pune
 *
 * =====================================================================================
 */

#ifndef ASTRON_IP3_ATP_MODEL_HPP_INCLUDED
#define ASTRON_IP3_ATP_MODEL_HPP_INCLUDED
#include <vector>
#include <iostream>
#include <cmath>
#include <boost/math/constants/constants.hpp>
#include "astron_utility_functions.hpp"
//const double pi = boost::math::constants::pi<double>();

//DECLATATIONS FOR IP3_SYSTEM
class IP3
{
   private:
//------------------parameters from reduced Li-Rinzel form for IP3-calicum signalling
      double a2 = 0.2E-03;     //    0.2         1/(micro M * sec)
      double d1 = 0.13;   //     0.13        micro M
      double d2 = 1.049;  //     1.049       micro M
      double d3 = 0.9434;   //   0.9434      micro M
      double d5 = 0.08234; //    0.08234     micro M

      double c0 = 2.0;  //       2.0         micro M
      double c1 = 0.185;   //                Dimensionless
      double v1 = 6.0E-03; //        6.0         1/sec
      double v2 = 0.11E-03;//        0.11        1/sec
      double v3 = 0.9E-03;     //    0.9         1/ (micro M * sec)
      double k3 = 0.1;   //      0.1         micro M

//------------ parameters from Stamastakis-Mantzaris model for IP3 via ATP

      double v4 = 4.0E-03;  //4.0 micro M/sec
      double k4 = 0.3;  // 0.3 micro M
      double a5 = 0.0; // dim.less (calcium feedback for IP3 production)
      double k5 = 1.1; // 1.1 micro M
      double v6 = 4E-03; // 0.19 /sec

      double c7 = 1.0; // Dim.less cy_vol/extr-cell_vol
      double v7 = 5.0E-03; // 5.0 micro M/sec (maximum ATP production rate)
      double v8 = 6.0E-03;  // 6.0 micro M/sec (maximum degeneration rate)
      double k8 = 5.0; // 5.0 micro M
      double F0 = 0.05; // dimention less (ATP feedback)
      double Cmax = 1.5; // 1.5 micro M (ATP feedback)
   public:

      double CaER = 0.0;      // micro M (Calcium concentration in the ER)
      //double ip3_conc = 0.0;      // micro M (Given IP3 concentration in the cytosol)
      //double ca_conc = 0.0;

      double ip3_tau = 0.0;
      double ip3_rate = 0.0;
      double ip3_thres = 0.0;
      double ip3_gen = 0.0;
      double ip3_equ = 0.0;

//------------------ CONSTRUCTORS

   IP3(): CaER(0.0)//, ca_conc(0.0), ip3_conc(0.0) /* IP3 class implicit constructor */
   {
   };

   /* ASTRO class explicit constructor */
   //IP3( double CaER_, double ca_conc_, double ip3_conc_ ): CaER(CaER_), ca_conc(ca_conc_), ip3_conc(ip3_conc_)
   IP3( double CaER_ ): CaER(CaER_)
   {
   };
//------------------ Function declarations
   void set_CaER(double ca_conc);

   double m_inf(double ip3_conc, double ca_conc);
   double h_inf(double ip3_conc, double ca_conc);
   double h_tau(double ip3_conc, double ca_conc);

   double F_ca(double ca_conc);

   template <class State, class Deriv >
   void operator() ( const State &x, Deriv &dxdt , const double  t );
};
//--------------------m_inf Function
double IP3::m_inf(double ip3_conc, double ca_conc)
{
   double value =  ( ip3_conc / ( ip3_conc + d1 ) ) * ( ca_conc / (ca_conc + d5) ) ;
   return value;
};
//--------------------h_tau Function
double IP3::h_tau(double ip3_conc, double ca_conc)
{
   double Q2 = d2 * ((ip3_conc + d1)/(ip3_conc + d3));
   double value  = 1 / (a2 * (Q2 + ca_conc) );
   return value;
}

//--------------------h_inf Function
double IP3::h_inf(double ip3_conc, double ca_conc)
{
   double Q2 = d2 * ((ip3_conc + d1)/(ip3_conc + d3));
   double value = Q2/(Q2+ca_conc);
   return value;
};
//--------------------Set CaER Function
void IP3::set_CaER(double ca_conc)
{
   this->CaER = (c0 - ca_conc) / c1;
   //std::cout << "Set_CaER = " << (c0 - ca_conc)/c1 << "\t" << CaER << "\n";
};
//----------Calicum induced ATP release function
double IP3::F_ca(double ca_conc)
{
   double val = ( (F0/(F0-1)) - (2 * (ca_conc/Cmax)) ) / ( (1/(F0-1)) - pow((ca_conc/Cmax),2) );
   return val;
}
//------- ASTRO class ODE Function
template <class State, class Deriv >
void IP3::operator() ( const State &x_, Deriv &dxdt_ , const double t )
{
   typename boost::range_iterator< const State >::type x = boost::begin( x_ );
   typename boost::range_iterator< Deriv >::type dxdt = boost::begin( dxdt_ );

   //std::cout << CaER << "\n";

   set_CaER(x[1]); // Update ER calcium level

   dxdt[0] = ( h_inf(x[2],x[1]) - x[0] ) / h_tau(x[2],x[1]) ; // dh/dt

   double JCh = ( c1 * v1 * pow(m_inf(x[2],x[1]),3) * pow(x[0],3) * (x[1] - CaER) ); //   J_channel
   double JPump = ( v3 * pow(x[1],2) ) / ( pow(k3,2) + pow(x[1],2) ) ;   //    J_Pump
   double JLeak = c1 * v2 * ( x[1] - CaER );   //    J_Leak

   dxdt[1] = - (JCh + JPump + JLeak) ;// dCa/dt
   double ip3_degrade = (x[2] - ip3_equ)/ip3_tau;
   double ip3_mGluR = ip3_rate * heaviside(ip3_gen,ip3_thres);
   //double ip3_atp = (v4 * x[3])/(k4+x[3]);
   double ip3_atp = 0.0;//(v4 * x[3])/(k4+x[3]) * ( (x[1] + ((1-a5)*k5)) / (x[1] + k5) ); //- v6*x[2];
   dxdt[2] =  -ip3_degrade + ip3_mGluR + ip3_atp ;//dip3/dt
   //dxdt[3] = ( c7 * v7 * F_ca(x[1]) ) - ( v8 * (x[3] / (k8 + x[3])) ) ; //dATP/dt

};

#endif // ASTRON_IP3_ATP_MODEL_HPP_INCLUDED
