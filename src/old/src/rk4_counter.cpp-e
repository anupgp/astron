// Time-stamp: <2016-04-29 16:57:50 anup>

#include <vector>
#include <iostream>

#include "rk4_counter.hpp"

void rk4_counter::counter_update(const unsigned int idx, const double t)
{
  // counter vector is automatically incremented if index is more than vector size
  if(idx > counter.size()-1){
    counter.resize(idx+1,0);
  }
  // for(auto el:rk4counter) std::cout << el << " ";
  // std::cout << std::endl;
  counter.at(idx)++;
  if(t>= prev_time && (counter[idx] == 5))
    {
      prev_time = t;
      counter[idx] = 1;
    }
  // for(auto el:rk4counter) std::cout << el << " ";
  // std::cout << std::endl;
  // std::cin.get();
}
