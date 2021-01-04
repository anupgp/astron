//#ifndef AMPAR_GILLESPIE_CLASS_HPP_INCLUDED
//#define AMPAR_GILLESPIE_CLASS_HPP_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <ctime>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>

#include <boost/numeric/odeint.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/generator_iterator.hpp>
#include <boost/random/linear_congruential.hpp>

#include "astron_utility_functions.hpp"
#include "stl_vector_operation_functions.hpp"
#include "boost_vector_matrix_operation_functions.hpp"

namespace bno=boost::numeric::odeint;
namespace bnu=boost::numeric::ublas;

typedef double value_type;
typedef bnu::matrix< value_type > matrix_type;

class stochastic_ampar
{
   private:
      unsigned int seed;
      boost::minstd_rand rng;   //Boost random number generator
      boost::uniform_real<double> uni_dist;   //Uniform random number distribution which produces values b/w 0 and 1 (0 inclusive, 1 exlusive).
      boost::variate_generator<boost::minstd_rand&, boost::uniform_real< double> > uni_rand;// variate generator
      //--------------
      double kf1 = 4.59E06;    //M^-1 S^-1
      double kb1 = 4.26E03;    //S^-1
      double kf2 = 28.4E06;    //M^-1 * S^-1
      double kb2 = 3.26E03;    //S^-1
      double kf3 = 1.27E06;    //M^-1 S^-1
      double kb3 = 45.7;       //S^-1
      double a0 = 4.24E03;     //S^-1
      double b0 = 900.0;       //S^-1
      double a1 = 2.89E03;     //S^-1
      double b1 = 39.2;        //S^-1
      double a2 = 172.0;       //S^-1
      double b2 = 0.727;       //S^-1
      double a3 = 17.7;        //S^-1
      double b3 = 4.0;         //S^-1
      double a4 = 16.8;        //S^-1
      double b4 = 190.4;       //S^-1
      double Volume = 1.0;
   public:
      //Construct vectors
      matrix_type X;       // A matrix to hold the states
      matrix_type P;       // A matrix that holds the probability at time t
      matrix_type T;       // The transition probability matrix
      matrix_type Q;       // The infinitly small matrix, Q matrix
      /* stochastic_ampar class constructor */
      stochastic_ampar(matrix_type X_, unsigned int seed_=std::time(0)):   seed(seed_),
                                                                        uni_dist(boost::uniform_real<double>(0,1)),
                                                                        uni_rand(boost::variate_generator<boost::minstd_rand&, boost::uniform_real<double> >(rng, uni_dist)),
                                                                        X(X_)
      {
         rng.seed(seed);
         std::vector<double> Tv;
         Tv = {
      };
      //------------------ Function declarations
      void operator() (  matrix_type &p, matrix_type &dpdt , const double  t )
      {
         dpdt = bnu::prod(p,Q);
      };
};
int main(int argc, char **argv)
{
   matrix_type mat(3,2);
   mat(2,1) = 32;
   stochastic_ampar test(mat);
   std::cout << test.X << std::endl;
}

