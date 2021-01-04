// Time-stamp: <2018-02-09 15:13:04 anup>
// Units: All SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Ref: bollmann2000, zhang2004b, kreft2004, parpura2000, thomas1999, robinson2002, von_poser1997, sun2007, bacaj2013, jackman2016
// Ref: heidelberger1994, crippa2006

#include <vector>
#include <iostream>
#include <cmath>
#include <string>

#include "data_types.hpp"
#include "physical_constants.hpp"
#include "global_variables.hpp"

#include "insilico/core.hpp"
#include "transmitter_release_syt4syt5.hpp"
#include "random_number_generator.hpp"

namespace consts=astron::phy_const;
namespace gvars=astron::globals;
namespace ar = astron::random;

void transmitter_release_syt4syt5::state_machine(state_type &variables, state_type &dxdt, const double t, unsigned index, 
					      stringmap varnames,
					      stringmap parnames,
					      stringmap valnames) 
{
  // Get all variable indices
  unsigned ca_cyt_index = newinsilico::get_neuron_index(index, "ca_cyt");

  // Sensor states
  unsigned k0_index = newinsilico::get_neuron_index(index, varnames["syt45_k0"]);
  unsigned k1_index = newinsilico::get_neuron_index(index, varnames["syt45_k1"]);
  unsigned k2_index = newinsilico::get_neuron_index(index, varnames["syt45_k2"]);
  
  unsigned f0_index = newinsilico::get_neuron_index(index, varnames["syt45_f0"]);
  unsigned f1_index = newinsilico::get_neuron_index(index, varnames["syt45_f1"]);
  unsigned f2_index = newinsilico::get_neuron_index(index, varnames["syt45_f2"]);
  unsigned f3_index = newinsilico::get_neuron_index(index, varnames["syt45_f3"]);
  unsigned f4_index = newinsilico::get_neuron_index(index, varnames["syt45_f4"]);
  unsigned f5_index = newinsilico::get_neuron_index(index, varnames["syt45_f5"]);
    
  // Vesicle release & recycling: Kiss-and-run
  unsigned vkdoc_index = newinsilico::get_neuron_index(index, varnames["syt45_vkdoc"]);   // Docked vesicles for KR
  unsigned vkrel_index = newinsilico::get_neuron_index(index, varnames["syt45_vkrel"]);   // Released vesicles KR
  unsigned vkend_index = newinsilico::get_neuron_index(index, varnames["syt45_vkend"]);   // Endocytosis vesicles KR 
  unsigned vkacd_index = newinsilico::get_neuron_index(index, varnames["syt45_vkacd"]);   // Reacidified vesicles KR

  // Vesicle release & recycling: Full fusion
  unsigned vfmob_index = newinsilico::get_neuron_index(index, varnames["syt45_vfmob"]);   // Mobile vesicles for FF
  unsigned vfrel_index = newinsilico::get_neuron_index(index, varnames["syt45_vfrel"]);   // Released vesicles FF
  unsigned vfend_index = newinsilico::get_neuron_index(index, varnames["syt45_vfend"]);   // Endocytosis vesicles FF 
  unsigned vfacd_index = newinsilico::get_neuron_index(index, varnames["syt45_vfacd"]);   // Reacidified vesicles FF

  // Get all parameter values
  const double volume_cyt = newinsilico::neuron_value(index, "volume_cyt"); // Volume_Cyt (m^3)
  
  const double kkf = newinsilico::neuron_value(index, parnames["syt45_kkf"]);
  const double kkb = newinsilico::neuron_value(index, parnames["syt45_kkb"]);
  const double kbb = newinsilico::neuron_value(index, parnames["syt45_kbb"]);
  const double k0exo = newinsilico::neuron_value(index, parnames["syt45_k0exo"]);
  const double kcaexo = newinsilico::neuron_value(index, parnames["syt45_kcaexo"]);

  const double fkf = newinsilico::neuron_value(index, parnames["syt45_fkf"]);
  const double fkb = newinsilico::neuron_value(index, parnames["syt45_fkb"]);
  const double fbb = newinsilico::neuron_value(index, parnames["syt45_fbb"]);
  const double f0exo = newinsilico::neuron_value(index, parnames["syt45_f0exo"]);
  const double fcaexo = newinsilico::neuron_value(index, parnames["syt45_fcaexo"]);

  const double rmob2doc = newinsilico::neuron_value(index, parnames["syt45_rmob2doc"]);
  const double rkend = newinsilico::neuron_value(index, parnames["syt45_rkend"]);
  const double rkacd = newinsilico::neuron_value(index, parnames["syt45_rkacd"]);
  const double rkacd2mob = newinsilico::neuron_value(index, parnames["syt45_rkacd2mob"]);
  
  const double rfend = newinsilico::neuron_value(index, parnames["syt45_rfend"]);
  const double rfacd = newinsilico::neuron_value(index, parnames["syt45_rfacd"]);
  const double rfacd2mob = newinsilico::neuron_value(index, parnames["syt45_rfacd2mob"]);

  const double fracmob2doc = newinsilico::neuron_value(index, parnames["syt45_fracmob2doc"]);

  // Set limits on variable values
  variables[ca_cyt_index] = std::max<double>(variables[ca_cyt_index],0.0);
  variables[k0_index] = std::max<double>(variables[k0_index],0.0);
  variables[k1_index] = std::max<double>(variables[k1_index],0.0);
  variables[k2_index] = std::max<double>(variables[k2_index],0.0);

  variables[f0_index] = std::max<double>(variables[f0_index],0.0);
  variables[f1_index] = std::max<double>(variables[f1_index],0.0);
  variables[f2_index] = std::max<double>(variables[f2_index],0.0);
  variables[f3_index] = std::max<double>(variables[f3_index],0.0);
  variables[f4_index] = std::max<double>(variables[f4_index],0.0);
  variables[f5_index] = std::max<double>(variables[f5_index],0.0);

  variables[vkdoc_index] = std::max<double>(variables[vkdoc_index],0.0);
  variables[vkrel_index] = std::max<double>(variables[vkrel_index],0.0);
  variables[vkend_index] = std::max<double>(variables[vkend_index],0.0);
  variables[vkacd_index] = std::max<double>(variables[vkacd_index],0.0);

  variables[vfmob_index] = std::max<double>(variables[vfmob_index],0.0);
  variables[vfrel_index] = std::max<double>(variables[vfrel_index],0.0);
  variables[vfend_index] = std::max<double>(variables[vfend_index],0.0);
  variables[vfacd_index] = std::max<double>(variables[vfacd_index],0.0);
    
  // Load initial values of glutamate_vesicles
  const double initcheck  = newinsilico::neuron_value(index, parnames["syt45_initcheck"]);
  // if (initcheck <= 0) {
    variables[k0_index] = variables[vkdoc_index] /(consts::Av * volume_cyt * 1000);
    variables[f0_index] = variables[vfmob_index] /(consts::Av * volume_cyt * 1000);
    // Update initialization check value
    // newinsilico::neuron_value(index, parnames["syt45_initcheck"], 1.0);
  // }
  
  // Get all variable values
  double ca_cyt = variables[ca_cyt_index];

  double k0 = variables[k0_index];
  double k1 = variables[k1_index];
  double k2 = variables[k2_index];
  
  double f0 = variables[f0_index];
  double f1 = variables[f1_index];
  double f2 = variables[f2_index];
  double f3 = variables[f3_index];
  double f4 = variables[f4_index];
  double f5 = variables[f5_index];

  double vkdoc = variables[vkdoc_index]; 
  double vkrel = variables[vkrel_index];
  double vkend = variables[vkend_index];
  double vkacd = variables[vkacd_index];

  double vfmob = variables[vfmob_index]; 
  double vfrel = variables[vfrel_index];
  double vfend = variables[vfend_index];
  double vfacd = variables[vfacd_index];
  
  // Time until no release is allowed
  double reldelay =   newinsilico::neuron_value(index, parnames["syt45_reldelay"]);
  
  // --------------------------------------------
  // Order of reactions: right, down, up, left
  
  dxdt[k0_index]  = (-k0 * 2 * kkf * ca_cyt)  + (k1 * 1 * kkb);
  dxdt[k1_index]  = (-k1 * 1 * kkf * ca_cyt)  + (k2 * 2 * kbb * kkb) + (-k1 * 1 * kkb)           + (k0 * 2 * kkf * ca_cyt);
  dxdt[k2_index]  =                                                    (-k2 * 2 * kbb * kkb)     + (k1 * 1 * kkf * ca_cyt);

  dxdt[f0_index]  = (-f0 * 5 * fkf * ca_cyt) + (f1 * fkb);
  dxdt[f1_index]  = (-f1 * 4 * fkf * ca_cyt) + (f2 * 2 * pow(fbb,1) * fkb) + (-f1 * 1 * pow(fbb,0) * fkb) + (f0 * 5 * fkf * ca_cyt);
  dxdt[f2_index]  = (-f2 * 3 * fkf * ca_cyt) + (f3 * 3 * pow(fbb,2) * fkb) + (-f2 * 2 * pow(fbb,1) * fkb) + (f1 * 4 * fkf * ca_cyt);
  dxdt[f3_index]  = (-f3 * 2 * fkf * ca_cyt) + (f4 * 4 * pow(fbb,3) * fkb) + (-f3 * 3 * pow(fbb,2) * fkb) + (f2 * 3 * fkf * ca_cyt);
  dxdt[f4_index]  = (-f4 * 1 * fkf * ca_cyt) + (f5 * 5 * pow(fbb,4) * fkb) + (-f4 * 4 * pow(fbb,3) * fkb) + (f3 * 2 * fkf * ca_cyt);
  dxdt[f5_index]  =                                                          (-f5 * 5 * pow(fbb,4) * fkb) + (f4 * 1 * fkf * ca_cyt);

  // ------------------------------------------

  double k0frac = (k0 / (k0 + k1 + k2));
  double k2frac = (k2 / (k0 + k1 + k2));
  
  double f0frac = (f0 / (f0 + f1 + f2 + f3 + f4 + f5));
  double f5frac = (f5 / (f0 + f1 + f2 + f3 + f4 + f5));

  // ----------------------
  
  dxdt[vkdoc_index] = 0.0
    + (- vkdoc * k0frac * k0exo)
    + (- vkdoc * k2frac * kcaexo)
    + (+ vfmob * (1-fracmob2doc) * rmob2doc);	// 

  dxdt[vkrel_index] = 0.0
    + (+ vkdoc * k0frac * k0exo)
    + (+ vkdoc * k2frac * kcaexo)
    + (- vkrel * rkend);

  dxdt[vkend_index] = 0.0
    + (+ vkrel * rkend)
    + (- vkend * rkacd);

  dxdt[vkacd_index] = 0.0
    + (+ vkend * rkacd)
    + (- vkacd * rkacd2mob);

  // ----------------------

  // dxdt[vfmob_index] = 0.0
  //   + (- vfmob * f0frac * f0exo)
  //   + (- vfmob * f5frac * fcaexo)
  //   + (- (vfmob) * rmob2doc)	// 1 vesicle remains in the mobile pool?
  //   + (+ vkacd * rkacd2mob)
  //   + (+ vfacd * rfacd2mob);

  // dxdt[vfrel_index] = 0.0
  //   + (+ vkdoc * f0frac * f0exo)
  //   + (+ vkdoc * f5frac * fcaexo)
  //   + (+ vfmob * f0frac * f0exo)
  //   + (+ vfmob * f5frac * fcaexo)
  //   + (- vfrel * rfend);

  // dxdt[vfend_index] = 0.0
  //   + (+ vfrel * rfend)
  //   + (- vfend * rfacd);

  // dxdt[vfacd_index] = 0.0
  //   + (+ vfend * rfacd)
  //   + (- vfacd * rfacd2mob);

  dxdt[vfmob_index] = 0.0
    + (- vfmob * f0frac * f0exo)
    + (- vfmob * f5frac * fcaexo)
    + (- vfmob * (1-fracmob2doc) * rmob2doc)	// 
    + (+ vkacd * rkacd2mob)
    + (+ vfacd * rfacd2mob);

  dxdt[vfrel_index] = 0.0
    + (+ vfmob * f0frac * f0exo)
    + (+ vfmob * f5frac * fcaexo)
    + (- vfrel * rfend);

  dxdt[vfend_index] = 0.0
    + (+ vfrel * rfend)
    + (- vfend * rfacd);

  dxdt[vfacd_index] = 0.0
    + (+ vfend * rfacd)
    + (- vfacd * rfacd2mob);

  // ------------------------------
  
  // Calculate release rates

  double kr0relrate =  vkdoc * k0frac * k0exo;
  double krcarelrate =  vkdoc * k2frac * kcaexo;
  double krrelrate = kr0relrate + krcarelrate;
  
  double ff0relrate =  vfmob * f0frac * f0exo;
  double ffcarelrate =  vfmob * f5frac * fcaexo;
  double ffrelrate = ff0relrate + ffcarelrate;
  
  double totalrelrate = krrelrate + ffrelrate;
    
  double ca_cyt_flux = 0.0

    + (-k0 * 2 * kkf * ca_cyt) + (k1 * 1 * kkb)
    + (-k1 * 1 * kkf * ca_cyt) + (k2 * 2 * kbb * kkb) 

    + (-f0 * 5 * fkf * ca_cyt) + (f1 * fkb) 
    + (-f1 * 4 * fkf * ca_cyt) + (f2 * 2 * pow(fbb,1) * fkb)                      
    + (-f2 * 3 * fkf * ca_cyt) + (f3 * 3 * pow(fbb,2) * fkb) 
    + (-f3 * 2 * fkf * ca_cyt) + (f4 * 4 * pow(fbb,3) * fkb)  
    + (-f4 * 1 * fkf * ca_cyt) + (f5 * 5 * pow(fbb,4) * fkb);

  newinsilico::neuron_value(index, valnames["syt45_ca_cyt_flux"], ca_cyt_flux);
  newinsilico::neuron_value(index, valnames["syt45_krrelrate"], krrelrate);
  newinsilico::neuron_value(index, valnames["syt45_ffrelrate"], ffrelrate);
  newinsilico::neuron_value(index, valnames["syt45_totalrelrate"], totalrelrate);
};

void transmitter_release_syt4syt5::poisson_release(state_type &variables, const double t, unsigned index, 
						ar::random_class &rnum1, ar::random_class &rnum2, ar::random_class &rnum3,
						stringmap varnames,
						stringmap parnames,
						stringmap valnames)
{
  const double krrelrate = newinsilico::neuron_value(index, valnames["syt45_krrelrate"]); // KR release rate
  const double ffrelrate = newinsilico::neuron_value(index, valnames["syt45_ffrelrate"]); // FF release rate


  // ---------------------------------------------------------------------------
  double r1,r2,r3,random = 0;
  
  int krrelflag = 0;
  double krreltime = -1.0;
    
  int ffrelflag = 0;
  double ffreltime = -1.0;

  int relflag = 0;
  double reltime = -1.0;
  
  // Time until no release is allowed
  double reldelay =   newinsilico::neuron_value(index, parnames["syt45_reldelay"]);	

  r1 = rnum1.uni_double();
  r2 = rnum2.uni_double();
  r3 = rnum3.uni_double();

  if((krrelrate * gvars::DELTA_T) > r1 && (t > reldelay) ){
    krrelflag = 1;
    krreltime = t;
    relflag = 1;
    reltime = t;
    random = r1;
  }
  if((ffrelrate * gvars::DELTA_T) > r2 && (t > reldelay)){
    ffrelflag = 1;
    ffreltime = t;
    relflag = 1;
    reltime = t;
    random = r2;
  }

  // ------------------------------

  std::string reltype;
  
  if(krrelflag == 1)
    reltype = "KR";
  else if(ffrelflag == 1)
    reltype = "FF";
  if (relflag == 1)
    std::cout << " ---- " << reltype << " release from cell" <<  index << " at " << reltime << std::endl;

  // ----------------------------------
  // condition to limit the output file write
  // if(relflag>0){
  //   newinsilico::set_write_this_interval(true);
  // }
  // else{
  //   newinsilico::set_write_this_interval(false);
  // }

  // ------------------------------
  newinsilico::neuron_value(index, valnames["syt45_krrelflag"], krrelflag);
  newinsilico::neuron_value(index, valnames["syt45_krreltime"], krreltime);
    
  newinsilico::neuron_value(index, valnames["syt45_ffrelflag"], ffrelflag);
  newinsilico::neuron_value(index, valnames["syt45_ffreltime"], ffreltime);

  newinsilico::neuron_value(index, valnames["syt45_relflag"], relflag);
  newinsilico::neuron_value(index, valnames["syt45_reltime"], reltime);

  newinsilico::neuron_value(index, valnames["syt45_random"], random); 
}
