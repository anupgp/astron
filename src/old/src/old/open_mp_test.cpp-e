#include <iostream>
#include <omp.h>



//#pragma omp num_threads(1)

int main()
{
  omp_set_num_threads(1024);
  int k = 0;

  #pragma omp parallel for schedule(static)
  for(int i=1; i< 100000000; i++){
    k = k + k - i*(i-1)*(i-2)*(i-3)*(i-4);
  }

  std::cout << "k = " << k;
}
