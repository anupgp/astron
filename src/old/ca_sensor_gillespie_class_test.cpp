#include <iostream>
#include <cmath>
#include <vector>


#include "stl_vector_operation_functions.hpp"
#include "gillespie_class.hpp"
#include "ca_sensor_gillespie_class.hpp"

//Function that computes Glutamate profile over time in the space just above the AMPARs
double glu_conc(double t, double t0)
{
   double tt = t-t0;
   double aa = 10;//300
   double bb = 2;
   double cc = 1;//185E-06;
   double dd = 1;
   double delay = 2.0E-05;
   double out = dd + ( (aa-dd) / (1 + (std::pow( ((tt - delay) / cc), bb) ) ) );
   return(out);
}
int main(int argc, char** argv)
{
   const int n_states = 22;
   std::vector<int> S0;
   for(int i=0;i<n_states; i++){
      S0.push_back(0);
   }
   S0[1] = 1;
   //std::vector<ampar_gillespie_class> ampars(10,ampar_gillespie_class(4500,Y));
   //std::vector<ampar_gillespie_class> ampars {ampar_gillespie_class(45,Y), ampar_gillespie_class(4500,Y)};
   //int n_ca_sensors = 2;// number of individual AMPARs
   //   std::vector<ca_sensor_gillespie_class> ca_sensors;   // object construction
   ca_sensor_gillespie_class ca_sensor(S0);
    //  for(int i=0; i<n_ca_sensors; i++){
    //     //Y[1] = Y[1]-(1);
    //     ca_sensors.push_back(ca_sensor_gillespie_class(S0));
    //  }
   double dt = 10E-06;
   double t = 0.0;
   double tmax = 10;
   std::cout << std::endl;
   while(t <= tmax){
      if( (t >= (3*dt)) && (t < (tmax)) ) {
         ca_sensor_gillespie_class::conCaIn = glu_conc(t,0.1);
      }
      else {
         ca_sensor_gillespie_class::conCaIn = 0;
      }
      std::cout << t << " " << ca_sensor_gillespie_class::conCaIn << " ";
      for(int i=0; i < ca_sensor.X.size(); i++){
         std::cout << ca_sensor.X[i] << " " ;
      }
      gillespie(ca_sensor,t,dt);
      t = t + dt;
      std::cout << std::endl;
   }
   std::cout << t << " " << ca_sensor_gillespie_class::conCaIn << " ";
   for(int i=0; i < ca_sensor.X.size(); i++){
      std::cout << ca_sensor.X[i] << " " ;
   }
   std::cout << std::endl;
}
