// Time-stamp: <2017-10-05 14:42:59 anup>
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
#include "transmitter_release_syt4b.hpp"
#include "random_number_generator.hpp"

namespace consts=astron::phy_const;
namespace gvars=astron::globals;
namespace ar = astron::random;

void transmitter_release_syt4b::state_machine(state_type &variables, state_type &dxdt, const double t, unsigned index, 
					      stringmap varnames,
					      stringmap parnames,
					      stringmap valnames) 
{
  // Get all variable indices
  unsigned ca_cyt_index = newinsilico::get_neuron_index(index, "ca_cyt");

  // Sensor states
  unsigned h0_index = newinsilico::get_neuron_index(index, varnames["h0"]);
  unsigned h1_index = newinsilico::get_neuron_index(index, varnames["h1"]);
  unsigned h2_index = newinsilico::get_neuron_index(index, varnames["h2"]);

  // Vesicle release & recycling
  unsigned vrelrsd_index = newinsilico::get_neuron_index(index, varnames["vrelrsd"]);
  unsigned vrecrsd_index = newinsilico::get_neuron_index(index, varnames["vrecrsd"]);
  unsigned vrelnew_index = newinsilico::get_neuron_index(index, varnames["vrelnew"]);
  unsigned vrecnew_index = newinsilico::get_neuron_index(index, varnames["vrecnew"]);

  unsigned relfrac_index = newinsilico::get_neuron_index(index, varnames["relfrac"]);
  
  // Get all parameter values
  const double volume_cyt = newinsilico::neuron_value(index, "volume_cyt"); // Volume_Cyt (m^3)
  
  const double hf = newinsilico::neuron_value(index, parnames["hf"]);
  const double hb = newinsilico::neuron_value(index, parnames["hb"]);
  const double b = newinsilico::neuron_value(index, parnames["b"]);
  const double sponf = newinsilico::neuron_value(index, parnames["sponf"]);
  const double fastf = newinsilico::neuron_value(index, parnames["fastf"]);
  const double vesnum = newinsilico::neuron_value(index, parnames["vesnum"]);
  const double krecff = newinsilico::neuron_value(index, parnames["krecff"]);   // Forward recycling  rate full fusion
  const double kreckr = newinsilico::neuron_value(index, parnames["kreckr"]);   // Forward recycling rate kiss-and-run
  const double knr = newinsilico::neuron_value(index, parnames["knr"]);   // Newcomer to resident rate
  const double krelfrac = newinsilico::neuron_value(index, parnames["krelfrac"]);
  const double newvesfrac = newinsilico::neuron_value(index, parnames["newvesfrac"]);
  const double newrelfrac = newinsilico::neuron_value(index, parnames["newrelfrac"]); 
  
  // Set limits on variable values
  variables[ca_cyt_index] = std::max<double>(variables[ca_cyt_index],0.0);
  variables[h0_index] = std::max<double>(variables[h0_index],0.0);
  variables[h1_index] = std::max<double>(variables[h1_index],0.0);
  variables[h2_index] = std::max<double>(variables[h2_index],0.0);

  variables[vrelrsd_index] = std::max<double>(variables[vrelrsd_index],0.0);
  variables[vrecrsd_index] = std::max<double>(variables[vrecrsd_index],0.0);
  variables[vrelnew_index] = std::max<double>(variables[vrelnew_index],0.0);
  variables[vrecnew_index] = std::max<double>(variables[vrecnew_index],0.0);

  variables[relfrac_index] = std::max<double>(variables[relfrac_index],0.0);
  
  // Load initial values of glutamate_vesicles
  const double initcheck  = newinsilico::neuron_value(index, parnames["initcheck"]);
  if (initcheck <= 0) {
    variables[h0_index] = vesnum/(consts::R * volume_cyt * 1000);
    variables[vrelrsd_index] = (vesnum) * (1-newvesfrac);
    variables[vrelnew_index] = (vesnum) * newvesfrac;
    // Update initialization check value
    newinsilico::neuron_value(index, parnames["initcheck"], 1.0);
  }
  
  // Get all variable values
  double ca_cyt = variables[ca_cyt_index];

  double h0 = variables[h0_index];
  double h1 = variables[h1_index];
  double h2 = variables[h2_index];

  double vrelrsd = variables[vrelrsd_index]; 
  double vrecrsd = variables[vrecrsd_index];
  double vrelnew = variables[vrelnew_index]; 
  double vrecnew = variables[vrecnew_index];

  double relfrac = variables[relfrac_index];
  
  // --------------------------------------------
  // Time until no release is allowed
  double reldelay =   newinsilico::neuron_value(index, parnames["reldelay"]);
  
  // --------------------------------------------
  // Order of reactions: right, down, up, left
  
  dxdt[h0_index]  = (-h0 * 2 * hf * ca_cyt) + (h1 * hb);
  dxdt[h1_index]  = (-h1 * hf * ca_cyt)   + (h2 * 2 * b * hb) + (-h1 * hb) +   (h0 * 2 * hf * ca_cyt);
  dxdt[h2_index]  = (-h2 * 2 * b * hb) + (h1 * hf * ca_cyt); 

  // ------------------------------------------

  double h0frac = (h0 / (h0 + h1 + h2));
  double h2frac = (h2 / (h0 + h1 + h2));

  dxdt[vrelrsd_index] = 0.0
    + (- h0frac * vrelrsd * sponf )
    + (- h2frac * vrelrsd * fastf )
    + (+ (vrelnew - (vrelnew * newvesfrac)) * knr);

  dxdt[vrecrsd_index] = 0.0
    + (+ h0frac * vrelrsd * sponf )
    + (+ h2frac * vrelrsd * fastf )
    + (- vrecrsd * kreckr);

  dxdt[vrelnew_index] = 0.0
    + (- h0frac * vrelnew * sponf * relfrac )
    + (- h2frac * vrelnew * fastf * relfrac * newrelfrac)
    + (- (vrelnew - (vrelnew * newvesfrac)) * knr )
    + (+ vrecrsd * kreckr)
    + (+ vrecnew * krecff);

  dxdt[vrecnew_index] = 0.0
    + (+ h0frac * vrelnew * sponf * relfrac )
    + (+ h2frac * vrelnew * fastf * relfrac * newrelfrac)
    + (- vrecnew * krecff);

  // Calculate RRP
  double rrp = vrelrsd + vrelnew;

  // Calculate release rates
  double sponrelrate = 0.0
    + (+ h0frac * vrelrsd * sponf)
    + (+ h0frac * vrelnew * sponf * relfrac * newrelfrac);

  double fastrelrate = 0.0
    + (+ h2frac * vrelrsd * fastf )
    + (+ h2frac * vrelnew * fastf * relfrac * newrelfrac);

  double totalrelrate = sponrelrate + fastrelrate;

  double resrelrate = (h0frac * vrelrsd * sponf ) + (h2frac * vrelrsd * fastf );
  double newrelrate = (h0frac * vrelnew * sponf * relfrac) + (h2frac * vrelnew * fastf * relfrac * newrelfrac);
  
  double ca_cyt_flux = 0.0
    + (-h0 * 2 * hf * ca_cyt) + (h1 * hb)                     
    + (-h1 * hf * ca_cyt)   + (h2 * 2 * b * hb);
  
  dxdt[relfrac_index] = (-relfrac * resrelrate) + ((1-relfrac) * krelfrac);
  
  // Update parameter values
  newinsilico::neuron_value(index, valnames["ca_cyt_flux"], ca_cyt_flux);
  newinsilico::neuron_value(index, valnames["rrp"], rrp);
  newinsilico::neuron_value(index, valnames["sponrelrate"], sponrelrate);
  newinsilico::neuron_value(index, valnames["fastrelrate"], fastrelrate);
  newinsilico::neuron_value(index, valnames["totalrelrate"], totalrelrate);

  newinsilico::neuron_value(index, valnames["resrelrate"], resrelrate);
  newinsilico::neuron_value(index, valnames["newrelrate"], newrelrate);
  

};

void transmitter_release_syt4::poisson_release(state_type &variables, const double t, unsigned index, 
					       ar::random_class &rnum1, ar::random_class &rnum2, ar::random_class &rnum3,
					       stringmap varnames,
					       stringmap parnames,
					       stringmap valnames)
{
  const double sponrelrate = newinsilico::neuron_value(index, valnames["sponrelrate"]); // Rate for spontaneous release
  const double fastrelrate = newinsilico::neuron_value(index, valnames["fastrelrate"]); // Rate for fast release
  const double rrprelrate = newinsilico::neuron_value(index, valnames["resrelrate"]); // Rate for rrp release
  const double rsvrelrate = newinsilico::neuron_value(index, valnames["newrelrate"]); // Rate for reserve release

  // ---------------------------------------------------------------------------
  double r1,r2,r3,random = 0;
  
  int sponflag = 0;
  double spontime = -1.0;
    
  int fastflag = 0;
  double fasttime = -1.0;

  int rrpflag = 0;
  double rrptime = -1.0;

  int rsvflag = 0;
  double rsvtime = -1.0;

  int relflag = 0;
  double reltime = -1.0;
  
  // Time until no release is allowed
  double reldelay =   newinsilico::neuron_value(index, parnames["reldelay"]);	

  r1 = rnum1.uni_double();
  r2 = rnum2.uni_double();
  r3 = rnum3.uni_double();

  if((sponrelrate * gvars::DELTA_T) > r1 && (t > reldelay) ){
    sponflag = 1;
    spontime = t;
    relflag = 1;
    reltime = t;
    random = r1;
  }
  if((fastrelrate * gvars::DELTA_T) > r2 && (t > reldelay)){
    fastflag = 1;
    fasttime = t;
    relflag = 1;
    reltime = t;
    random = r2;
  }

  //  check which transmitter is released
  std::string str = varnames["h0"];
  std::string transmitter = "not found";
  if(str.find("gluves") < str.npos)
    transmitter = "glutamate";
  else if(str.find("atpves") < str.npos)
    transmitter = "atp";
  // check which type of release occured
  std::string reltype = "unknown transmitter";
  if(fastflag == 1)
    reltype = "fast";
  else if(sponflag == 1)
    reltype = "spontaneous";
  if (relflag == 1)
    std::cout << "*** " << reltype << " release of " << transmitter << " from cell" <<  index << " at " << reltime << std::endl;

  // ----------------------------------

  newinsilico::neuron_value(index, valnames["sponflag"], sponflag);
  newinsilico::neuron_value(index, valnames["spontime"], spontime);
    
  newinsilico::neuron_value(index, valnames["fastflag"], fastflag);
  newinsilico::neuron_value(index, valnames["fasttime"], fasttime);

  newinsilico::neuron_value(index, valnames["relflag"], relflag);
  newinsilico::neuron_value(index, valnames["reltime"], reltime);

  newinsilico::neuron_value(index, valnames["random"], random); 
}
