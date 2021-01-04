#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "hh_post_det_model.hpp"
//#include "vgcc_det_model.hpp"
//#include "pmca_det_model.hpp"
#include "ca_sensor_gillespie_class.hpp"
#include "vgcc_gillespie_class.hpp"
#include "pmca_gillespie_class.hpp"

#include "gillespie_class.hpp"
#include "physical_constants.hpp"
#include "stl_vector_operation_functions.hpp"


#include <boost/numeric/odeint.hpp> /*  Specifying the file within < > lets c++ search for it at -I path  */
#include <boost/range/iterator_range.hpp>
#include <boost/range/iterator.hpp>

namespace bno=boost::numeric::odeint;
namespace gill=astron::gillespie;
namespace g_vgcc=gill::vgcc;
namespace g_pmca=gill::pmca;
namespace consts=astron::phy_const;

typedef std::vector< double > state_type;
typedef state_type::iterator state_type_it;
typedef bno::runge_kutta4 < state_type > rk4_stepper_type;

//-----------------
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
  std::ofstream fout(filename);
  if (!fout){
    std::cout << "Error opening file " << filename << "\n";
    return (0);
  }
  std::cout << "File = " << filename << std::endl;
  // ----------------------------------
  const double vol_pre = 1E-18;	// Volume of whole presynaptic terminal
  const double vol_pmca = 1E-18;
  const double vol_vgcc = 1E-18;

  double conCaIn = 100E-09;	// Baseline Calcium concentration
  int numCaIn = conCaIn * consts::Av * vol_pre * 1000; // Molarity in Liters 1L = 1000 * 10^-6 meter^3
  
   
  // Initialize deterministic objects
  rk4_stepper_type stepper;
  
  HH_POST hh_post(500E-12);                             // constructs an hh_pre object with 25 micron radius
  state_type X_hh_post = {0,0,0,-80E-03};                    //{m,h,n,V}

  //PMCA pmca(100E-09);                                   // constructs an PMCA object with 100 nM calcium concentration (intracellular)
  //state_type X_pmca = {100E-09, 17E-03, 0, 0};          //{conCaIn, PMCA0, PMCA1, PMCA2}

  //VGCC vgcc;                                            // constructs VGCCs
  //state_type X_vgcc = {50, 0, 0, 0, 0};                //{C0, C1, C2, C3, O}
  //-------------------------------------

  // Initialize MCMC: PMCA
  const int n_pmca = 1;
  const int n_states_pmca = 5; 	// [NCa, Leak, PMCA0, PMCA1, PMCA2]
  std::vector<int> X_pmca = {62,1530,1530,0,0}; // [NCa, NLeak, NPMCA0, PMCA1, PMCA2]
  std::vector<g_pmca::pmca_gillespie_class> gpmca;
  for(int i=0; i <n_pmca; i++){
    gpmca.push_back(g_pmca::pmca_gillespie_class(1000,X_pmca));
  }
  // Initialize MCMC: VGCC 
  const int n_vgcc = 1;
  const int n_states_vgcc = 5;	// [C0 C1 C2 C3 O]
  std::vector<int> X_vgcc = {50,0,0,0,0};
  std::vector<g_vgcc::vgcc_gillespie_class> gvgcc;
  for(int i=0; i <n_vgcc; i++){
    gvgcc.push_back(g_vgcc::vgcc_gillespie_class(vol_vgcc,X_vgcc));
  }
  // Initialize MCMC: ca_sensors
  //const int n_ca_sensors = 1; // number of individual Ca-sensors/vesicles
  //const int n_states_ca_sensor=21; // number of Ca-sensor states
  //std::vector<int> X_cas(n_states_ca_sensor); // State vector for ca_sensor initialization in state X0Y0;
 //for(int i=0;i<n_states_ca_sensor; i++){
 //  X_cas[i] = 0;
 //};
 //X_cas[0] = 7;
 //std::vector<gill::ca_sensor_gillespie_class> ca_sensors;    // ca_sensor object construction
 //for(int i=0; i<n_ca_sensors; i++){
 //  ca_sensors.push_back(gill::ca_sensor_gillespie_class(X_cas)); // Loads state to each ca_sensor
 //}
 ////-------------------------------------
 ////                      time(1) IExt(1) X_hh_post(4) vgcc(5) pmca(4) conCaIn(1) ca_sensor(21) spon_rel(1) syn_rel(1) asyn_rel(1) total_rel(1) = 
 //const int n_param_out = (1) + 2+ 21; 
 //std::vector< double > Y(11);                           // Ouput vector
  //--------------------------------------
  double t = 0.0;
  const double dt = 10E-06;
  const double tmax = 100E-03;
  // -------------------------------------
  
  while (t <= tmax){
    //std::cout << "conCaIn = " << conCaIn << " numCaIn = " << numCaIn << std::endl;

    if( (t > 22E-03) && ( t < (24E-03 )) ){
      hh_post.IExt = 20E-02;	// External current to trigger presynaptic spike 
    }
    if( (t >= 24E-03) && ( t <= (tmax )) ){
      hh_post.IExt = 0;
    }
    stepper.do_step( hh_post, X_hh_post, t, dt); // update voltage

    //gpmca[0].X[0] = numCaIn;     
    for(int i=0; i<n_pmca; i++){
      gillespie(gpmca[i],t,dt);
    }
    numCaIn = gpmca[0].X[0]; //abs(g_pmca::pmca_gillespie_class::numCaIn);
    conCaIn = ((numCaIn) / (consts::Av * vol_pre * 1000));

    g_vgcc::vgcc_gillespie_class::V = X_hh_post[3];
    g_vgcc::vgcc_gillespie_class::conCaIn = conCaIn;
    for(int i=0; i<n_vgcc; i++){
      gillespie(gvgcc[i],t,dt);
    }
    numCaIn = numCaIn + abs(g_vgcc::vgcc_gillespie_class::numCaFlux);
    conCaIn = numCaIn / (consts::Av * vol_pre * 1000);

    fout << t << " " << X_hh_post << " " << gpmca[0].X << " " << gvgcc[0].X << " " << numCaIn << " " << conCaIn << std::endl;
    //std::cout << t << " " << gpmca[0].X << std::endl;
    //std::cin.get();
    t = t + dt;
  }
  fout.close();
  return 0;
}

// Extra codes
  // g_pmca::pmca_gillespie_class::numCaIn = numCaIn;
//g_vgcc::vgcc_gillespie_class::conCaIn = conCaIn;		   // Set vgcc.conCaIn
    //g_vgcc::vgcc_gillespie_class::V = X_hh_post[3];		   // Set vgcc.V
   // for(int i=0; i<n_vgcc; i++){
   //   gillespie(gvgcc[i],t,dt);
   // }
    //conCaIn = conCaIn + (g_pmca::pmca_gillespie_class::numCaIn / (consts::Av * vol_pmca) ); // update conCaIn
    
    //vgcc.V = X_hh_post[3];	// Feed presynaptic voltage to VGCC
    //stepper.do_step( vgcc, X_vgcc, t,  dt); // update vgcc
    //vgcc.update(dt, X_vgcc[4]);
    //X_pmca[0]  = conCaIn; // update conCaIn of PMCA buffers
    //stepper.do_step( pmca, X_pmca, t, dt);
    //conCaIn = X_pmca[0];	// update conCaIn
    //numCaIn_ca_sensor = round(vgcc.numCaIn/10) + 1;//und((vgcc.numCaIn - 59) / 60 );//round((vgcc.conCaIn - 59) / 6 );
    //gill::ca_sensor_gillespie_class::conCaIn = numCaIn_ca_sensor;
    //for(int i=0; i<n_ca_sensors; i++){
    //   gillespie(ca_sensors[i],t,dt);
    //}

   //Y[7] = gill::ca_sensor_gillespie_class::sponRelcount;
   //Y[8] = gill::ca_sensor_gillespie_class::synRelcount;
   //Y[9] = gill::ca_sensor_gillespie_class::asynRelcount;
   //Y[10] = gill::ca_sensor_gillespie_class::totalRelcount;
