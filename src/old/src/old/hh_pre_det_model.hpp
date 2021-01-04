#ifndef HH_PRE_HPP_INCLUDED
#define HH_PRE_HPP_INCLUDED

#include <vector>
#include <iostream>
#include <cmath>
#include <boost/math/constants/constants.hpp>

//UNITS: sec, V, A, M

//DECLARATIONS FOR HH_PRE_MODEL

class HH_PRE
{
   private:
      const double pi = boost::math::constants::pi<double>();
      double Cm = 1.0;   // F/m^2 Specific capacitance
      //----Reversal potentials for Na, K, channels in mV
      double ENa = 50.0;   // Reversal potential for Sodium currents in Volts
      double EK = -85.0;    // Reversal potential for Potassium currents in Volts
      double ELeak = -81; // Reversal potential for Leak currents in Volts

      double GNa = 100;   // Maximum conductance for Sodium channels S/m^2
      double GK = 36;    // Maximum conductance for Potassium channels S/m^2
      double GLeak = 0.5;  // Maximum conductance for Leak channels S/m^2

   public:
      double IExt = 0.0; //extern current in Amps
      double Area = 0.0;
      double Cap = 0.0;
      double V = 0.0;      // Membrane voltage V
      /* NEURON class explicit constructor */
      HH_PRE( double Area_ = 500E-08): Area(Area_)
      {
         Cap = Cm * Area;
      };
      //---Equations for bouton Na Channel (Ref: Dominique Engel & Peter Jonas, 2005, Neuron)
      double alpha_Na_act(const double V);
      double beta_Na_act(const double V);
      double alpha_Na_inact(const double V);
      double beta_Na_inact(const double V);
      //---Equations for bouton K Channel (Ref: Dominique Engel & Peter Jonas, 2005, Neuron)
      double alpha_K_act(const double V);
      double beta_K_act(const double V);
      //---Declaration of the ODE solver
      template <class State, class Deriv >
      void operator() ( const State &x, Deriv &dxdt , const double  t );
};
//Function declarations
//------------- Na+ channels --- implimented from classical HH (1952)
double HH_PRE::alpha_Na_act(const double V)
{
   double a = 0.1;
   double b = 45;
   double c = 10;
   double val = (- a * ( (V + b) / (exp( -(V + b) / c ) - 1 ) ) );

   double A = 93.82;
   double B = -105;
   double C = 17;
   double VAL = (- A * ( (V + B) / (exp( -(V + B) / C ) - 1 ) ) );
   return (VAL);
}
double HH_PRE::beta_Na_act(const double V)
{
   double a = 4;
   double b = 70;
   double c = 18;
   double val = ( a * ( exp( - (V + b) / c )) );

   double A = 0.168;
   double C = 23.27;
   double VAL = ( A *  exp( - V / C ) );

   return (VAL);
}
double HH_PRE::alpha_Na_inact(const double V)
{
   double val = 0.07 * exp( -( V + 70) /20 );

   double A = 0.0001;
   double C = 18.706;
   double VAL = ( A *  exp( - (V + 0) / C ) );

   return (VAL);
}
double HH_PRE::beta_Na_inact(const double V)
{
   double val = ( 1 / ( exp( - (V + 40) / 10) + 1) );

   double A = 6.6;
   double B = 17.6;
   double C = 13.3;
   double VAL = ( A / ( (exp( -(V + B) / C ) + 1 ) ) );

   return (VAL);
}
//--------K+ channel alpha & beta
double HH_PRE::alpha_K_act(const double V)
{
   double val = -0.01 * (V + 60) / ( exp( -(V +  60) / 10) - 1 );
   double VAL = -0.01 * (V + 55) / ( exp( -(V +  55) / 10) - 1 );
   return (VAL);
};
double HH_PRE::beta_K_act(const double V)
{
   double val = 0.125 * exp (- (V + 70) / 80);
   double VAL = 0.125 * exp (- (V + 65) / 80);
   return (VAL);
};
//-------HH_PRE class ODE Function

template <class State, class Deriv >
void HH_PRE::operator() ( const State &x, Deriv &dxdt , const double t )
{
   //typename boost::range_iterator< const State >::type x_it = boost::begin( x_ );
   //typename boost::range_iterator< Deriv >::type dxdt_it = boost::begin( dxdt_ );

   dxdt[0] = ( alpha_Na_act(x[3]) * (1 - x[0]) ) - (beta_Na_act(x[3]) * x[0]); // Na activation
   dxdt[1] = ( alpha_Na_inact(x[3]) * (1 - x[1]) ) - (beta_Na_inact(x[3]) * x[1]); // Na inactivation
   dxdt[2] = ( alpha_K_act(x[3]) * (1 - x[2]) ) - (beta_K_act(x[3]) * x[2]); // K activation
   double INa =   -(Area * GNa * pow(x[0],3) * x[1] * (x[3] - ENa) );
   double IK =   -(Area * GK * pow(x[2],4) * (x[3] - EK) );
   double ILeak = -(Area * GLeak *  (x[3] - ELeak) );
   dxdt[3] = (1/Cap) * (INa + IK + ILeak  + (IExt * Area)  );
};

#endif // HH_PRE_HPP_INCLUDED

