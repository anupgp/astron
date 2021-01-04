#ifndef DET_MODEL_VGCC_HPP_INCLUDED
#define DET_MODEL_VGCC_HPP_INCLUDED

#include <iostream>
#include <cmath>
#include <vector>

#include "physical_constants.hpp"
#include "utility_functions.hpp"

namespace consts=astron::phy_const;

class DET_MODEL_VGCC
{
private:
  const double GCa = 2E-12;      // Single channel conductance = 2.2E-12 Siemens 
  const double conCaOut = 2E-03;   // Outside Calcium concentration is fixed at 2 mM
  const double Xmax = 10;		   // Total concentration of Calcium channels
  //const double sfactor = 1;
  const double ERev = 60E-03;	// Reversal potential of Calcium channel fixed at 60 mV (data from from Borst & Sakmann; JP 1998)
  // Private Functions
  
  double boltz(double V_);	// Calculates Boltzmann function for voltage: taken from Bischofberger et. al, jns, 2002
  double GHK(double V_);		// Calculates modified GHK: taken from Bischofberger et. al, jns, 2002
  double alpha(double V_, int rx_id); 
  double beta(double V_, int rx_id);

  void update_ECa(void);
  void update_conCaIn(double dt);
  void update_ICa();
  

public:

  std::vector<double> X;                // Number of open channels
  
  double ECa = 0.0;		// Reversal potential for Calcium channels
  double volume = 0.0;		// Volume of the reaction space
  double area = 0.0; 

  double V = 0.0;      // Membrane voltage V
  double conCaIn = 0.0;    // Inside Calcium concentration 100 nM
  double I_Ca = 0.0;       // Calcium current

  double  numCaIn = 0.0;  
  // Constructor
  explicit DET_MODEL_VGCC (std::vector<double> X_ = {0,0,0,0,0}, double V_ = -70.0E-03, 
			   double conCaIn_ = 100E-09, double volume_ = 1E-18, double area_ = 8.5E-12 ): V(V_),
													conCaIn(conCaIn_), 
													volume(volume_), 
													area(area_), 
													X(X_) {};
  void update_variables(double dt);
  template <class State, class Deriv >
  void operator() ( const State &x, Deriv &dxdt , const double  t );
};
//---------------------
double DET_MODEL_VGCC::boltz(double V_)
{
  return(1/(1+exp((-3.9E-03 -V_)/7.1E-03)));
};
//---------------------
double DET_MODEL_VGCC::GHK(double V_)
{
  return(-3.003E-09 * V_ * (  (0.3933 - exp(-V_/80.36E-03))/(1 - exp(V_/80.36E-03))) * boltz(V_) );
};
void DET_MODEL_VGCC::update_ECa(void) // Calculates reversal potential from Calcium concentrations (outside/inside)
{
  ECa = ( (consts::R * consts::T) / (consts::Z_Ca * consts::F) ) * log(conCaOut/conCaIn);
  //std::cout << V << " " << ECa << std::endl;

};
void DET_MODEL_VGCC::update_variables(double dt)
{
  //I_Ca = ( (X[4]) * Xmax * 9E-05 * GHK(V) );
  update_ECa();
  I_Ca = X[4] * Xmax * GCa * (V - ERev);
  double dq = I_Ca * dt * consts::Z_Ca;	// Charge that came in
  double dmoles_CaIn = dq / (consts::F * consts::Z_Ca);
  numCaIn = dmoles_CaIn * consts::Av;
  conCaIn = conCaIn - ( dmoles_CaIn / (1000 * volume) );
  //std::cout << "ConCaIn = " << conCaIn << " ECa " << ECa << std::endl;  
};
//------------ alpha Function
double DET_MODEL_VGCC::alpha(double V_, int rx_id)
{
  double value = 0.0;
  switch (rx_id){
  case 1:{
    double a = 4.04E03;     // 4.04E03 sec^-1
    double v = 49.14E-03;     // 49.14E-03 V
    value = a * exp( V_/v);
    break;
  }
  case 2:{
    double a = 6.70E03;     // 6.7E03 sec^-1
    double v = 42.08E-03;     // 42.08E-03 V
    value = a * exp( V_/v);
    break;
  }
  case 3:{
    double a = 4.39E03;     // 4.39E03 sec^-1
    double v = 55.31E-03;     // 55.31E-03  V
    value = a * exp( V_/v);
    break;
  }
  case 4:{
    double a = 17.33E03;     // 17.33E03 sec^-1
    double v = 26.55E-03;     // 26.55E-03 V
    value = a * exp( V_/v);
    break;
  }
  }
  return std::max<double>(value,0.0);
};
//----------- beta Function
double DET_MODEL_VGCC::beta(double V_, int rx_id)
{
  double value = 0.0;
  switch (rx_id){
  case 1:{
    double b = 2.88E03;     // 2.88E03 sec^-1
    double v = 49.14E-03;     // 49.14E-03 V
    value = b * exp( -V_/v);
    break;
  }
  case 2:{
    double b = 6.30E03;     // 6.30E03 sec^-1
    double v = 42.08E-03;     // 42.08E-03 V
    value = b * exp( -V_/v);
    break;
  }
  case 3:{
    double b = 8.16E03;     // 8.16E03 sec^-1
    double v = 55.31E-03;     // 55.31E-03 V
    value = b * exp( -V_/v);
    break;
  }
  case 4:{
    double b = 1.84E03;     // 1.84E03 sec^-1
    double v = 26.55E-03;     // 26.55E-03 V
    value = b * exp( -V_/v);
    break;
  }
  }
  return std::max(value,0.0);
};
// }}}
//------- VGCC class ODE Function
template <class State, class Deriv >
void DET_MODEL_VGCC::operator() ( const State &x, Deriv &dxdt, const double t )
{
  dxdt[0] = (beta(V,1)*x[1]) + (-alpha(V,1)*x[0]); /* d[C0]/dt */
  dxdt[1] = (alpha(V,1)*x[0]) + (-beta(V,1)*x[1]) +  (-alpha(V,2)*x[1]) + (beta(V,2)*x[2]); /* d[C1]/dt */
  dxdt[2] = (alpha(V,2)*x[1]) + (-beta(V,2)*x[2]) +  (-alpha(V,3)*x[2]) + (beta(V,3)*x[3]); /* d[C2]/dt */
  dxdt[3] = (alpha(V,3)*x[2]) + (-beta(V,3)*x[3]) +  (-alpha(V,4)*x[3]) + (beta(V,4)*x[4]); /* d[C3]/dt */
  dxdt[4] = (alpha(V,4)*x[3]) + (-beta(V,4)*x[4]); /* d[0]/dt */
};
#endif // DET_MODEL_VGCC_HPP_INCLUDED
