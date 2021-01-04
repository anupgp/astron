#ifndef IP3_DET_MODEL_HPP_INCLUDED
#define IP3_DET_MODEL_HPP_INCLUDED
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

   public:

      double CaER = 0.0;      // micro M (Calcium concentration in the ER)
      double ip3_conc = 0.0;      // micro M (Given IP3 concentration in the cytosol)
      double ca_conc = 0.0;

      double ip3_tau = 0.0;
      double ip3_rate = 0.0;
      double ip3_thres = 0.0;
      double ip3_gen = 0.0;
      double ip3_equ = 0.0;

//------------------ CONSTRUCTORS

   /* IP3 class implicit constructor */
   IP3(): CaER(0.0), ca_conc(0.0), ip3_conc(0.0)
   {
   };

  /* ASTRO class explicit constructor */
   IP3( double CaER_, double ca_conc_, double ip3_conc_ ): CaER(CaER_), ca_conc(ca_conc_), ip3_conc(ip3_conc_)
   {
   };
//------------------ Function declarations
   void set_CaER();

   double m_inf();
   double h_inf();
   double h_tau();

   template <class State, class Deriv >
   void operator() ( const State &x, Deriv &dxdt , const double  t );
};
//--------------------m_inf Function
double IP3::m_inf()
{
   double value =  ( ip3_conc / ( ip3_conc + d1 ) ) * ( ca_conc / (ca_conc + d5) ) ;
   return value;
};
//--------------------h_tau Function
double IP3::h_tau()
{
   double Q2 = d2 * ((ip3_conc + d1)/(ip3_conc + d3));
   double value  = 1 / (a2 * (Q2 + ca_conc) );
   return value;
}

//--------------------h_inf Function
double IP3::h_inf()
{
   double Q2 = d2 * ((ip3_conc + d1)/(ip3_conc + d3));
   double value = Q2/(Q2+ca_conc);
   return value;
};
//--------------------Set CaER Function
void IP3::set_CaER()
{
   this->CaER = (c0 - ca_conc) / c1;
   //std::cout << "Set_CaER = " << (c0 - ca_conc)/c1 << "\t" << CaER << "\n";
};
//------- ASTRO class ODE Function
template <class State, class Deriv >
void IP3::operator() ( const State &x_, Deriv &dxdt_ , const double t )
{
   typename boost::range_iterator< const State >::type x = boost::begin( x_ );
   typename boost::range_iterator< Deriv >::type dxdt = boost::begin( dxdt_ );

   //std::cout << CaER << "\n";

   ca_conc = x[1]; // Set Calcium concentration
   ip3_conc = x[2]; // Set ip3 concentration

   set_CaER(); // Update ER calcium level

   dxdt[0] = ( h_inf() - x[0] ) / h_tau() ; // dh/dt

   double JCh = ( c1 * v1 * pow(m_inf(),3) * pow(x[0],3) * (x[1] - CaER) ); //   J_channel
   double JPump = ( v3 * pow(x[1],2) ) / ( pow(k3,2) + pow(x[1],2) ) ;   //    J_Pump
   double JLeak = c1 * v2 * ( x[1] - CaER );   //    J_Leak

   dxdt[1] = - (JCh + JPump + JLeak) ;// dCa/dt
   dxdt[2] =  (1/ip3_tau) * (ip3_equ - x[2])  + (ip3_rate * heaviside(ip3_gen,ip3_thres)) ;//dip3/dt


};

#endif // IP3_DET_MODEL_HPP_INCLUDED
