#ifndef DET_MODEL_CALBINDIN_HPP_INCLUDED
#define DET_MODEL_CALBINDIN_HPP_INCLUDED
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>

//#include <boost/math/constants/constants.hpp>
#include "utility_functions.hpp"

//DECLATATIONS FOR DET_CALBINDIN_SYSTEM
//Units: Sec, Volts, Ampere, Meter
class DET_MODEL_CALBINDIN
{
private:

  double h1 = 0.55E7;   // M^-1 S^-1
  double h2 = 2.6;	// S^-1
  double m1 = 4.35E7;   // M^-1 S^-1
  double m2 = 35.8;	// S^-1
  const double conCaIn = 100E-09;

  const double kon_f = 0.45E07;	// 1.30E07
  const double koff_f = 2.6;	// 2.4
  const double kon_s = 3.53E07;	// 8.53E07
  const double koff_s = 15.8;	// 44.44

public:
  std::vector<double> X;
  
  void set_boundary_cond (void);

  //Class constructors
  explicit DET_MODEL_CALBINDIN (std::vector<double> X_): X(X_) // Default constructor
  {};

  template <class State, class Deriv >
  void operator() ( const State &x, Deriv &dxdt , const double  t );

};
//------- DET_CALBINDIN class ODE Function
//template <class State, class Deriv >
//void DET_MODEL_CALBINDIN::operator() ( const State &x, Deriv &dxdt, const double t )
//{
//    
//  dxdt[0] = (-2*h1*x[1]*x[0]) + (-2*m1*x[1]*x[0]) + (h2*x[2])  + (m2*x[4]) 
//    + (-h1*x[2]*x[0]) + (2*h2*x[3])  +  (-2*m1*x[2]*x[0]) + (m2*x[5])  +  (-2*h1*x[1]*x[0]) + (h2*x[2]) 
//    + (-h1*x[2]*x[0]) + (2*h2*x[3]) + (m2*x[6]) + (-2*m1*x[3]*x[0]) 
//   
//    + (m2*x[4]) + (-2*m1*x[1]*x[0]) + (-2*h1*x[4]*x[0]) + (h2*x[5]) + (-m1*x[4]*x[0]) + (2*m2*x[7]) 
//    + (-h1*x[5]*x[0]) + (2*h2*x[6]) + (-m1*x[5]*x[0]) + (2*m2*x[8]) + (-2*h1*x[4]*x[0]) + (h2*x[5]) + (m2*x[5]) + (-2*m1*x[2]*x[0]) 
//    + (-h1*x[5]*x[0]) + (2*h2*x[6]) + (-2*m1*x[3]*x[0]) + (m2*x[6]) + (2*m2*x[9]) + (-m1*x[6]*x[0]) 
//      
//    + (2*m2*x[7]) + (-m1*x[4]*x[0]) + (-2*h1*x[7]*x[0]) + (h2*x[8]) 
//    + (-h1*x[8]*x[0]) + (2*h2*x[9]) + (-m1*x[5]*x[0]) + (2*m2*x[8]) + (-2*h1*x[7]*x[0]) + (h2*x[8]) 
//    + (-m1*x[6]*x[0]) + (2*m2*x[9]) + (-h1*x[8]*x[0]) + (2*h2*x[9]); /* d[Ca] / dt */
//
//  dxdt[1] = (-2*h1*x[1]*x[0]) + (-2*m1*x[1]*x[0]) + (h2*x[2])  + (m2*x[4]); /* d[BH0M0] / dt */
//  dxdt[2] = (-h1*x[2]*x[0]) + (2*h2*x[3])  +  (-2*m1*x[2]*x[0]) + (m2*x[5])  +  (2*h1*x[1]*x[0]) + (-h2*x[2]);/* d[BH1M0] / dt */
//  dxdt[3] = (h1*x[2]*x[0]) + (-2*h2*x[3]) + (m2*x[6]) + (-2*m1*x[3]*x[0]);/* d[BH2M0] / dt */
//    
//  dxdt[4] = (-m2*x[4]) + (2*m1*x[1]*x[0]) + (-2*h1*x[4]*x[0]) + (h2*x[5]) + (-m1*x[4]*x[0]) + (2*m2*x[7]);/* d[BH0M1] / dt */
//  dxdt[5] = (-h1*x[5]*x[0]) + (2*h2*x[6]) + (-m1*x[5]*x[0]) + (2*m2*x[8]) + (2*h1*x[4]*x[0]) + (-h2*x[5]) + (-m2*x[5]) + (2*m1*x[2]*x[0]);/* d[BH1M1] / dt */
//  dxdt[6] = (h1*x[5]*x[0]) + (-2*h2*x[6]) + (2*m1*x[3]*x[0]) + (-m2*x[6]) + (2*m2*x[9]) + (-m1*x[6]*x[0]) ;/* d[BH2M1] / dt */
//
//  dxdt[7] = (-2*m2*x[7]) + (m1*x[4]*x[0]) + (-2*h1*x[7]*x[0]) + (h2*x[8]);/* d[BH0M2] / dt */
//  dxdt[8] = (-h1*x[8]*x[0]) + (2*h2*x[9]) + (m1*x[5]*x[0]) + (-2*m2*x[8]) + (2*h1*x[7]*x[0]) + (-h2*x[8]);/* d[BH1M2] / dt */
//  dxdt[9] = (m1*x[6]*x[0]) + (-2*m2*x[9]) + (h1*x[8]*x[0]) + (-2*h2*x[9]);/* d[BH2M2] / dt */
//};
template <class State, class Deriv >
void DET_MODEL_CALBINDIN::operator() ( const State &x, Deriv &dxdt, const double t )
{
  dxdt[0] = (-x[1] * x[0] * 3 * kon_f) + (x[2] * koff_f) + (-x[2] * x[0] * 2 * kon_f) + (x[3] * 2 * koff_f) + (-x[3] * x[0] * kon_f) + (x[4] * 3 * koff_f) +
    (-x[1] * x[0] * kon_s) + (x[5] * koff_s) + (-x[2] * x[0] * kon_s) + (x[6] * koff_s) + (-x[3] * x[0] * kon_s) + (x[7] * koff_s) + (-x[4] * x[0] * kon_s) + (x[8] * koff_s) +
    (-x[5] * x[0] * 3 * kon_f) + (x[6] * koff_f) + (-x[6] * x[0] * 2 * kon_f) + (x[7] * 2 * koff_f) + (-x[7] * x[0] * kon_f) + (x[8] * 3 * koff_f);
  
  dxdt[1] = (-x[1] * x[0] * 3 * kon_f) + (x[2] * koff_f) + (-x[1] * x[0] * kon_s) + (x[5] * koff_s);
  dxdt[2] = (-x[2] * x[0] * 2 * kon_f) + (x[3] * 2 * koff_f) + (-x[2] * x[0] * kon_s) + (x[6] * koff_s) + (-x[2] * koff_f) + (x[1] * x[0] * 3 * kon_f);
  dxdt[3] = (-x[3] * x[0] * kon_f) + (x[4] * 3 * koff_f) + (-x[3] * x[0] * kon_s) + (x[7] * koff_s) + (-x[3] * 2 * koff_f) + (x[2] * x[0] * 2 * kon_f);
  dxdt[4] = (-x[4] * x[0] * kon_s) + (x[8] * koff_s) + (-x[4] * 3 * koff_f) + (x[3] * x[0] * kon_f);
  dxdt[5] = (-x[5] * x[0] * 3 * kon_f) + (x[6] * koff_f) + (-x[5] * koff_s) + (x[1] * x[0] * kon_s);
  dxdt[6] = (-x[6] * x[0] * 2 * kon_f) + (x[7] * 2 * koff_f) + (-x[6] * koff_s) + (x[2] * x[0] * kon_s) + (-x[6] * koff_f) + (x[5] * x[0] * 3 * kon_f);
  dxdt[7] = (-x[7] * x[0] * kon_f) + (x[8] * 3 * koff_f) + (-x[7] * koff_s) + (x[3] * x[0] * kon_s) + (-x[7] * 2 * koff_f) + (x[6] * x[0] * 2 * kon_f);
  dxdt[8] = (-x[8] * koff_s) + (x[4] * x[0] * kon_s) + (-x[8] * 3 * koff_f) + (x[7] * x[0] * kon_f);
};


//------- Set boundary conditions
void DET_MODEL_CALBINDIN::set_boundary_cond(void)
{
  for(int i=0; i<X.size(); i++){
    X[i] = std::max(X[i], 0.0);
  }
};
#endif // DET_MODEL_CALBINDIN_HPP_INCLUDED`
