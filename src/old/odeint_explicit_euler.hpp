#ifndef DET_ODEINT_EXPLICIT_EULER_HPP_INCLUDED
#define DET_ODEINT_EXPLICIT_EULER_HPP_INCLUDED

#include <iostream>
#include <cmath>
#include <vector>

#include "physical_constants.hpp"
#include "utility_functions.hpp"

namespace det_odeint_explicit_euler {

  template <class state_type>  
  class DET_ODEINT_EXPLICIT_EULER
  {
  private:
    
  public:

    DET_ODEINT_EXPLICIT_EULER(void) { };
    template < class obj_type >
    void do_step(obj_type &obj, state_type &x, const double t, const double dt); 
  };
  template <class state_type> 
  template <class obj_type>
  void DET_ODEINT_EXPLICIT_EULER<state_type>::do_step (obj_type &obj, state_type &x, const double t, const double dt)
  {
    state_type d (x.size(),0.0);
    obj(x,d,t); 		// obtain the derivative at x
    std::vector<double>::iterator xi = x.begin();
    std::vector<double>::iterator di = d.begin();
    for(int i=0; i<x.size(); i++) {
      *(xi) = (*xi) + (dt *  (*di)); // Euler algorithm
      ++xi;
      ++di;
    }
  };  
}     // det_odeint_explicit_euler

#endif // DET_ODEINT_EXPLICIT_EULER_HPP_INCLUDED
