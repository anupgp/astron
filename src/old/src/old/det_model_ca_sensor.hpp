#ifndef DET_MODEL_CALCIUM_SENSOR_HPP_INCLUDED
#define DET_MODEL_CALCIUM_SENSOR_HPP_INCLUDED

#include <vector>
#include <iostream>
#include <cmath>

#include "physical_constants.hpp"
#include "utility_functions.hpp"

namespace consts=astron::phy_const;

//Units: SI

class DET_MODEL_CALCIUM_SENSOR
{
private:

  /* Parameters: Sudhof model */
  //const double A = 1.53E8;         // Units = M^-1 s^-1
  //const double B = 5.8E03;	     // Units = s^-1
  //const double S = 2.94E06;	     // Units = M^-1 * s^-1
  //const double D = 130;	     // Units = s^-1
  //const double b = 0.25;           // Units = dimentionless
  //
  //const double Gspon = 0.417E-3;   // Units = s^-1
  //const double Gsyn = 6000.0;	     // Units = s^-1; 
  //const double Gasyn = 6000.0 ;    // Units = s^-1

  //const double refract = 0.0;

  /* Paramters: Suhita model */
  // -------------------------------------------
  const double A = 1.91E8;         // Units = M^-1 s^-1
  const double B = 2.32E03;	     // Units = s^-1
  const double S = 3.68E06;	     // Units = M^-1 * s^-1
  const double D = 13;	     // Units = s^-1
  const double b = 0.25;           // Units = dimentionless

  const double Gspon = 0.417E-3;   // Units = s^-1
  const double Gsyn = 2000.0;	     // Units = s^-1; 
  const double Gasyn = 50.0 ;	     // Units = s^-1
  
  const double Gref = 1/6.34E-03;

  // --------------------------------------------

  double spon_rate = 0.0;
  double syn_rate = 0.0;
  double asyn_rate = 0.0;
  double total_rate = 0.0;

  double spon_num_cum = 0.0;
  double syn_num_cum = 0.0;
  double asyn_num_cum = 0.0;
  double total_num_cum = 0.0;

  bool flag = 0;
  int prev_vesicle_num = 0;

public:

  std::vector <double> X;
  double volume = 0.0;    // Volume of the spherical bouton
  
  /* CALCIUM_SENSOR class explicit constructor */
  DET_MODEL_CALCIUM_SENSOR( std::vector<double> X_ = {0,0,0,0,0,0,0}, double volume_ = 1E-18): volume(volume_),X(X_)
  {
  };
  //------------------ Function declarations
  void reset(void);
  void update(double simtime, double dt);
  std::vector<double> get_rel_rates(void);
  std::vector<double> get_num_vesciles(void);
  double get_Pr();
  template <class State, class Deriv >
  void operator() ( const State &x, Deriv &dxdt , const double  t );
};
void DET_MODEL_CALCIUM_SENSOR::reset(void)
{
  spon_rate = 0.0;
  syn_rate = 0.0;
  asyn_rate = 0.0;
  total_rate = 0.0;

  spon_num_cum = 0;
  syn_num_cum = 0;
  asyn_num_cum = 0;
  total_num_cum = 0;

  flag = 0;
  prev_vesicle_num = 0;

}

std::vector<double> DET_MODEL_CALCIUM_SENSOR::get_rel_rates(void)
{
  std::vector<double> rels = {spon_rate, syn_rate, asyn_rate, total_rate};
  return (rels);
}

double DET_MODEL_CALCIUM_SENSOR::get_Pr(void)
{
  return(0);
}

std::vector<double> DET_MODEL_CALCIUM_SENSOR::get_num_vesciles(void)
{
  std::vector<double> numves = {spon_num_cum, syn_num_cum, asyn_num_cum, total_num_cum, double(flag) };
  //std::cout << numTotD << " " << numTotI << std::endl;  
  return (numves);
}

void DET_MODEL_CALCIUM_SENSOR::update(double simtime, double dt)
{

  spon_rate = X[1]*Gspon*(1E-03) * consts::Av * volume *1000; // [spon.rel.rate]
  syn_rate = (X[6]+X[12]+X[18]) * Gsyn*(1E-03) * consts::Av * volume * 1000; // [syn.rel.rate]
  asyn_rate = (X[13]+X[14]+X[15]+X[16]+X[17]+X[18])*Gasyn * (1E-03) * consts::Av * volume * 1000; // [asyn.rel.rate]
  total_rate = spon_rate + syn_rate + asyn_rate;      

  spon_num_cum = spon_num_cum + ( spon_rate*(dt/1E-03) );
  syn_num_cum = syn_num_cum + ( syn_rate*(dt/1E-03) );
  asyn_num_cum = asyn_num_cum + ( asyn_rate*(dt/1E-03) );
  total_num_cum = spon_num_cum + syn_num_cum + asyn_num_cum;

  int curr_vesicle_num = int(std::floor(total_num_cum));

  if( curr_vesicle_num > prev_vesicle_num){
    prev_vesicle_num = curr_vesicle_num;
    
    flag = 1;
    
    X[19] = X[1];
    X[20] = X[6];
    X[21] = X[12];
    X[22] = X[13];
    X[23] = X[14];
    X[24] = X[15];
    X[25] = X[16];
    X[26] = X[17];
    X[27] = X[18];
    
    X[1] = 0;
    X[6] = 0;
    X[12] = 0;
    X[13] = 0;
    X[14] = 0;
    X[15] = 0;
    X[16] = 0;
    X[17] = 0;
    X[18] = 0;
  }
  else{
    flag = 0;
  }

};

//------- CALCIUM_SENSOR class ODE Function
template <class State, class Deriv >
void DET_MODEL_CALCIUM_SENSOR::operator() ( const State &x, Deriv &dxdt, const double t )
{
  dxdt[0] = (-x[1]*5*A*x[0]) + (x[2]*B) + (-x[1]*2*S*x[0]) + (x[7]*D)
    + (-x[2]*4*A*x[0]) + (x[3]*2*B*b) + (-x[2]*2*S*x[0]) + (x[8]*D) + (x[2]*B) + (-x[1]*5*A*x[0])
    + (-x[3]*3*A*x[0]) + (x[4]*3*B*b*b) + (-x[3]*2*S*x[0]) + (x[9]*D) + (x[3]*2*B*b) + (-x[2]*4*A*x[0])
    + (-x[4]*2*A*x[0]) + (x[5]*4*B*b*b*b) + (-x[4]*2*S*x[0]) + (x[10]*D) + (x[4]*3*B*b*b) + (-x[3]*3*A*x[0])
    + (-x[5]*1*A*x[0]) + (x[6]*5*B*b*b*b*b) + (-x[5]*2*S*x[0]) + (x[11]*D) + (x[5]*4*B*b*b*b) + (-x[4]*2*A*x[0])
    + (-x[6]*2*S*x[0]) + (x[12]*D) + (x[6]*5*B*b*b*b*b) + (-x[5]*A*x[0])

    + (-x[7]*5*A*x[0]) + (x[8]*B) + (-x[7]*S*x[0]) + (x[13]*2*b*D) + (x[7]*D) + (-x[1]*2*S*x[0])
    + (-x[8]*4*A*x[0]) + (x[9]*2*B*b) + (-x[8]*S*x[0]) + (x[14]*2*b*D) + (x[8]*B) + (-x[7]*5*A*x[0]) + (x[8]*D) + (-x[2]*2*S*x[0])
    + (-x[9]*3*A*x[0]) + (x[10]*3*B*b*b) + (-x[9]*S*x[0]) + (x[15]*2*b*D) + (x[9]*2*B*b) + (-x[8]*4*A*x[0]) + (x[9]*D) + (-x[3]*2*S*x[0])
    + (-x[10]*2*A*x[0]) + (x[11]*4*B*b*b*b) + (-x[10]*S*x[0]) + (x[16]*2*b*D) + (x[10]*3*B*b*b) + (-x[9]*3*A*x[0]) + (x[10]*D) + (-x[4]*2*S*x[0])
    + (-x[11]*1*A*x[0]) + (x[12]*5*B*b*b*b*b) + (-x[11]*S*x[0]) + (x[17]*2*b*D) + (x[11]*4*B*b*b*b) + (-x[10]*2*A*x[0]) + (x[11]*D) + (-x[5]*2*S*x[0])
    + (-x[12]*S*x[0]) + (x[18]*2*b*D) + (x[12]*5*B*b*b*b*b) + (-x[11]*A*x[0]) + (x[12]*D) + (-x[6]*2*S*x[0])

    + (-x[13]*5*A*x[0]) + (x[14]*B) + (x[13]*2*b*D) + (-x[7]*S*x[0])
    + (-x[14]*4*A*x[0]) + (x[15]*2*B*b) + (x[14]*2*b*D) + (-x[8]*S*x[0]) + (x[14]*B) + (-x[13]*5*A*x[0])
    + (-x[15]*3*A*x[0]) + (x[16]*3*B*b*b) + (x[15]*2*b*D) + (-x[9]*S*x[0]) + (x[15]*2*b*B) + (-x[14]*4*A*x[0])
    + (-x[16]*2*A*x[0]) + (x[17]*4*B*b*b*b) + (x[16]*2*b*D) + (-x[10]*S*x[0]) + (x[16]*3*B*b*b) + (-x[15]*3*A*x[0])
    + (-x[17]*1*A*x[0]) + (x[18]*5*B*b*b*b*b) + (x[17]*2*b*D) + (-x[11]*S*x[0]) + (x[17]*4*B*b*b*b) + (-x[16]*2*A*x[0])
    + (x[18]*5*B*b*b*b*b) + (-x[17]*A*x[0]) + (x[18]*2*b*D) + (-x[12]*S*x[0]);	//d[Ca]/dt]

  dxdt[1] = (-x[1]*5*A*x[0]) + (x[2]*B) + (-x[1]*2*S*x[0]) + (x[7]*D) + (-x[1]*Gspon) + (x[19]*Gref);      /* d[X0Y0]/dt */
  dxdt[2] = (-x[2]*4*A*x[0]) + (x[3]*2*B*b) + (-x[2]*2*S*x[0]) + (x[8]*D) + (-x[2]*B) + (x[1]*5*A*x[0]);      /* d[X1Y0]/dt */
  dxdt[3] = (-x[3]*3*A*x[0]) + (x[4]*3*B*b*b) + (-x[3]*2*S*x[0]) + (x[9]*D) + (-x[3]*2*B*b) + (x[2]*4*A*x[0]);      /* d[X2Y0]/dt */
  dxdt[4] = (-x[4]*2*A*x[0]) + (x[5]*4*B*b*b*b) + (-x[4]*2*S*x[0]) + (x[10]*D) + (-x[4]*3*B*b*b) + (x[3]*3*A*x[0]);      /* d[X3Y0]/dt */
  dxdt[5] = (-x[5]*1*A*x[0]) + (x[6]*5*B*b*b*b*b) + (-x[5]*2*S*x[0]) + (x[11]*D) + (-x[5]*4*B*b*b*b) + (x[4]*2*A*x[0]);      /* d[X4Y0]/dt */
  dxdt[6] = (-x[6]*2*S*x[0]) + (x[12]*D) + (-x[6]*5*B*b*b*b*b) + (x[5]*A*x[0]) + (-x[6]*Gsyn)  + (x[20]*Gref);      /* d[X5Y0]/dt */

  dxdt[7] = (-x[7]*5*A*x[0]) + (x[8]*B) + (-x[7]*S*x[0]) + (x[13]*2*b*D) + (-x[7]*D) + (x[1]*2*S*x[0]);      /* d[X0Y1]/dt */
  dxdt[8] = (-x[8]*4*A*x[0]) + (x[9]*2*B*b) + (-x[8]*S*x[0]) + (x[14]*2*b*D) + (-x[8]*B) + (x[7]*5*A*x[0]) + (-x[8]*D) + (x[2]*2*S*x[0]);      /* d[X1Y1]/dt */
  dxdt[9] = (-x[9]*3*A*x[0]) + (x[10]*3*B*b*b) + (-x[9]*S*x[0]) + (x[15]*2*b*D) + (-x[9]*2*B*b) + (x[8]*4*A*x[0]) + (-x[9]*D) + (x[3]*2*S*x[0]);/* d[X2Y1]/dt */
  dxdt[10] = (-x[10]*2*A*x[0]) + (x[11]*4*B*b*b*b) + (-x[10]*S*x[0]) + (x[16]*2*b*D) + (-x[10]*3*B*b*b) + (x[9]*3*A*x[0]) + (-x[10]*D) + (x[4]*2*S*x[0]); /* d[X3Y1]/dt */
  dxdt[11] = (-x[11]*1*A*x[0]) + (x[12]*5*B*b*b*b*b) + (-x[11]*S*x[0]) + (x[17]*2*b*D) + (-x[11]*4*B*b*b*b) + (x[10]*2*A*x[0]) + (-x[11]*D) + (x[5]*2*S*x[0]); /* d[X4Y1]/dt */
  dxdt[12] = (-x[12]*S*x[0]) + (x[18]*2*b*D) + (-x[12]*5*B*b*b*b*b) + (x[11]*A*x[0]) + (-x[12]*D) + (x[6]*2*S*x[0]) + (-x[12]*Gsyn) + (x[21]*Gref); // d[X5Y1]/dt
  
  dxdt[13] = (-x[13]*5*A*x[0]) + (x[14]*B) + (-x[13]*2*b*D) + (x[7]*S*x[0]) + (-x[13]*Gasyn) + (x[22]*Gref); // d[X0Y2]/dt
  dxdt[14] = (-x[14]*4*A*x[0]) + (x[15]*2*B*b) + (-x[14]*2*b*D) + (x[8]*S*x[0]) + (-x[14]*B) + (x[13]*5*A*x[0]) + (-x[14]*Gasyn) + (x[23]*Gref); // d[X1Y2]/dt
  dxdt[15] = (-x[15]*3*A*x[0]) + (x[16]*3*B*b*b) + (-x[15]*2*b*D) + (x[9]*S*x[0]) + (-x[15]*2*b*B) + (x[14]*4*A*x[0]) + (-x[15]*Gasyn) + (x[24]*Gref); // d[X2Y2]/dt
  dxdt[16] = (-x[16]*2*A*x[0]) + (x[17]*4*B*b*b*b) + (-x[16]*2*b*D) + (x[10]*S*x[0]) + (-x[16]*3*B*b*b) + (x[15]*3*A*x[0]) + (-x[16]*Gasyn) + (x[25]*Gref);    /* d[X3Y2]/dt */
  dxdt[17] = (-x[17]*1*A*x[0]) + (x[18]*5*B*b*b*b*b) + (-x[17]*2*b*D) + (x[11]*S*x[0]) + (-x[17]*4*B*b*b*b) + (x[16]*2*A*x[0]) + (-x[17]*Gasyn) + (x[26]*Gref); /* d[X4Y2]/dt */
  dxdt[18] = (-x[18]*5*B*b*b*b*b) + (x[17]*A*x[0]) + (-x[18]*2*b*D) + (x[12]*S*x[0]) + (-x[18]*Gsyn) + (-x[18]*Gasyn) + (x[27]*Gref);      /* d[X5Y2]/dt */
  
  dxdt[19] =  (-x[19]*Gref);	// d[X0Y0C]/dt
  dxdt[20] =  (-x[20]*Gref);	// d[X5Y0C]/dt
  dxdt[21] =  (-x[21]*Gref);	// d[X5Y1C]/dt
  dxdt[22] =  (-x[22]*Gref);	// d[X0Y2C]/dt
  dxdt[23] =  (-x[23]*Gref);	// d[X1Y2C]/dt
  dxdt[24] =  (-x[24]*Gref);	// d[X2Y2C]/dt
  dxdt[25] =  (-x[25]*Gref);	// d[X3Y2C]/dt
  dxdt[26] =  (-x[26]*Gref);	// d[X4Y2C]/dt
  dxdt[27] =  (-x[27]*Gref);	// d[X5Y2C]/dt

};
#endif // DET_MODEL_CALCIUM_SENSOR_MODEL_HPP_INCLUDED
