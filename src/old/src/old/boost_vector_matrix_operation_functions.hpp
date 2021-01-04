#pragma once
#ifndef BOOST_VECTOR_MATRIX_OPERATION_FUNCTIONS_HPP_INCLUDED
#define BOOST_VECTOR_MATRIX_OPERATION_FUNCTIONS_HPP_INCLUDED

namespace bnu=boost::numeric::ublas;

//-------------------------------
template <typename vec_type, typename mat_type>
void MatrixCopy(const std::vector<vec_type> v, bnu::matrix<mat_type> &m, const bool byrow = true)
/*Copy a vector v to the matrix m in either row or columnwise*/
{
   if(v.size() != m.size1()*m.size2()){
      std::cout << "rows of the matrix = " << m.size1() << std::endl << "columns of matrix = " << m.size2() << std::endl;
      std::cout << "size of vector = " << v.size() << std::endl;
      std::cout << "size of vector not equal to sum of row and columns of the given matrix" << std::endl;
      return;
   }
      if(byrow){
         for(size_t row=0; row<m.size1(); row++){
            for(size_t col=0; col<m.size2(); col++){
               m(row,col) = v[(row*(m.size2()))+(col)];
            }
         }
      }
      else{
         for(size_t col=0; col<m.size2(); col++){
            for(size_t row=0; row<m.size1(); row++){
               m(row,col) = v[(col*(m.size1()))+(row)];
            }
         }
      }

}
//-------------------------------
std::vector<double> colSum(const bnu::matrix<double> &m)
{
   std::vector<double> colsum;
   for(size_t col=0; col < m.size2(); col++){
      double sum=0.0;
      for(size_t row=0; row < m.size1(); row++){
         sum = sum + m(row,col);
      }
      colsum.push_back(sum);
   }
   return colsum;
}
//-------------------------------
std::vector<double> rowSum(const bnu::matrix<double> &m)
{
   std::vector<double> rowsum;
   for(size_t row=0; row < m.size1(); row++){
      double sum=0.0;
      for(size_t col=0; col < m.size2(); col++){
         sum = sum + m(row,col);
      }
      rowsum.push_back(sum);
   }
   return rowsum;
}
#endif   // BOOST_VECTOR_MATRIX_OPERATION_FUNCTIONS_HPP_INCLUDED

