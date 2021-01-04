#pragma once
#ifndef STL_VECTOR_OPERATION_FUNCTIONS_HPP_INCLUDED
#define STL_VECTOR_OPERATION_FUNCTIONS_HPP_INCLUDED

#include <iostream>
#include <vector>
//-------------------------------------
template<typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& v)
{
   //out << "[";
   size_t last = v.size() - 1;
   for(size_t i = 0; i < v.size(); ++i) {
      out << v[i];
      if (i != last)
         out << " ";
   }
   //out << "]";
   //out << std::endl;
   return out;
}
//----------------------------------
template< typename T >
T vectorSum(const std::vector<T> v)
{
   T sum=0;
   for(size_t i=0; i < v.size();i++){
      sum = sum + v[i];
   }
   return sum;
}
//-------------------------------
std::vector<double> vectorProd(const std::vector<double> a, const std::vector<double> b)
{
   std::vector<double> c( a.size() );
   if(a.size() == b.size()){
      for(size_t i=0; i < a.size();i++){
         c[i] = (a[i] * b[i]);
      }
   }
   return(c);
}
//-----------------------------
template< typename T >
std::vector<T> vectorCumSum(const std::vector<T> v)
{
   std::vector<T> cumsum;
   T sum = 0;
   for(size_t i=0; i < v.size();i++){
      sum = sum + v[i];
      cumsum.push_back(sum);
   }
   return(cumsum);
}
//-------------------------------
std::vector<double> vectorScalarProd(const std::vector<double> a, const double s)
{
   std::vector<double> c( a.size() );
      for(size_t i=0; i < a.size();i++){
         c[i] = (a[i] * s);
      }
   return(c);
}
#endif // STL_VECTOR_OPERATION_FUNCTIONS_HPP_INCLUDED

