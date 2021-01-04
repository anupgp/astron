#ifndef ASTRON_UTILITY_FUNCTIONS_HPP_INCLUDED
#define ASTRON_UTILITY_FUNCTIONS_HPP_INCLUDED

#include <vector>
#include <iostream>
#include <cmath>


// -------------------Write_state Function
template <class State_Type >
struct write_state
{
   void operator() (State_Type x, double t=0.0, std::string sep ="\n")
   {
   //std::cout << t << "\t";
   std::cout << t << " ";
   for( std::vector<double>::iterator itr = x.begin(); itr != x.end() ; ++itr)
      {
         std::cout << *itr << " ";
      };
   std::cout << sep;
   };
};

#endif // ASTRON_UTILITY_FUNCTIONS_HPP_INCLUDED
