/*
 * =====================================================================================
 *
 *       Filename:  astron_main_atp.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  06/28/2014 02:04:16 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Anup Pillai (), anupgpillai@gmail.com
 *   Organization:  IISER Pune
 *
 * =====================================================================================
 */
#define DIR1 "/media/chivda/BigDaddy/"
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
//#include "/home/goofy/DATA/SCRIPTS/CPP/Astron/astron_proj.hpp"
#include "astron_ATPext_model.hpp"
//#include "astron_ip3_model.hpp"
//#include "astron_ip3_atp_model.hpp"
//#include "astron_utility_functions.hpp"
//#include "/opt/boost/boost_1_55_0/boost/numeric/ublas/vector.hpp" /*  Specifying the full path in qoutes for a header file */
#include <boost/numeric/odeint.hpp> /*  Specifying the file within < > lets c++ search for it at -I path  */

using namespace std;
using namespace boost::numeric::odeint;

typedef std::vector< double > state_type;

//-----------------
int main(int argc, char **argv)
{
   ATPext atp_ext(25E-04);

   typedef runge_kutta4 < state_type > stepper_type;
   stepper_type rk4;


   double atp_conc0 = 0.0;
   double adp_conc0 = 0.0;
   double amp_conc0 = 0.0;
   double ado_conc0 = 0.0;
   double ino_conc0 = 0.0;

   state_type x = {atp_conc0, adp_conc0, amp_conc0, ado_conc0, ino_conc0};

   double dt = 100.0; // 40 in micro sec
   double atp_pulse = 0.0;
   int pulse_given=0;
   for (double t=0.0; t<= (1000 * 1 * 60); t+= dt)
   {
      x[0] = x[0] + atp_pulse;
      if ( t >=3000 & (t < 4000) & (pulse_given == 0) )
      {
         atp_pulse = 1000.0;   // micro M
         pulse_given = 1;
      }
      else
      {
         atp_pulse = 0.0;
      }
      rk4.do_step(boost::ref(atp_ext),std::make_pair(x.begin(),x.end()),t,dt);
      cout << t << " " << x[0] << " " << x[1] << " " << x[2] << " " << x[3] << " " << x[4] << " " << atp_pulse << "\n";
      //hh.printparam();
      //xwrite(x,t);
      //if (t >=1000) cin.get(); // Press enter key to continue
      //cin.get();
   }

   return 0;
}
