// Time-stamp: <2016-03-25 14:00:28 anup>

#ifndef RANDOM_NUMBER_GENERATOR_HPP_INCLUDED
#define RANDOM_NUMBER_GENERATOR_HPP_INCLUDED

#include <iostream>
#include <vector>
#include <random>

namespace astron {
  namespace random {
    class random_class
    {
    private:
      std::mt19937_64 rand_gen;
      std::uniform_real_distribution<double> uni_dist_double;
      std::uniform_int_distribution<int> uni_dist_int;
      
    public:
      int uni_int(void);
      double uni_double(void);
      inline explicit random_class(long long rand_seed_, int begin_val_, int end_val_ ):
	rand_gen(rand_seed_), 
	uni_dist_double(begin_val_,end_val_),
	uni_dist_int(begin_val_,end_val_)
      {};
    };

  } // namespace random
}   // namespace astron

#endif

