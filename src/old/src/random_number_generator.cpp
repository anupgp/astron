// Time-stamp: <2016-03-25 13:38:36 anup>

#include <random>
#include <array>

#include "random_number_generator.hpp"

int astron::random::random_class::uni_int(void)
{
  return(uni_dist_int(rand_gen));
};

double astron::random::random_class::uni_double(void)
{
  return(uni_dist_double(rand_gen));
};
