/* Last Revised Date: 3_AUG_2015 */
// UNITS: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads

#ifndef VESICULAR_RELASE_HPP_INCLUDED	
#define VESICULAR_RELASE_HPP_INCLUDED

#include <vector>
#include <iostream>
#include <cmath>

#include "insilico/include/data_types.hpp"
#include "insilico/include/physical_constants.hpp"
#include "insilico/include/astron_global_variables.hpp"
//#include "insilico/include/astron_boost_random.hpp"

#include "insilico-0.25/include/insilico/core.hpp"

namespace consts=astron::phy_const;
namespace gvars=astron::global_vars;

namespace vesres {
  void state_machine(state_type &variables, state_type &dxdt, const double t, unsigned index, std::unordered_map< std::string, std::string> > varnames, 
		     std::unordered_map< std::string, std::string> > parnames, std::unordered_map< std::string, std::string> > valnames) 
  {
    // Get all variable indices
    unsigned ca_cyt_index = insilico::engine::neuron_index(index, "ca_cyt");
      
    unsigned H0L0_index = insilico::engine::neuron_index(index, varnames["H0L0"]);
    unsigned H1L0_index = insilico::engine::neuron_index(index, varnames["H1L0"]);
    unsigned H2L0_index = insilico::engine::neuron_index(index, varnames["H2L0"]);
    unsigned H3L0_index = insilico::engine::neuron_index(index, varnames["H3L0"]);  
    unsigned H4L0_index = insilico::engine::neuron_index(index, varnames["H4L0"]);
    unsigned H5L0_index = insilico::engine::neuron_index(index, varnames["H5L0"]);

    unsigned H0L1_index = insilico::engine::neuron_index(index, varnames["H0L1"]);
    unsigned H1L1_index = insilico::engine::neuron_index(index, varnames["H1L1"]);
    unsigned H2L1_index = insilico::engine::neuron_index(index, varnames["H2L1"]);
    unsigned H3L1_index = insilico::engine::neuron_index(index, varnames["H3L1"]);
    unsigned H4L1_index = insilico::engine::neuron_index(index, varnames["H4L1"]);
    unsigned H5L1_index = insilico::engine::neuron_index(index, varnames["H5L1"]);

    unsigned H0L2_index = insilico::engine::neuron_index(index, varnames["H0L2"]);
    unsigned H1L2_index = insilico::engine::neuron_index(index, varnames["H1L2"]);
    unsigned H2L2_index = insilico::engine::neuron_index(index, varnames["H2L2"]);
    unsigned H3L2_index = insilico::engine::neuron_index(index, varnames["H3L2"]);
    unsigned H4L2_index = insilico::engine::neuron_index(index, varnames["H4L2"]);
    unsigned H5L2_index = insilico::engine::neuron_index(index, varnames["H5L2"]);

    unsigned H0L0F_index = insilico::engine::neuron_index(index, varnames["H0L0F"]);
    unsigned H5L0F_index = insilico::engine::neuron_index(index, varnames["H5L0F"]);
    unsigned H5L1F_index = insilico::engine::neuron_index(index, varnames["H5L1F"]);
    unsigned H0L2F_index = insilico::engine::neuron_index(index, varnames["H0L2F"]);
    unsigned H1L2F_index = insilico::engine::neuron_index(index, varnames["H1L2F"]);
    unsigned H2L2F_index = insilico::engine::neuron_index(index, varnames["H2L2F"]);
    unsigned H3L2F_index = insilico::engine::neuron_index(index, varnames["H3L2F"]);
    unsigned H4L2F_index = insilico::engine::neuron_index(index, varnames["H4L2F"]);
    unsigned H5L2F_index = insilico::engine::neuron_index(index, varnames["H5L2F"]);

    unsigned H0L0R_index = insilico::engine::neuron_index(index, varnames["H0L0R"]);
    unsigned H5L0R_index = insilico::engine::neuron_index(index, varnames["H5L0R"]);
    unsigned H5L1R_index = insilico::engine::neuron_index(index, varnames["H5L1R"]);
    unsigned H0L2R_index = insilico::engine::neuron_index(index, varnames["H0L2R"]);
    unsigned H1L2R_index = insilico::engine::neuron_index(index, varnames["H1L2R"]);
    unsigned H2L2R_index = insilico::engine::neuron_index(index, varnames["H2L2R"]);
    unsigned H3L2R_index = insilico::engine::neuron_index(index, varnames["H3L2R"]);
    unsigned H4L2R_index = insilico::engine::neuron_index(index, varnames["H4L2R"]);
    unsigned H5L2R_index = insilico::engine::neuron_index(index, varnames["H5L2R"]);
 
    // Get all parameter values
    const double A = insilico::engine::neuron_value(index, parnames["A"]);
    const double B = insilico::engine::neuron_value(index, parnames["B"]);
    const double S = insilico::engine::neuron_value(index, parnames["S"]);
    const double D = insilico::engine::neuron_value(index, parnames["D"]);
    const double b = insilico::engine::neuron_value(index, parnames["b"]);
    const double Gspon = insilico::engine::neuron_value(index, parnames["Gspon"]);
    const double Gsyn = insilico::engine::neuron_value(index, parnames["Gsyn");
    const double Gasyn = insilico::engine::neuron_value(index, parnames["Gasyn"]);
    const double Kfast = insilico::engine::neuron_value(index, parnames["Kfast"]);
    const double Kslow = insilico::engine::neuron_value(index, parnames["Kslow"]);

    // Get all variable values
    double ca_cyt = variables[ca_cyt_index];
  
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

    dxdt[H0L0_index] = (-H0L0*5*A*ca_cyt) + (H1L0*B) + (-H0L0*2*S*ca_cyt) + (H0L1*D) + (-H0L0*Gspon) + (H0L0F*Kfast) + (H0L0R*Kslow)  + (H0L2R*Kslow)  + (H5L0R*Kslow) + (H5L1R*Kslow) 
      + (H1L2R*Kslow) + (H2L2R*Kslow) + (H3L2R*Kslow) + (H4L2R*Kslow) + (H5L2R*Kslow);      /* d[X0Y0]/dt */
  
    dxdt[H1L0_index] = (-H1L0*4*A*ca_cyt) + (H2L0*2*B*b) + (-H1L0*2*S*ca_cyt) + (H1L1*D) + (-H1L0*B) + (H0L0*5*A*ca_cyt);      /* d[X1Y0]/dt */
    dxdt[H2L0_index] = (-H2L0*3*A*ca_cyt) + (H3L0*3*B*b*b) + (-H2L0*2*S*ca_cyt) + (H2L1*D) + (-H2L0*2*B*b) + (H1L0*4*A*ca_cyt);      /* d[X2Y0]/dt */
    dxdt[H3L0_index] = (-H3L0*2*A*ca_cyt) + (H4L0*4*B*b*b*b) + (-H3L0*2*S*ca_cyt) + (H3L1*D) + (-H3L0*3*B*b*b) + (H2L0*3*A*ca_cyt);      /* d[X3Y0]/dt */
    dxdt[H4L0_index] = (-H4L0*1*A*ca_cyt) + (H5L0*5*B*b*b*b*b) + (-H4L0*2*S*ca_cyt) + (H4L1*D) + (-H4L0*4*B*b*b*b) + (H3L0*2*A*ca_cyt);      /* d[X4Y0]/dt */
    dxdt[H5L0_index] = (-H5L0*2*S*ca_cyt) + (H5L1*D) + (-H5L0*5*B*b*b*b*b) + (H4L0*A*ca_cyt) + (-H5L0*Gsyn)  + (H5L0F*Kfast);      /* d[X5Y0]/dt */

    dxdt[H0L1_index] = (-H0L1*5*A*ca_cyt) + (H1L1*B) + (-H0L1*S*ca_cyt) + (H0L2*2*b*D) + (-H0L1*D) + (H0L0*2*S*ca_cyt);      /* d[X0Y1]/dt */
    dxdt[H1L1_index] = (-H1L1*4*A*ca_cyt) + (H2L1*2*B*b) + (-H1L1*S*ca_cyt) + (H1L2*2*b*D) + (-H1L1*B) + (H0L1*5*A*ca_cyt) + (-H1L1*D) + (H1L0*2*S*ca_cyt);      /* d[X1Y1]/dt */
    dxdt[H2L1_index] = (-H2L1*3*A*ca_cyt) + (H3L1*3*B*b*b) + (-H2L1*S*ca_cyt) + (H2L2*2*b*D) + (-H2L1*2*B*b) + (H1L1*4*A*ca_cyt) + (-H2L1*D) + (H2L0*2*S*ca_cyt);/* d[X2Y1]/dt */
    dxdt[H3L1_index] = (-H3L1*2*A*ca_cyt) + (H4L1*4*B*b*b*b) + (-H3L1*S*ca_cyt) + (H3L2*2*b*D) + (-H3L1*3*B*b*b) + (H2L1*3*A*ca_cyt) + (-H3L1*D) + (H3L0*2*S*ca_cyt); /* d[X3Y1]/dt */
    dxdt[H4L1_index] = (-H4L1*1*A*ca_cyt) + (H5L1*5*B*b*b*b*b) + (-H4L1*S*ca_cyt) + (H4L2*2*b*D) + (-H4L1*4*B*b*b*b) + (H3L1*2*A*ca_cyt) + (-H4L1*D) + (H4L0*2*S*ca_cyt); /* d[H4Y1]/dt */
    dxdt[H5L1_index] = (-H5L1*S*ca_cyt) + (H5L2*2*b*D) + (-H5L1*5*B*b*b*b*b) + (H4L1*A*ca_cyt) + (-H5L1*D) + (H5L0*2*S*ca_cyt) + (-H5L1*Gsyn)  + (H5L1F*Kfast); // d[X5Y1]/dt
  
    dxdt[H0L2_index] = (-H0L2*5*A*ca_cyt) + (H1L2*B) + (-H0L2*2*b*D) + (H0L1*S*ca_cyt) + (-H0L2*Gasyn) +  (H0L2F*Kfast); // d[X0Y2]/dt
    dxdt[H1L2_index] = (-H1L2*4*A*ca_cyt) + (H2L2*2*B*b) + (-H1L2*2*b*D) + (H1L1*S*ca_cyt) + (-H1L2*B) + (H0L2*5*A*ca_cyt) + (-H1L2*Gasyn)  + (H1L2F*Kfast); // d[X1Y2]/dt
    dxdt[H2L2_index] = (-H2L2*3*A*ca_cyt) + (H3L2*3*B*b*b) + (-H2L2*2*b*D) + (H2L1*S*ca_cyt) + (-H2L2*2*b*B) + (H1L2*4*A*ca_cyt) + (-H2L2*Gasyn)  + (H2L2F*Kfast); // d[X2Y2]/dt
    dxdt[H3L2_index] = (-H3L2*2*A*ca_cyt) + (H4L2*4*B*b*b*b) + (-H3L2*2*b*D) + (H3L1*S*ca_cyt) + (-H3L2*3*B*b*b) + (H2L2*3*A*ca_cyt) + (-H3L2*Gasyn)  + (H3L2F*Kfast);    /* d[X3Y2]/dt */
    dxdt[H4L2_index] = (-H4L2*1*A*ca_cyt) + (H5L2*5*B*b*b*b*b) + (-H4L2*2*b*D) + (H4L1*S*ca_cyt) + (-H4L2*4*B*b*b*b) + (H3L2*2*A*ca_cyt) + (-H4L2*Gasyn)  + (H4L2F*Kfast); /* d[H4Y2]/dt */
    dxdt[H5L2_index] = (-H5L2*5*B*b*b*b*b) + (H4L2*A*ca_cyt) + (-H5L2*2*b*D) + (H5L1*S*ca_cyt) + (-H5L2*Gsyn) + (-H5L2*Gasyn)  + (H5L2F*Kfast);      /* d[X5Y2]/dt */
  
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

    double ca_cyt_flux = (-H0L0*5*A*ca_cyt) + (H1L0*B) + (-H0L0*2*S*ca_cyt) + (H0L1*D) 
      + (-H1L0*4*A*ca_cyt) + (H2L0*2*B*b) + (-H1L0*2*S*ca_cyt) + (H1L1*D) + (H1L0*B) + (-H0L0*5*A*ca_cyt)
      + (-H2L0*3*A*ca_cyt) + (H3L0*3*B*b*b) + (-H2L0*2*S*ca_cyt) + (H2L1*D) + (H2L0*2*B*b) + (-H1L0*4*A*ca_cyt)
      + (-H3L0*2*A*ca_cyt) + (H4L0*4*B*b*b*b) + (-H3L0*2*S*ca_cyt) + (H3L1*D) + (H3L0*3*B*b*b) + (-H2L0*3*A*ca_cyt)
      + (-H4L0*1*A*ca_cyt) + (H5L0*5*B*b*b*b*b) + (-H4L0*2*S*ca_cyt) + (H4L1*D) + (H4L0*4*B*b*b*b) + (-H3L0*2*A*ca_cyt)
      + (-H5L0*2*S*ca_cyt) + (H5L1*D) + (H5L0*5*B*b*b*b*b) + (-H4L0*A*ca_cyt)
 
      + (-H0L1*5*A*ca_cyt) + (H1L1*B) + (-H0L1*S*ca_cyt) + (H0L2*2*b*D) + (H0L1*D) + (-H0L0*2*S*ca_cyt)
      + (-H1L1*4*A*ca_cyt) + (H2L1*2*B*b) + (-H1L1*S*ca_cyt) + (H1L2*2*b*D) + (H1L1*B) + (-H0L1*5*A*ca_cyt) + (H1L1*D) + (-H1L0*2*S*ca_cyt)
      + (-H2L1*3*A*ca_cyt) + (H3L1*3*B*b*b) + (-H2L1*S*ca_cyt) + (H2L2*2*b*D) + (H2L1*2*B*b) + (-H1L1*4*A*ca_cyt) + (H2L1*D) + (-H2L0*2*S*ca_cyt)
      + (-H3L1*2*A*ca_cyt) + (H4L1*4*B*b*b*b) + (-H3L1*S*ca_cyt) + (H3L2*2*b*D) + (H3L1*3*B*b*b) + (-H2L1*3*A*ca_cyt) + (H3L1*D) + (-H3L0*2*S*ca_cyt)
      + (-H4L1*1*A*ca_cyt) + (H5L1*5*B*b*b*b*b) + (-H4L1*S*ca_cyt) + (H4L2*2*b*D) + (H4L1*4*B*b*b*b) + (-H3L1*2*A*ca_cyt) + (H4L1*D) + (-H4L0*2*S*ca_cyt)
      + (-H5L1*S*ca_cyt) + (H5L2*2*b*D) + (H5L1*5*B*b*b*b*b) + (-H4L1*A*ca_cyt) + (H5L1*D) + (-H5L0*2*S*ca_cyt)
 
      + (-H0L2*5*A*ca_cyt) + (H1L2*B) + (H0L2*2*b*D) + (-H0L1*S*ca_cyt)
      + (-H1L2*4*A*ca_cyt) + (H2L2*2*B*b) + (H1L2*2*b*D) + (-H1L1*S*ca_cyt) + (H1L2*B) + (-H0L2*5*A*ca_cyt)
      + (-H2L2*3*A*ca_cyt) + (H3L2*3*B*b*b) + (H2L2*2*b*D) + (-H2L1*S*ca_cyt) + (H2L2*2*b*B) + (-H1L2*4*A*ca_cyt)
      + (-H3L2*2*A*ca_cyt) + (H4L2*4*B*b*b*b) + (H3L2*2*b*D) + (-H3L1*S*ca_cyt) + (H3L2*3*B*b*b) + (-H2L2*3*A*ca_cyt)
      + (-H4L2*1*A*ca_cyt) + (H5L2*5*B*b*b*b*b) + (H4L2*2*b*D) + (-H4L1*S*ca_cyt) + (H4L2*4*B*b*b*b) + (-H3L2*2*A*ca_cyt)
      + (H5L2*5*B*b*b*b*b) + (-H4L2*A*ca_cyt) + (H5L2*2*b*D) + (-H5L1*S*ca_cyt);	//d[Ca]/dt]

    // Update parameter values
    double ves_total = H0L0 + H1L0 + H2L0 + H3L0 + H4L0 + H5L0 +
      H0L1 + H1L1 + H2L1 +  H3L1 +  H4L1 +  H5L1 +
      H0L2 +  H1L2 +  H2L2 +  H3L2 +  H4L2 +  H5L2 + 
      H0L0F +  H5L0F +  H5L1F +  H0L2F +  H1L2F +  H2L2F +  H3L2F +  H4L2F +  H5L2F + 
      H0L0R +  H5L0R +  H5L1R +  H0L2R +  H1L2R +  H2L2R +  H3L2R +  H4L2R +  H5L2R;

    double ves_released = H0L0R +  H5L0R +  H5L1R +  H0L2R +  H1L2R +  H2L2R +  H3L2R +  H4L2R +  H5L2R;

    insilico::engine::neuron_value(index, valnames["ca_cyt_flux"], ca_cyt_flux);
    insilico::engine::neuron_value(index, valnames["ves_total"], ves_total);
    insilico::engine::neuron_value(index, valnames["ves_released"], ves_released);
  };

  void update_rate(state_type &variables,double t, unsigned index,std::vector<std::string> varnames,std::vector<std::string> parnames,std::vector<std::string> valnames)
  {
    // Get all variable indices
    unsigned H0L0_index = insilico::engine::neuron_index(index, varnames["H0L0"]);
    unsigned H5L0_index = insilico::engine::neuron_index(index, varnames["H5L0"]);
    unsigned H5L1_index = insilico::engine::neuron_index(index, varnames["H5L1"]);
    unsigned H0L2_index = insilico::engine::neuron_index(index, varnames["H0L2"]);
    unsigned H1L2_index = insilico::engine::neuron_index(index, varnames["H1L2"]);
    unsigned H2L2_index = insilico::engine::neuron_index(index, varnames["H2L2"]);
    unsigned H3L2_index = insilico::engine::neuron_index(index, varnames["H3L2"]);
    unsigned H4L2_index = insilico::engine::neuron_index(index, varnames["H4L2"]);
    unsigned H5L2_index = insilico::engine::neuron_index(index, varnames["H5L2"]);
  
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
    const double Gspon = insilico::engine::neuron_value(index, parnames["Gspon"]);
    const double Gsyn = insilico::engine::neuron_value(index, parnames["Gspon"]);
    const double Gasyn = insilico::engine::neuron_value(index, parnames["Gspon"]);

    const double volume_cyt = insilico::engine::neuron_value(index, "volume_cyt");
  
    double spon_rate = H0L0 * Gspon * consts::Av * volume_cyt * 1000; // [spon.vesicles]
    double syn_rate = (H5L0 + H5L1 + H5L2) * Gsyn * consts::Av * volume_cyt * 1000; // [syn.rel.vesicles]
    double asyn_rate = (H0L2 + H1L2 + H2L2 + H3L2 + H4L2 + H5L2) * Gasyn * consts::Av * volume_cyt * 1000; // [asyn.rel.vesicles]
    double total_rate = spon_rate + syn_rate + asyn_rate;      

    insilico::engine::neuron_value(index, valnames["spon_rate"], spon_rate);
    insilico::engine::neuron_value(index, valnames["syn_rate"], syn_rate);
    insilico::engine::neuron_value(index, valnames["asyn_rate"], asyn_rate);
    insilico::engine::neuron_value(index, valnames["total_rate"], total_rate);

  };

  void update_release(state_type &variables, const double t, unsigned index, double rand_num, std::vector<std::string> varnames,std::vector<std::string> valnames1,std::vector<std::string> valnames2)
  {

    // Get all variable indices
    unsigned H0L0_index = insilico::engine::neuron_index(index, varnames["H0L0"]);
    unsigned H5L0_index = insilico::engine::neuron_index(index, varnames["H5L0"]);
    unsigned H5L1_index = insilico::engine::neuron_index(index, varnames["H5L1"]);
    unsigned H0L2_index = insilico::engine::neuron_index(index, varnames["H0L2"]);
    unsigned H1L2_index = insilico::engine::neuron_index(index, varnames["H1L2"]);
    unsigned H2L2_index = insilico::engine::neuron_index(index, varnames["H2L2"]);
    unsigned H3L2_index = insilico::engine::neuron_index(index, varnames["H3L2"]);
    unsigned H4L2_index = insilico::engine::neuron_index(index, varnames["H4L2"]);
    unsigned H5L2_index = insilico::engine::neuron_index(index, varnames["H5L2"]);

    unsigned H0L0F_index = insilico::engine::neuron_index(index, varnames["H0L0F"]);
    unsigned H5L0F_index = insilico::engine::neuron_index(index, varnames["H5L0F"]);
    unsigned H5L1F_index = insilico::engine::neuron_index(index, varnames["H5L1F"]);
    unsigned H0L2F_index = insilico::engine::neuron_index(index, varnames["H0L2F"]);
    unsigned H1L2F_index = insilico::engine::neuron_index(index, varnames["H1L2F"]);
    unsigned H2L2F_index = insilico::engine::neuron_index(index, varnames["H2L2F"]);
    unsigned H3L2F_index = insilico::engine::neuron_index(index, varnames["H3L2F"]);
    unsigned H4L2F_index = insilico::engine::neuron_index(index, varnames["H4L2F"]);
    unsigned H5L2F_index = insilico::engine::neuron_index(index, varnames["H5L2F"]);
 
    // Get parameter values
    int flag = (int)insilico::engine::neuron_value(index, valnames2[7]);
    double gluves_rel_time = insilico::engine::neuron_value(index, valnames2[8]);
    double total_rate = insilico::engine::neuron_value(index, valnames2[6]);

    // Checks for the last (1th) RK4 call 
    if(gvars::rk4cell.rk4counter[index] == 1){
      flag = 0;
      gluves_rel_time = -1.0;
    }

    if( (std::min(total_rate,1.0) * 1E-02) > rand_num && (gvars::rk4cell.rk4counter[index] == 1) ){
      flag = 1;
      gluves_rel_time = t;
      variables[H0L0F_index] = variables[H0L0F_index] + variables[H0L0_index];
      variables[H5L0F_index] = variables[H5L0F_index] + variables[H5L0_index];
      variables[H5L1F_index] = variables[H5L1F_index] + variables[H5L1_index];
      variables[H0L2F_index] = variables[H0L2F_index] + variables[H0L2_index];
      variables[H1L2F_index] = variables[H1L2F_index] + variables[H1L2_index];
      variables[H2L2F_index] = variables[H2L2F_index] + variables[H2L2_index];
      variables[H3L2F_index] = variables[H3L2F_index] + variables[H3L2_index];
      variables[H4L2F_index] = variables[H4L2F_index] + variables[H4L2_index];
      variables[H5L2F_index] = variables[H5L2F_index] + variables[H5L2_index];  
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
    insilico::engine::neuron_value(index, valnames2[7], flag);
    insilico::engine::neuron_value(index, valnames2[8], gluves_rel_time);  
  };
}
#endif // VESICULAR_RELASE_HPP_INCLUDED
