#ifndef DET_MODEL_PMCA_HPP_INCLUDED
#define DET_MODEL_PMCA_HPP_INCLUDED
#include <vector>
#include <iostream>
#include <cmath>
#include <boost/math/constants/constants.hpp>
#include "utility_functions.hpp"

//DECLATATIONS FOR PMCA_SYSTEM
//Units: SI
class DET_MODEL_PMCA
{
private:
  double kf1 = 3E7;   // 1.5E07 M^-1S^-1
  double kb1 = 20.0;    // S^-1
  double kf2 = 20.0;    // S^-1
  double kf3 = 100.0;   // S^-1
  double kl = 12.5;	// 12.5 S^-1

public:
  std::vector<double> X;      // Inside Calcium concentration in Molars
  //------------------ CONSTRUCTORS
  DET_MODEL_PMCA(std::vector<double> X_): X(X_) { };
  template <class State, class Deriv >
  void operator() ( const State &x, Deriv &dxdt , const double  t );
};

//------- PMCA class ODE Function
template <class State, class Deriv >
void DET_MODEL_PMCA::operator() ( const State &x, Deriv &dxdt, const double t )
// [Cai] [PMCA0] [PMCA1] [PMCA2]  [Cao]
// [x0]    [x1]    [x2]    [x3]   [x4] 
{ 
  dxdt[0] = (-x[0]*x[1]*kf1) + (x[1]*kl);
  dxdt[1] = (-x[0]*x[1]*kf1) + (-x[1]*kl) + (x[2]*kb1) + (x[3]*kf3);
  dxdt[2] = (-x[2]*kb1) + (x[1]*x[0]*kf1) + (-x[2]*kf2);
  dxdt[3] = (-x[3]*kf3) + (x[2]*kb1);
  dxdt[4] = (x[3]*kf3) + (-x[1]*kl);
}
#endif // DET_MODEL_PMCA_HPP_INCLUDED




