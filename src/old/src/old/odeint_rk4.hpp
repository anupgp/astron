#ifndef DET_ODEINT_RK4_HPP_INCLUDED
#define DET_ODEINT_RK4_HPP_INCLUDED

#include <iostream>
#include <cmath>
#include <vector>

#include "physical_constants.hpp"
#include "utility_functions.hpp"

namespace det_odeint_rk4 {

  template <class obj_type, class state_type>  
  class DET_ODEINT_RK4
  {
  private: 
    //void deriv(
  public:
    void do_step(obj_type &obj, state_type &x0, const double t, const double dt); 
  };
  template <class obj_type, class state_type > 
  void DET_ODEINT_RK4 < obj_type, state_type >::do_step(obj_type &obj, state_type &x, const double t, const double dt)
  {
    state_type x0 = x;
    state_type dm = (x0.size(),0.0); // deriv at mid point
    state_type dt = (x0.size(),0.0); // deriv at trial point
    state_type d = (x0.size(),0.0);  // deriv at final point 
    
    state_type d0 (x0.size(),0.0);
    obj(x0,d0,t);		// Find derivative at x0
    // find x1 at t +  dt/2 
    std::vector<double>::iterator x0i = x0.begin();
    std::vector<double>::iterator d0i = d0.begin();
    for(int i=0; i<x.size(); i++) {
      *(xi+i) = *(xi+i) + ( (dt/2) *  (*(di+i)) ) ;
    }
  };
}     // det_odeint_rk4

#endif // DET_ODEINT_RK4_HPP_INCLUDED
