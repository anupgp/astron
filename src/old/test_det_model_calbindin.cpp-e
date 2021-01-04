#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

#include "det_model_calbindin.hpp"
#include "det_model_pmca.hpp"
#include "det_model_vgcc.hpp"
#include "det_model_hh_post.hpp"
#include "det_model_ca_sensor.hpp"
#include "physical_constants.hpp"
#include "stl_vector_operation_functions.hpp"
#include "stoch_odeint_explicit_euler.hpp"

#include <boost/numeric/odeint.hpp> /*  Specifying the file within < > lets c++ search for it at -I path  */
#include <boost/range/iterator_range.hpp>
#include <boost/range/iterator.hpp>

namespace bno=boost::numeric::odeint;
namespace consts=astron::phy_const;
namespace myode=stoch_odeint_explicit_euler;

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
  double conCaIn = 100E-09;
  if (argc >=3 ){
    conCaIn = std::stod(argv[2]);
  }
  else{
    std::cout << "No 3rd argument provided" << std::endl;
  }
  // ----------------------------------
  // Initialize deterministic objects
  const double volume = 1E-18;
  const int nVesicles = 7;

  rk4_stepper_type stepper_cb, stepper_pmca, stepper_hhp, stepper_vgcc, stepper_sensor;

 

  state_type Xpmca = {45E-06,1530/(consts::Av * 1000 * volume),0,0,2E-03};	       //1530
  state_type Xcb = {45E-06,40E-06,0,0,0,0,0,0,0}; //45E-06i
  state_type Xhhp = {0,1,0,-80.0E-03};
  state_type Xvgcc = {1,0,0,0,0};
  state_type Xsensor = {0, nVesicles /(consts::Av * 1000 * volume) ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0 };

  DET_MODEL_CALBINDIN det_cb(Xcb);
  DET_MODEL_PMCA det_pmca(Xpmca);
  DET_MODEL_HH_POST det_hhp(Xhhp);
  DET_MODEL_VGCC det_vgcc(Xvgcc);
  DET_MODEL_CALCIUM_SENSOR det_sensor(Xsensor,volume);
  //--------------------------------------
  myode::STOCH_ODEINT_EXPLICIT_EULER< state_type > odeint_euler;
  std::vector<int> s = {0,0,0,1};
  //--------------------------------------
  double t = 0.0;
  const double dt = 15E-06;
  const double tmax = 30;
  // ------------------------------------
  std::vector<double> rels(4);
  conCaIn = 45000E-09;		// 26400E-09
  double conCaStep = 10E-09;
  double conCaMax = 10E-03;
  double relMax = 0.0;
  double relMaxtime = 0.0;
  double V1 = -80E-03;
  double V2 = -80E-03;
  double Vb = -80E-03;
  double Vm = Vb;

  double Vstep = 10E-03;
  //-------------------------------------
  //while (V1 <= 120E-03){
  //t = 0.0;
  //Vm = Vb;
  //det_vgcc.X[0] = 1;
  for(int i=0; i<det_sensor.X.size(); i++){
    det_sensor.X[i] = 0.0;
  }
  det_sensor.X[0] = conCaIn;
  det_sensor.X[1] = nVesicles /(consts::Av * 1000 * volume);

  det_sensor.reset();
    
  while (t <= tmax){
    //det_pmca.X[0] = conCaIn;
    //det_pmca.X[4] = 2E-03;
    stepper_pmca.do_step( det_pmca, det_pmca.X, t, dt);
    //conCaIn  = det_pmca.X[0];
    //det_cb.X[0] = conCaIn;
    stepper_cb.do_step( det_cb, det_cb.X, t, dt);
    //det_cb.set_boundary_cond();
    //conCaIn = det_cb.X[0];
    //deint_euler.do_step( det_hhp,det_hhp.X,s,t,dt);
    stepper_hhp.do_step( det_hhp,det_hhp.X, t, dt);
    //det_vgcc.V = det_hhp.X[3];
    stepper_vgcc.do_step(det_vgcc,det_vgcc.X, t, dt);
    //---------------------------
    if( (t > 15000E-03) && ( t < (15004E-03 )) ){
      det_hhp.IExt = 20E-02;	// External current to trigger presynaptic spike 
      //Vm = V1;
    }
    if( (t > 15004E-03) && ( t < (18000E-03 )) ){
      det_hhp.IExt = 00E-02;	// External current to trigger presynaptic spike 
      //Vm = V1;
    }
    if( (t > 18000E-03) && ( t < (18004E-03 )) ){
      det_hhp.IExt = 20E-02;	// External current to trigger presynaptic spike 
      //Vm = V1;
    }
    if( (t >= 18004E-03) && ( t <= (tmax )) ){
      //if( (t >= 8E-03) && ( t <= (tmax )) ){
      det_hhp.IExt = 0;
      //Vm = Vb;
    }
    // copy values here
    det.
    
    //det_vgcc.conCaIn = conCaIn;
    //det_vgcc.update_variables(dt);
    //conCaIn = det_vgcc.conCaIn;
    //--------------------------
    //det_sensor.X[0] = conCaIn;
    //stepper_sensor.do_step(det_sensor, det_sensor.X,t,dt);
    //det_sensor.update(t,dt);
    //rels = det_sensor.get_rel_rates();
    //conCaIn = det_sensor.X[0];
    //if (rels[3] > relMax){
    //  relMax = rels[3];
    //  relMaxtime = t;
    //};
    //-------------------------
    //fout << t << " " << conCaIn << " " << det_sensor.get_rel_rates() << " " << det_sensor.get_num_vesciles() << std::endl;
    fout << t << " " << conCaIn << " " << det_pmca.X << " " << det_cb.X << " " << det_hhp.X << " " << det_vgcc.X << " " << det_vgcc.I_Ca << " " << std::endl;
    //std::cout << det_hhp.X << std::endl;
    //std::cin.get();
    t = t + dt;
  };
  //fout << conCaIn << " " << relMax  << " " << relMaxtime << " " << det_sensor.get_Pr() << std::endl;
  //std::cout << conCaIn << " " << relMax << " " << det_sensor.get_Pr() << std::endl;
  //conCaIn = conCaIn + conCaStep;
  //V1+=Vstep;
  //relMax = 0;
  //relMaxtime = 0.0;
  //};
  fout.close();
  return 0;
}
