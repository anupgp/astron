#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

#include <stl_vector_operation_functions.hpp>
#include <gillespie_class.hpp>
#include <ca_sensor_gillespie_class.hpp>

//Function that computes Glutamate profile over time in the space just above the AMPARs
int ca_conc(double t, double delay)
{
  double aa = 1.0;// starting value //300
  double bb = 2.51; // how log the starting value
  double cc = 100E-06;//decay time
  double dd = 1.0;//final settle value
  double ans = dd + ( (aa - dd) / (1 + (std::pow( (std::abs(t - delay) / cc), bb) ) ) );
  return(round(ans));
}

int main(int argc, char *argv[])
{
   //-------------------------------------
   std::string filename;         // Output filename variable
   // decode arguments passed
   if (argc < 2){
      filename = argv[0];
      std::cout << "No filename prefix provided" << std::endl;
      filename = filename.substr(2,filename.length()-2) + "_run";
   }
   else{
      filename = std::string(argv[1]);
   }
   //std::string filename = ("main_current.out");
   std::ofstream fout(filename);
   if (!fout){
      std::cout << "Error opening file " << filename << "\n";
      return (0);
   }
   std::cout << "File = " << filename << std::endl;
   //-------------------------------------
   const double delay = 5E-03;
   const double dt = 1E-05;
   const double tmax = 0.4 ;
   //-------------------------------------
   const int n_ca_sensors = 1;                           // number of individual Ca-sensors/vesicles
   const int n_states_ca_sensor=21;                      // number of Ca-sensor states
   std::vector<int> X_cas(n_states_ca_sensor);              // State vector for ca_sensor initialization in state X0Y0;
   for(int i=0;i<n_states_ca_sensor; i++){
      X_cas[i] = 0;
   };
   X_cas[0] = 7;
   std::vector<ca_sensor_gillespie_class> ca_sensors;    // ca_sensor object construction
   for(int i=0; i<n_ca_sensors; i++){
      ca_sensors.push_back(ca_sensor_gillespie_class(X_cas)); // Loads state to each ca_sensor
   }
   //-------------------------------------
   const int n_param_out = 3 + (n_ca_sensors * 21) + 4;
   //const int n_param_out = 3 + () + 3;
   std::vector< double > Y(n_param_out);                           // Ouput vector
   //-------------------------------------
   double t = 0.0;
   while(t <= tmax){
     //std::cout << " t = " << t << " delay = " << delay << std::endl;
     ca_sensor_gillespie_class::conCaIn = 1;//ca_conc(t,delay);
      for(int i=0; i<n_ca_sensors; i++){
         gillespie(ca_sensors[i],t,dt);
      }
      Y[0] = (ca_sensor_gillespie_class::time);
      Y[1] = (ca_sensor_gillespie_class::conCaIn);
      Y[2] = (ca_sensor_gillespie_class::relFlag);

      int k = 3;
      for(int i = 0; i < n_ca_sensors; i++){
         for(int j = 0; j < ca_sensors[i].X.size(); j++){
           Y[k++] = ca_sensors[i].X[j];
         }
      }
      Y[Y.size() - 4] = ca_sensor_gillespie_class::sponRelcount;
      Y[Y.size() - 3] = ca_sensor_gillespie_class::synRelcount;
      Y[Y.size() - 2] = ca_sensor_gillespie_class::asynRelcount;
      Y[Y.size() - 1] = ca_sensor_gillespie_class::totalRelcount;
      //std::cout << "Y = " << Y << std::endl;
      fout << Y << std::endl;
      //std::cin.get();
      t   = t + dt;
    }
   fout.close();
   return(0);
}

