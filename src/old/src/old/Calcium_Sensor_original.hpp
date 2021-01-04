/* Last Revised Date: 08_APRIL_2015 */
/* Lastest status: not checked   */
#ifndef CALCIUM_SENSOR_HPP_INCLUDED
#define CALCIUM_SENSOR_HPP_INCLUDED

#include <vector>
#include <iostream>
#include <cmath>

#include "data_types.hpp"
#include "physical_constants.hpp"
#include "global_variables.hpp"
#include "insilico/core.hpp"
#include "utility_functions.hpp"


//UNITS: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads

namespace consts=astron::phy_const;
namespace gvars=astron::global_vars;

class CALCIUM_SENSOR
{
public:
  // Stattic variables
  static double presenttime;
  static unsigned rk4count;

  static double spon_rate;
  static double syn_rate;
  static double asyn_rate;
  static double total_rate;

  static double spon_num_cum;
  static double syn_num_cum;
  static double asyn_num_cum;
  static double total_num_cum;

  static unsigned flag;
  static unsigned prev_vesicle_num;
  static unsigned curr_vesicle_num;

  // Static functions
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
  static void reset(void);
  static void update(state_type &variables, double t, unsigned index);
};
// Static variable initializations
double CALCIUM_SENSOR::presenttime = 0.0;
unsigned CALCIUM_SENSOR::rk4count = 0;

double CALCIUM_SENSOR::spon_rate = 0.0;
double CALCIUM_SENSOR::syn_rate = 0.0;
double CALCIUM_SENSOR::asyn_rate = 0.0;
double CALCIUM_SENSOR::total_rate = 0.0;

double CALCIUM_SENSOR::spon_num_cum = 0.0;
double CALCIUM_SENSOR::syn_num_cum = 0.0;
double CALCIUM_SENSOR::asyn_num_cum = 0.0;
double CALCIUM_SENSOR::total_num_cum = 0.0;

unsigned CALCIUM_SENSOR::flag = 0;
unsigned CALCIUM_SENSOR::prev_vesicle_num = 0;
unsigned CALCIUM_SENSOR::curr_vesicle_num = 0;


void CALCIUM_SENSOR::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{


  
// Get all variable indices
  unsigned Ca_Cyt_index = insilico::engine::neuron_index(index, "Ca_Cyt");
  
  unsigned H0L0_index = insilico::engine::neuron_index(index, "gluves_H0L0");
  unsigned H1L0_index = insilico::engine::neuron_index(index, "gluves_H1L0");
  unsigned H2L0_index = insilico::engine::neuron_index(index, "gluves_H2L0");
  unsigned H3L0_index = insilico::engine::neuron_index(index, "gluves_H3L0");  
  unsigned H4L0_index = insilico::engine::neuron_index(index, "gluves_H4L0");
  unsigned H5L0_index = insilico::engine::neuron_index(index, "gluves_H5L0");

  unsigned H0L1_index = insilico::engine::neuron_index(index, "gluves_H0L1");
  unsigned H1L1_index = insilico::engine::neuron_index(index, "gluves_H1L1");
  unsigned H2L1_index = insilico::engine::neuron_index(index, "gluves_H2L1");
  unsigned H3L1_index = insilico::engine::neuron_index(index, "gluves_H3L1");
  unsigned H4L1_index = insilico::engine::neuron_index(index, "gluves_H4L1");
  unsigned H5L1_index = insilico::engine::neuron_index(index, "gluves_H5L1");

  unsigned H0L2_index = insilico::engine::neuron_index(index, "gluves_H0L2");
  unsigned H1L2_index = insilico::engine::neuron_index(index, "gluves_H1L2");
  unsigned H2L2_index = insilico::engine::neuron_index(index, "gluves_H2L2");
  unsigned H3L2_index = insilico::engine::neuron_index(index, "gluves_H3L2");
  unsigned H4L2_index = insilico::engine::neuron_index(index, "gluves_H4L2");
  unsigned H5L2_index = insilico::engine::neuron_index(index, "gluves_H5L2");

  unsigned H0L0F_index = insilico::engine::neuron_index(index, "gluves_H0L0F");
  unsigned H5L0F_index = insilico::engine::neuron_index(index, "gluves_H5L0F");
  unsigned H5L1F_index = insilico::engine::neuron_index(index, "gluves_H5L1F");
  unsigned H0L2F_index = insilico::engine::neuron_index(index, "gluves_H0L2F");
  unsigned H1L2F_index = insilico::engine::neuron_index(index, "gluves_H1L2F");
  unsigned H2L2F_index = insilico::engine::neuron_index(index, "gluves_H2L2F");
  unsigned H3L2F_index = insilico::engine::neuron_index(index, "gluves_H3L2F");
  unsigned H4L2F_index = insilico::engine::neuron_index(index, "gluves_H4L2F");
  unsigned H5L2F_index = insilico::engine::neuron_index(index, "gluves_H5L2F");

  unsigned H0L0R_index = insilico::engine::neuron_index(index, "gluves_H0L0R");
  unsigned H5L0R_index = insilico::engine::neuron_index(index, "gluves_H5L0R");
  unsigned H5L1R_index = insilico::engine::neuron_index(index, "gluves_H5L1R");
  unsigned H0L2R_index = insilico::engine::neuron_index(index, "gluves_H0L2R");
  unsigned H1L2R_index = insilico::engine::neuron_index(index, "gluves_H1L2R");
  unsigned H2L2R_index = insilico::engine::neuron_index(index, "gluves_H2L2R");
  unsigned H3L2R_index = insilico::engine::neuron_index(index, "gluves_H3L2R");
  unsigned H4L2R_index = insilico::engine::neuron_index(index, "gluves_H4L2R");
  unsigned H5L2R_index = insilico::engine::neuron_index(index, "gluves_H5L2R");
 
  // Get all parameter values
  const double A = insilico::engine::neuron_value(index, "gluves_A");
  const double B = insilico::engine::neuron_value(index, "gluves_B");
  const double S = insilico::engine::neuron_value(index, "gluves_S");
  const double D = insilico::engine::neuron_value(index, "gluves_D");
  const double b = insilico::engine::neuron_value(index, "gluves_b");
  const double Gspon = insilico::engine::neuron_value(index, "gluves_Gspon");
  const double Gsyn = insilico::engine::neuron_value(index, "gluves_Gsyn");
  const double Gasyn = insilico::engine::neuron_value(index, "gluves_Gasyn");
  const double Kfast = insilico::engine::neuron_value(index, "gluves_Kfast");
  const double Kslow = insilico::engine::neuron_value(index, "gluves_Kslow");
  // Get all variable values
  double Ca_Cyt = variables[Ca_Cyt_index];
  
  double H0L0 = variables[H0L0_index];
  double H1L0 = variables[H1L0_index];
  double H2L0 = variables[H2L0_index];
  double H3L0 = variables[H3L0_index];  
  double H4L0 = variables[H4L0_index];
  double H5L0 = variables[H5L0_index];
			  	         
  double H0L1 = variables[H0L1_index];
  double H1L1 = variables[H1L1_index];
  double H2L1 = variables[H2L1_index];
  double H3L1 = variables[H3L1_index];
  double H4L1 = variables[H4L1_index];
  double H5L1 = variables[H5L1_index];

  double H0L2 = variables[H0L2_index];
  double H1L2 = variables[H1L2_index];
  double H2L2 = variables[H2L2_index];
  double H3L2 = variables[H3L2_index];
  double H4L2 = variables[H4L2_index];
  double H5L2 = variables[H5L2_index];

  double H0L0F = variables[H0L0F_index];
  double H5L0F = variables[H5L0F_index];
  double H5L1F = variables[H5L1F_index];
  double H0L2F = variables[H0L2F_index];
  double H1L2F = variables[H1L2F_index];
  double H2L2F = variables[H2L2F_index];
  double H3L2F = variables[H3L2F_index];
  double H4L2F = variables[H4L2F_index];
  double H5L2F = variables[H5L2F_index];

  double H0L0R = variables[H0L0R_index];
  double H5L0R = variables[H5L0R_index];
  double H5L1R = variables[H5L1R_index];
  double H0L2R = variables[H0L2R_index];
  double H1L2R = variables[H1L2R_index];
  double H2L2R = variables[H2L2R_index];
  double H3L2R = variables[H3L2R_index];
  double H4L2R = variables[H4L2R_index];
  double H5L2R = variables[H5L2R_index];   

  // --------------------------------------------

  dxdt[H0L0_index] = (-H0L0*5*A*Ca_Cyt) + (H1L0*B) + (-H0L0*2*S*Ca_Cyt) + (H0L1*D) + (-H0L0*Gspon) + (H0L0F*Kfast) + (H0L0R*Kslow)  + (H0L2R*Kslow)  + (H5L0R*Kslow) + (H5L1R*Kslow) 
    + (H1L2R*Kslow) + (H2L2R*Kslow) + (H3L2R*Kslow) + (H4L2R*Kslow) + (H5L2R*Kslow);      /* d[X0Y0]/dt */
  
  dxdt[H1L0_index] = (-H1L0*4*A*Ca_Cyt) + (H2L0*2*B*b) + (-H1L0*2*S*Ca_Cyt) + (H1L1*D) + (-H1L0*B) + (H0L0*5*A*Ca_Cyt);      /* d[X1Y0]/dt */
  dxdt[H2L0_index] = (-H2L0*3*A*Ca_Cyt) + (H3L0*3*B*b*b) + (-H2L0*2*S*Ca_Cyt) + (H2L1*D) + (-H2L0*2*B*b) + (H1L0*4*A*Ca_Cyt);      /* d[X2Y0]/dt */
  dxdt[H3L0_index] = (-H3L0*2*A*Ca_Cyt) + (H4L0*4*B*b*b*b) + (-H3L0*2*S*Ca_Cyt) + (H3L1*D) + (-H3L0*3*B*b*b) + (H2L0*3*A*Ca_Cyt);      /* d[X3Y0]/dt */
  dxdt[H4L0_index] = (-H4L0*1*A*Ca_Cyt) + (H5L0*5*B*b*b*b*b) + (-H4L0*2*S*Ca_Cyt) + (H4L1*D) + (-H4L0*4*B*b*b*b) + (H3L0*2*A*Ca_Cyt);      /* d[X4Y0]/dt */
  dxdt[H5L0_index] = (-H5L0*2*S*Ca_Cyt) + (H5L1*D) + (-H5L0*5*B*b*b*b*b) + (H4L0*A*Ca_Cyt) + (-H5L0*Gsyn)  + (H5L0F*Kfast);      /* d[X5Y0]/dt */

  dxdt[H0L1_index] = (-H0L1*5*A*Ca_Cyt) + (H1L1*B) + (-H0L1*S*Ca_Cyt) + (H0L2*2*b*D) + (-H0L1*D) + (H0L0*2*S*Ca_Cyt);      /* d[X0Y1]/dt */
  dxdt[H1L1_index] = (-H1L1*4*A*Ca_Cyt) + (H2L1*2*B*b) + (-H1L1*S*Ca_Cyt) + (H1L2*2*b*D) + (-H1L1*B) + (H0L1*5*A*Ca_Cyt) + (-H1L1*D) + (H1L0*2*S*Ca_Cyt);      /* d[X1Y1]/dt */
  dxdt[H2L1_index] = (-H2L1*3*A*Ca_Cyt) + (H3L1*3*B*b*b) + (-H2L1*S*Ca_Cyt) + (H2L2*2*b*D) + (-H2L1*2*B*b) + (H1L1*4*A*Ca_Cyt) + (-H2L1*D) + (H2L0*2*S*Ca_Cyt);/* d[X2Y1]/dt */
  dxdt[H3L1_index] = (-H3L1*2*A*Ca_Cyt) + (H4L1*4*B*b*b*b) + (-H3L1*S*Ca_Cyt) + (H3L2*2*b*D) + (-H3L1*3*B*b*b) + (H2L1*3*A*Ca_Cyt) + (-H3L1*D) + (H3L0*2*S*Ca_Cyt); /* d[X3Y1]/dt */
  dxdt[H4L1_index] = (-H4L1*1*A*Ca_Cyt) + (H5L1*5*B*b*b*b*b) + (-H4L1*S*Ca_Cyt) + (H4L2*2*b*D) + (-H4L1*4*B*b*b*b) + (H3L1*2*A*Ca_Cyt) + (-H4L1*D) + (H4L0*2*S*Ca_Cyt); /* d[H4Y1]/dt */
  dxdt[H5L1_index] = (-H5L1*S*Ca_Cyt) + (H5L2*2*b*D) + (-H5L1*5*B*b*b*b*b) + (H4L1*A*Ca_Cyt) + (-H5L1*D) + (H5L0*2*S*Ca_Cyt) + (-H5L1*Gsyn)  + (H5L1F*Kfast); // d[X5Y1]/dt
  
  dxdt[H0L2_index] = (-H0L2*5*A*Ca_Cyt) + (H1L2*B) + (-H0L2*2*b*D) + (H0L1*S*Ca_Cyt) + (-H0L2*Gasyn) +  (H0L2F*Kfast); // d[X0Y2]/dt
  dxdt[H1L2_index] = (-H1L2*4*A*Ca_Cyt) + (H2L2*2*B*b) + (-H1L2*2*b*D) + (H1L1*S*Ca_Cyt) + (-H1L2*B) + (H0L2*5*A*Ca_Cyt) + (-H1L2*Gasyn)  + (H1L2F*Kfast); // d[X1Y2]/dt
  dxdt[H2L2_index] = (-H2L2*3*A*Ca_Cyt) + (H3L2*3*B*b*b) + (-H2L2*2*b*D) + (H2L1*S*Ca_Cyt) + (-H2L2*2*b*B) + (H1L2*4*A*Ca_Cyt) + (-H2L2*Gasyn)  + (H2L2F*Kfast); // d[X2Y2]/dt
  dxdt[H3L2_index] = (-H3L2*2*A*Ca_Cyt) + (H4L2*4*B*b*b*b) + (-H3L2*2*b*D) + (H3L1*S*Ca_Cyt) + (-H3L2*3*B*b*b) + (H2L2*3*A*Ca_Cyt) + (-H3L2*Gasyn)  + (H3L2F*Kfast);    /* d[X3Y2]/dt */
  dxdt[H4L2_index] = (-H4L2*1*A*Ca_Cyt) + (H5L2*5*B*b*b*b*b) + (-H4L2*2*b*D) + (H4L1*S*Ca_Cyt) + (-H4L2*4*B*b*b*b) + (H3L2*2*A*Ca_Cyt) + (-H4L2*Gasyn)  + (H4L2F*Kfast); /* d[H4Y2]/dt */
  dxdt[H5L2_index] = (-H5L2*5*B*b*b*b*b) + (H4L2*A*Ca_Cyt) + (-H5L2*2*b*D) + (H5L1*S*Ca_Cyt) + (-H5L2*Gsyn) + (-H5L2*Gasyn)  + (H5L2F*Kfast);      /* d[X5Y2]/dt */
  
  dxdt[H0L0R_index] =  (H0L0*Gspon) + (-H0L0R*Kslow);	
  dxdt[H5L0R_index] =  (H5L0*Gsyn)  + (-H5L0R*Kslow);	
  dxdt[H5L1R_index] =  (H5L1*Gsyn)  + (-H5L1R*Kslow);
  dxdt[H0L2R_index] =  (H0L2*Gasyn) + (-H0L2R*Kslow);	
  dxdt[H1L2R_index] =  (H1L2*Gasyn) + (-H1L2R*Kslow);	
  dxdt[H2L2R_index] =  (H2L2*Gasyn) + (-H2L2R*Kslow);	
  dxdt[H3L2R_index] =  (H3L2*Gasyn) + (-H3L2R*Kslow);	
  dxdt[H4L2R_index] =  (H4L2*Gasyn) + (-H4L2R*Kslow);	
  dxdt[H5L2R_index] =  (H5L2*Gasyn) + (H5L2*Gsyn) + (-H5L2R*Kslow);	

  dxdt[H0L0F_index] =   (-H0L0F*Kfast);	
  dxdt[H5L0F_index] =   (-H5L0F*Kfast);	
  dxdt[H5L1F_index] =   (-H5L1F*Kfast);	
  dxdt[H0L2F_index] =   (-H0L2F*Kfast);	
  dxdt[H1L2F_index] =   (-H1L2F*Kfast);	
  dxdt[H2L2F_index] =   (-H2L2F*Kfast);	
  dxdt[H3L2F_index] =   (-H3L2F*Kfast);	
  dxdt[H4L2F_index] =   (-H4L2F*Kfast);	
  dxdt[H5L2F_index] =   (-H5L2F*Kfast);	

  double Ca_Sensor_Ca_Cyt_dxdt = (-H0L0*5*A*Ca_Cyt) + (H1L0*B) + (-H0L0*2*S*Ca_Cyt) + (H0L1*D) 
   + (-H1L0*4*A*Ca_Cyt) + (H2L0*2*B*b) + (-H1L0*2*S*Ca_Cyt) + (H1L1*D) + (H1L0*B) + (-H0L0*5*A*Ca_Cyt)
   + (-H2L0*3*A*Ca_Cyt) + (H3L0*3*B*b*b) + (-H2L0*2*S*Ca_Cyt) + (H2L1*D) + (H2L0*2*B*b) + (-H1L0*4*A*Ca_Cyt)
   + (-H3L0*2*A*Ca_Cyt) + (H4L0*4*B*b*b*b) + (-H3L0*2*S*Ca_Cyt) + (H3L1*D) + (H3L0*3*B*b*b) + (-H2L0*3*A*Ca_Cyt)
   + (-H4L0*1*A*Ca_Cyt) + (H5L0*5*B*b*b*b*b) + (-H4L0*2*S*Ca_Cyt) + (H4L1*D) + (H4L0*4*B*b*b*b) + (-H3L0*2*A*Ca_Cyt)
   + (-H5L0*2*S*Ca_Cyt) + (H5L1*D) + (H5L0*5*B*b*b*b*b) + (-H4L0*A*Ca_Cyt)
 
   + (-H0L1*5*A*Ca_Cyt) + (H1L1*B) + (-H0L1*S*Ca_Cyt) + (H0L2*2*b*D) + (H0L1*D) + (-H0L0*2*S*Ca_Cyt)
   + (-H1L1*4*A*Ca_Cyt) + (H2L1*2*B*b) + (-H1L1*S*Ca_Cyt) + (H1L2*2*b*D) + (H1L1*B) + (-H0L1*5*A*Ca_Cyt) + (H1L1*D) + (-H1L0*2*S*Ca_Cyt)
   + (-H2L1*3*A*Ca_Cyt) + (H3L1*3*B*b*b) + (-H2L1*S*Ca_Cyt) + (H2L2*2*b*D) + (H2L1*2*B*b) + (-H1L1*4*A*Ca_Cyt) + (H2L1*D) + (-H2L0*2*S*Ca_Cyt)
   + (-H3L1*2*A*Ca_Cyt) + (H4L1*4*B*b*b*b) + (-H3L1*S*Ca_Cyt) + (H3L2*2*b*D) + (H3L1*3*B*b*b) + (-H2L1*3*A*Ca_Cyt) + (H3L1*D) + (-H3L0*2*S*Ca_Cyt)
   + (-H4L1*1*A*Ca_Cyt) + (H5L1*5*B*b*b*b*b) + (-H4L1*S*Ca_Cyt) + (H4L2*2*b*D) + (H4L1*4*B*b*b*b) + (-H3L1*2*A*Ca_Cyt) + (H4L1*D) + (-H4L0*2*S*Ca_Cyt)
   + (-H5L1*S*Ca_Cyt) + (H5L2*2*b*D) + (H5L1*5*B*b*b*b*b) + (-H4L1*A*Ca_Cyt) + (H5L1*D) + (-H5L0*2*S*Ca_Cyt)
 
   + (-H0L2*5*A*Ca_Cyt) + (H1L2*B) + (H0L2*2*b*D) + (-H0L1*S*Ca_Cyt)
   + (-H1L2*4*A*Ca_Cyt) + (H2L2*2*B*b) + (H1L2*2*b*D) + (-H1L1*S*Ca_Cyt) + (H1L2*B) + (-H0L2*5*A*Ca_Cyt)
   + (-H2L2*3*A*Ca_Cyt) + (H3L2*3*B*b*b) + (H2L2*2*b*D) + (-H2L1*S*Ca_Cyt) + (H2L2*2*b*B) + (-H1L2*4*A*Ca_Cyt)
   + (-H3L2*2*A*Ca_Cyt) + (H4L2*4*B*b*b*b) + (H3L2*2*b*D) + (-H3L1*S*Ca_Cyt) + (H3L2*3*B*b*b) + (-H2L2*3*A*Ca_Cyt)
   + (-H4L2*1*A*Ca_Cyt) + (H5L2*5*B*b*b*b*b) + (H4L2*2*b*D) + (-H4L1*S*Ca_Cyt) + (H4L2*4*B*b*b*b) + (-H3L2*2*A*Ca_Cyt)
   + (H5L2*5*B*b*b*b*b) + (-H4L2*A*Ca_Cyt) + (H5L2*2*b*D) + (-H5L1*S*Ca_Cyt);	//d[Ca]/dt]

  // Update parameter values
  double gluves_total = H0L0 + H1L0 + H2L0 + H3L0 + H4L0 + H5L0 +
    H0L1 + H1L1 + H2L1 +  H3L1 +  H4L1 +  H5L1 +
    H0L2 +  H1L2 +  H2L2 +  H3L2 +  H4L2 +  H5L2 + 
    H0L0F +  H5L0F +  H5L1F +  H0L2F +  H1L2F +  H2L2F +  H3L2F +  H4L2F +  H5L2F + 
    H0L0R +  H5L0R +  H5L1R +  H0L2R +  H1L2R +  H2L2R +  H3L2R +  H4L2R +  H5L2R;

  double gluves_rel_total = H0L0R +  H5L0R +  H5L1R +  H0L2R +  H1L2R +  H2L2R +  H3L2R +  H4L2R +  H5L2R;

  CALCIUM_SENSOR::update(variables,t,index);
  
  insilico::engine::neuron_value(index, "Ca_Sensor_Ca_Cyt_dxdt", Ca_Sensor_Ca_Cyt_dxdt);
  insilico::engine::neuron_value(index, "gluves_total", gluves_total);
  insilico::engine::neuron_value(index, "gluves_rel_total", gluves_rel_total);
};

void CALCIUM_SENSOR::reset(void)
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
};

void CALCIUM_SENSOR::update(state_type &variables,double t, unsigned index)
{
  // Get all variable indices
  unsigned H0L0_index = insilico::engine::neuron_index(index, "gluves_H0L0");
  unsigned H5L0_index = insilico::engine::neuron_index(index, "gluves_H5L0");
  unsigned H5L1_index = insilico::engine::neuron_index(index, "gluves_H5L1");
  unsigned H0L2_index = insilico::engine::neuron_index(index, "gluves_H0L2");
  unsigned H1L2_index = insilico::engine::neuron_index(index, "gluves_H1L2");
  unsigned H2L2_index = insilico::engine::neuron_index(index, "gluves_H2L2");
  unsigned H3L2_index = insilico::engine::neuron_index(index, "gluves_H3L2");
  unsigned H4L2_index = insilico::engine::neuron_index(index, "gluves_H4L2");
  unsigned H5L2_index = insilico::engine::neuron_index(index, "gluves_H5L2");

  unsigned H0L0F_index = insilico::engine::neuron_index(index, "gluves_H0L0F");
  unsigned H5L0F_index = insilico::engine::neuron_index(index, "gluves_H5L0F");
  unsigned H5L1F_index = insilico::engine::neuron_index(index, "gluves_H5L1F");
  unsigned H0L2F_index = insilico::engine::neuron_index(index, "gluves_H0L2F");
  unsigned H1L2F_index = insilico::engine::neuron_index(index, "gluves_H1L2F");
  unsigned H2L2F_index = insilico::engine::neuron_index(index, "gluves_H2L2F");
  unsigned H3L2F_index = insilico::engine::neuron_index(index, "gluves_H3L2F");
  unsigned H4L2F_index = insilico::engine::neuron_index(index, "gluves_H4L2F");
  unsigned H5L2F_index = insilico::engine::neuron_index(index, "gluves_H5L2F"); 
  
  // Get all variable values
  double H0L0 = variables[H0L0_index];
  double H5L0 = variables[H5L0_index];
  double H5L1 = variables[H5L1_index];
  double H5L2 = variables[H5L2_index];
  double H0L2 = variables[H0L2_index];
  double H1L2 = variables[H1L2_index];
  double H2L2 = variables[H2L2_index];
  double H3L2 = variables[H3L2_index];
  double H4L2 = variables[H4L2_index];

 // Get all parameter values
  const double Gspon = insilico::engine::neuron_value(index, "gluves_Gspon");
  const double Gsyn = insilico::engine::neuron_value(index, "gluves_Gsyn");
  const double Gasyn = insilico::engine::neuron_value(index, "gluves_Gasyn");
  const double volume = insilico::engine::neuron_value(index, "volume");
  
  spon_rate = H0L0 * Gspon * consts::Av * volume *1000; // [spon.vesicles]
  syn_rate = (H5L0 + H5L1 + H5L2) * Gsyn * consts::Av * volume * 1000; // [syn.rel.vesicles]
  asyn_rate = (H0L2 + H1L2 + H2L2 + H3L2 + H4L2 + H5L2) * Gasyn * consts::Av * volume * 1000; // [asyn.rel.vesicles]
  total_rate = spon_rate + syn_rate + asyn_rate;      

  
  // Checks for the last (4th) RK4 call 
  if ((t > (presenttime + (gvars::DELTA_T/2)))) {
    rk4count+=1;
    if (rk4count == 2){
      presenttime = t;
      rk4count = 0;
      spon_num_cum = spon_num_cum + (spon_rate * gvars::DELTA_T);
      syn_num_cum = syn_num_cum + (syn_rate * gvars::DELTA_T);
      asyn_num_cum = asyn_num_cum + (asyn_rate * gvars::DELTA_T);
      total_num_cum = spon_num_cum + syn_num_cum + asyn_num_cum;
      
      curr_vesicle_num = std::floor(total_num_cum);
      if( curr_vesicle_num > prev_vesicle_num){
	prev_vesicle_num += 1;
	flag = 1;
	variables[H0L0F_index] = variables[H0L0F_index] + H0L0;
	variables[H5L0F_index] = variables[H5L0F_index] + H5L0;
	variables[H5L1F_index] = variables[H5L1F_index] + H5L1;
	variables[H0L2F_index] = variables[H0L2F_index] + H0L2;
	variables[H1L2F_index] = variables[H1L2F_index] + H1L2;
	variables[H2L2F_index] = variables[H2L2F_index] + H2L2;
	variables[H3L2F_index] = variables[H3L2F_index] + H3L2;
	variables[H4L2F_index] = variables[H4L2F_index] + H4L2;
	variables[H5L2F_index] = variables[H5L2F_index] + H5L2;  

	variables[H0L0_index] = 0.0;
	variables[H5L0_index] = 0.0;
	variables[H5L1_index] = 0.0;
	variables[H0L2_index] = 0.0;
	variables[H1L2_index] = 0.0;
	variables[H2L2_index] = 0.0;
	variables[H3L2_index] = 0.0;
	variables[H4L2_index] = 0.0;
	variables[H5L2_index] = 0.0;
      }
      else{
	flag = 0;
      }
      //std::cout << " Function update() has been called at time : " << t * 1E06 <<  " DELTA_T " << gvars::DELTA_T * 1E06 << std::endl;
      //std::cin.get();
    }
  }

  insilico::engine::neuron_value(index, "gluves_spon_rate", spon_rate);
  insilico::engine::neuron_value(index, "gluves_syn_rate", syn_rate);
  insilico::engine::neuron_value(index, "gluves_asyn_rate", asyn_rate);
  insilico::engine::neuron_value(index, "gluves_total_rate", total_rate);

  insilico::engine::neuron_value(index, "gluves_spon_num_cum", spon_num_cum);
  insilico::engine::neuron_value(index, "gluves_syn_num_cum", syn_num_cum);
  insilico::engine::neuron_value(index, "gluves_asyn_num_cum", asyn_num_cum);
  insilico::engine::neuron_value(index, "gluves_total_num_cum", total_num_cum);
  insilico::engine::neuron_value(index, "gluves_rel_flag", flag);

  // Update release parameters for the neuron
  if (flag){
  insilico::engine::neuron_value(index, "last_rel_time", t);
  }

  //std::cout << "Time = " << t << " Curr_vesicle_num = " << curr_vesicle_num << " prev_vesicle_num = " << prev_vesicle_num << std::endl;
  //std::cout << "spon_rate =  " << spon_rate << " | syn_rate = " << syn_rate << " | asyn_rate = " << asyn_rate << " | total_rate = " << total_rate << std::endl;  
  //std::cout << "spon_num_cum =  " << spon_num_cum << "| syn_num_cum = " << syn_num_cum << " | asyn_num_cum = " << asyn_num_cum << " | total_num_cum = " << total_num_cum << std::endl;
  //std::cout << "Flag = " << flag << std::endl;
  //std::cin.get();
  // Update variables

};
#endif // CALCIUM_SENSOR_HPP_INCLUDED
