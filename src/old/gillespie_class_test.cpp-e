#include <iostream>
#include <cmath>
#include <vector>

#include "stl_vector_operation_functions.hpp"
#include "ampar_gillespie_class.hpp"
#include "gillespie_class.hpp"

//Function that computes Glutamate profile over time in the space just above the AMPARs
double glu_conc(double t, double t0)
{
   double tt = t-t0;
   double aa = 300;
   double bb = 2;
   double cc = 185E-06;
   double dd = 0;
   double delay = 2.0E-05;
   double out = dd + ( (aa-dd) / (1 + (std::pow( ((tt - delay) / cc), bb) ) ) );
   return(out);
}
int main(int argc, char** argv)
{

   std::vector<int> Y(8), Y1(8);
   Y = {0,1,0,0,0,0,0,0};
   Y1 = {0,130,0,0,0,0,0,0};
   //std::vector<ampar_gillespie_class> ampars(10,ampar_gillespie_class(4500,Y));
   //std::vector<ampar_gillespie_class> ampars {ampar_gillespie_class(45,Y), ampar_gillespie_class(4500,Y)};
   int n_ampars = 130;// number of individual AMPARs
      ampar_gillespie_class ampar(Y1);        // object construction
      std::vector<ampar_gillespie_class> ampars;   // object construction
      for(int i=0; i<n_ampars; i++){
         //Y[1] = Y[1]-(1);
         ampars.push_back(ampar_gillespie_class(Y));
      }
      double dt = 1E-06;
      double t = dt;
      double tmax = 2;
      std::cout << t << "  ";
      for(int i=0; i < n_ampars; i++){
         std::cout << ampars[i].X[7] << " ";
      }
      std::cout << ampar.X[7] << " ";// AMPAR open
      std::cout << ampar.X[0] << " ";// glutamate concentration
      std::cout << std::endl;
      while(t <= tmax){
         std::cout << t << " ";
         if ((t >= 0.2)) {
            ampar.X[0] = glu_conc(t,0.2);
            for(int i=0; i < n_ampars; i++){
            ampars[i].X[0] = glu_conc(t,0.2);
            }
         }
     // else if ((t >= 0.5) && ( t < (0.5 + dt)) ){
     //    ampar.X[0] = 1000;
     //    for(int i=0; i < n_ampars; i++){
     //    ampars[i].X[0] = 20;
     //    }
     // }
     // else if ((t >= 1.5) && ( t < (1.5 + dt)) ){
     //    ampar.X[0] = 1000;
     //    for(int i=0; i < n_ampars; i++){
     //    ampars[i].X[0] = 20;
     //    }
     // }
     //    else {
     //       ampar.X[0] = 0;
     //       for(int i=0; i < n_ampars; i++){
     //       ampars[i].X[0] = 0;
     //       }
     //    }
         gillespie(ampar,dt);
         for(int i=0; i < n_ampars; i++){
            gillespie(ampars[i],dt);
            std::cout << ampars[i].X[7] << " ";
         }
      std::cout << ampar.X[7] << " ";
      std::cout << ampar.X[0] << " ";
      std::cout << std::endl;
      t+=dt;
   }

}
