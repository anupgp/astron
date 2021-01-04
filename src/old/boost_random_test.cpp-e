#include <iostream>
#include <boost_random.hpp>

int main()
{
  //uni_int_dist_type dist1(1,6); // created a uniform integer distribution from [1,6]
  uni_real_dist_type uni_real_dist(0,1); // created a uniform real distribution from [0,1) 
  uni_var_gen_real_type random_unif_real(gen,uni_real_dist); // binding the random generator with "uni_real_dist" distribution

  for(int i=0; i<100; i++){
    std::cout << " " << random_unif_real();
    std::cout << std::endl;
  }  

  return 0;
}

