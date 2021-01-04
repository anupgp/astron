// Time-stamp: <2017-03-17 18:07:30 anup>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Ref: sun2007,bacaj2013, jackman2016

#include <vector>
#include <iostream>
#include <cmath>
#include <string>

#include "data_types.hpp"
#include "physical_constants.hpp"
#include "global_variables.hpp"

#include "insilico/core.hpp"
#include "transmitter_release_hybrid.hpp"
#include "random_number_generator.hpp"

namespace consts=astron::phy_const;
namespace gvars=astron::globals;
namespace ar = astron::random;
  
void transmitter_release_hybrid::state_machine(state_type &variables, state_type &dxdt, const double t, unsigned index, 
					     stringmap varnames, 
					     stringmap parnames,
					     stringmap valnames) 
{
  // Get all variable indices
  unsigned ca_cyt_index = newinsilico::get_neuron_index(index, "ca_cyt");
      
  // Sensor states
  unsigned h0l0_index = newinsilico::get_neuron_index(index, varnames["h0l0"]);
  unsigned h1l0_index = newinsilico::get_neuron_index(index, varnames["h1l0"]);
  unsigned h2l0_index = newinsilico::get_neuron_index(index, varnames["h2l0"]);

  unsigned h0l1_index = newinsilico::get_neuron_index(index, varnames["h0l1"]);
  unsigned h1l1_index = newinsilico::get_neuron_index(index, varnames["h1l1"]);
  unsigned h2l1_index = newinsilico::get_neuron_index(index, varnames["h2l1"]);

  unsigned h0l2_index = newinsilico::get_neuron_index(index, varnames["h0l2"]);
  unsigned h1l2_index = newinsilico::get_neuron_index(index, varnames["h1l2"]);
  unsigned h2l2_index = newinsilico::get_neuron_index(index, varnames["h2l2"]);

  // Sensor refractory period
  unsigned href_index = newinsilico::get_neuron_index(index, varnames["href"]);

  // Sensor recycling
  unsigned hff_index = newinsilico::get_neuron_index(index, varnames["hff"]);
  unsigned hkr_index = newinsilico::get_neuron_index(index, varnames["hkr"]);
        
  // Get all parameter values
  const double volume_cyt = newinsilico::neuron_value(index, "volume_cyt"); // Volume_Cyt (m^3)

  const double hf = newinsilico::neuron_value(index, parnames["hf"]); // Forward rate high sensitivity sensor
  const double hb = newinsilico::neuron_value(index, parnames["hb"]); // Backward rate high sensitivity sensor
  const double lf = newinsilico::neuron_value(index, parnames["lf"]); // Forward rate low sensitivity sensor
  const double lb = newinsilico::neuron_value(index, parnames["lb"]); // Backward rate low sensitivity sensor
  const double b = newinsilico::neuron_value(index, parnames["b"]); // A factor that gets multiplied to all backward reaction rates
  const double sponf = newinsilico::neuron_value(index, parnames["sponf"]); // Forward rate for spontaneous release
  const double slowf = newinsilico::neuron_value(index, parnames["slowf"]); // Forward rate for  slow release
  const double sslowf = newinsilico::neuron_value(index, parnames["sslowf"]); // Forward rate for super slow release
  const double refb = newinsilico::neuron_value(index, parnames["refb"]);     // Backward rate for refractory period
  const double recfff = newinsilico::neuron_value(index, parnames["recfff"]); // Forward recycling  rate full fusion
  const double reckrf = newinsilico::neuron_value(index, parnames["reckrf"]); // Forward recycling rate kiss-and-run
  const double probff = newinsilico::neuron_value(index, parnames["probff"]); // Probability of full fusion events
  
  // Set limits on variable values
  variables[ca_cyt_index] = std::max<double>(variables[ca_cyt_index],0.0);
  variables[h0l0_index] = std::max<double>(variables[h0l0_index],0.0);
  variables[h1l0_index] = std::max<double>(variables[h1l0_index],0.0);
  variables[h2l0_index] = std::max<double>(variables[h2l0_index],0.0);

  variables[h0l1_index] = std::max<double>(variables[h0l1_index],0.0);
  variables[h1l1_index] = std::max<double>(variables[h1l1_index],0.0);
  variables[h2l1_index] = std::max<double>(variables[h2l1_index],0.0);

  variables[h0l2_index] = std::max<double>(variables[h0l2_index],0.0);
  variables[h1l2_index] = std::max<double>(variables[h1l2_index],0.0);
  variables[h2l2_index] = std::max<double>(variables[h2l2_index],0.0);
    
  // Variables for sensor refcyling
  variables[hff_index] = std::max<double>(variables[hff_index],0.0);
  variables[hkr_index] = std::max<double>(variables[hkr_index],0.0);

  // Variable for sensor refractory period
  variables[href_index] = std::max<double>(variables[href_index],0.0);
  
  // Load initial values of glutamate_vesicles
  const double initcheck  = newinsilico::neuron_value(index, parnames["initcheck"]);
  const double vesnum = newinsilico::neuron_value(index, parnames["vesnum"]);
  if (initcheck <= 0) {
    variables[h0l0_index] = (vesnum) / (consts::Av * volume_cyt * 1000);
    // Update initialization check value
    newinsilico::neuron_value(index, parnames["initcheck"], 1.0);
  }

  // -------------------
  // check whether refractory period is needed
  const double refon  = newinsilico::neuron_value(index, parnames["refon"]);
  // -------------------
  
  // Get all variable values
  double ca_cyt = variables[ca_cyt_index];

  double h0l0 = variables[h0l0_index];
  double h1l0 = variables[h1l0_index];
  double h2l0 = variables[h2l0_index];
			  	         
  double h0l1 = variables[h0l1_index];
  double h1l1 = variables[h1l1_index];
  double h2l1 = variables[h2l1_index];

  double h0l2 = variables[h0l2_index];
  double h1l2 = variables[h1l2_index];
  double h2l2 = variables[h2l2_index];

  double href =std::max<double>(variables[href_index],0.0); // Variables for a refractory period
  double hff = variables[hff_index]; // Variable for vesicles released via full fusion events
  double hkr = variables[hkr_index]; // Variable for vesicles released via kiss-and-run events

  // --------------------------------------------
  // Time until no release is allowed
  // double reldelay =   newinsilico::neuron_value(index, parnames["reldelay"]);
  
  // --------------------------------------------
  // Order of reactions: right, down, up, left
  // std::cout << sponf << " " << synf << " " << asynf << " " << freezeb << " " << offb << std::endl;
  dxdt[h0l0_index] = (-h0l0*2*hf*ca_cyt) + (h1l0*1*hb)   + (-h0l0*2*lf*ca_cyt) + (h0l1*lb)                                                                                  + (hff*recfff) + (hkr*reckrf) + (-h0l0 * sponf * href);
  dxdt[h1l0_index] = (-h1l0*1*hf*ca_cyt) + (h2l0*2*hb*b) + (-h1l0*2*lf*ca_cyt) + (h1l1*lb)                                           + (-h1l0*1*hb) +   (h0l0*2*hf*ca_cyt);
  dxdt[h2l0_index] =                                       (-h2l0*2*lf*ca_cyt) + (h2l1*lb)                                           + (-h2l0*2*hb*b) + (h1l0*1*hf*ca_cyt)  + (-h2l0 * slowf * href);

  dxdt[h0l1_index] = (-h0l1*2*hf*ca_cyt) + (h1l1*1*hb)   + (-h0l1*lf*ca_cyt)   + (h0l2*2*lb*b) + (-h0l1*lb)     + (h0l0*2*lf*ca_cyt);     
  dxdt[h1l1_index] = (-h1l1*1*hf*ca_cyt) + (h2l1*2*hb*b) + (-h1l1*lf*ca_cyt)   + (h1l2*2*lb*b) + (-h1l1*lb)     + (h1l0*2*lf*ca_cyt) + (-h1l1*1*hb) +   (h0l1*2*hf*ca_cyt); 
  dxdt[h2l1_index] =                                       (-h2l1*lf*ca_cyt)   + (h2l2*2*lb*b) + (-h2l1*lb)     + (h2l0*2*lf*ca_cyt) + (-h2l1*2*hb*b) + (h1l1*1*hf*ca_cyt)  + (-h2l1 * slowf * href);
  
  dxdt[h0l2_index] = (-h0l2*2*hf*ca_cyt) + (h1l2*1*hb)                                         + (-h0l2*2*lb*b) + (h0l1*lf*ca_cyt)                                          + (-h0l2 * sslowf * href);     
  dxdt[h1l2_index] = (-h1l2*1*hf*ca_cyt) + (h2l2*2*hb*b)                                       + (-h1l2*2*lb*b) + (h1l1*lf*ca_cyt)   + (-h1l2*1*hb)  +  (h0l2*2*hf*ca_cyt)  + (-h1l2 * sslowf * href);    
  dxdt[h2l2_index] =                                                                             (-h2l2*2*lb*b) + (h2l1*lf*ca_cyt)   + (-h2l2*2*hb*b) + (h1l2*1*hf*ca_cyt)  + (-h2l2 * slowf * href) + (-h2l2 * sslowf * href); 

  // Calculate RRP
  double rrp = (
		(0
		 + h0l0 + h1l0 + h2l0
		 + h0l1 + h1l1 + h2l1
		 + h0l2 + h1l2 + h2l2
		 )
		* (consts::Av * volume_cyt * 1000));

  // Calculate total release rate
  double trr = ((h0l0 * sponf) + ((h2l0 + h2l1 + h2l2) * slowf) +  ((h0l2 + h1l2 + h2l2) * sslowf));

  // Implementing the refractory period using a cost/punishment function
  // dxdt[href_index] = (-href * trr * refon * (consts::Av * volume_cyt * 1000) / vesnum) + ((1-href) * refb * refon);
  dxdt[href_index] = (-href * trr * refon * (consts::Av * volume_cyt * 1000)) + ((1-href) * refb * refon);
  // dxdt[href_index] = (-href * trr * refon * (consts::Av * volume_cyt * 1000)) + ((1-href) * refb * refon);

  // Implementing vesicular releasr via kiss-and-run and full-fusion
  // Vesicles released via full-fusions and via kiss-and-run are recycled back to the initial state
  dxdt[hff_index] = (-hff*recfff) + (probff * trr * href);
  dxdt[hkr_index] = (-hkr*reckrf) + ((1-probff) * trr * href);
  
  double ca_cyt_flux = 0.0
    + (-h0l0*2*hf*ca_cyt) + (h1l0*1*hb) +         (-h0l0*2*lf*ca_cyt) + (h0l1*lb)
    + (-h1l0*1*hf*ca_cyt) + (h2l0*2*hb*b) +       (-h1l0*2*lf*ca_cyt) + (h1l1*lb)          + (h1l0*1*hb) +   (-h0l0*2*hf*ca_cyt)
    +                                             (-h2l0*2*lf*ca_cyt) + (h2l1*lb)          + (h2l0*2*hb*b) + (-h1l0*1*hf*ca_cyt)                                        
			                                                                                                                                                                       
    + (-h0l1*2*hf*ca_cyt) + (h1l1*1*hb) +         (-h0l1*lf*ca_cyt) + (h0l2*2*lb*b)        + (h0l1*lb)     + (-h0l0*2*lf*ca_cyt)
    + (-h1l1*1*hf*ca_cyt) + (h2l1*2*hb*b) +       (-h1l1*lf*ca_cyt) + (h1l2*2*lb*b)        + (h1l1*lb)     + (-h1l0*2*lf*ca_cyt) + (h1l1*1*hb) +   (-h0l1*2*hf*ca_cyt)
    +                                             (-h2l1*lf*ca_cyt) + (h2l2*2*lb*b)        + (h2l1*lb)     + (-h2l0*2*lf*ca_cyt) + (h2l1*2*hb*b) + (-h1l1*1*hf*ca_cyt)

    + (-h0l2*2*hf*ca_cyt) + (h1l2*1*hb)                                                    + (h0l2*2*lb*b) + (-h0l1*lf*ca_cyt)
    + (-h1l2*1*hf*ca_cyt) + (h2l2*2*hb*b)                                                  + (h1l2*2*lb*b) + (-h1l1*lf*ca_cyt)   + (h1l2*1*hb)  +  (-h0l2*2*hf*ca_cyt)
    +                                                                                      + (h2l2*2*lb*b) + (-h2l1*lf*ca_cyt)   + (h2l2*2*hb*b) + (-h1l2*1*hf*ca_cyt);
   
  double sponrelrate = (h0l0 * sponf) * href * (consts::Av * volume_cyt * 1000);
  double slowrelrate = (h2l0 + h2l1 + h2l2) * slowf * href * (consts::Av * volume_cyt * 1000);
  double sslowrelrate = (h0l2 + h1l2 + h2l2) * sslowf * href * (consts::Av * volume_cyt * 1000);
  double totalrelrate = sponrelrate + slowrelrate + sslowrelrate;
 
  // Update parameter values
  newinsilico::neuron_value(index, valnames["ca_cyt_flux"], ca_cyt_flux);
  newinsilico::neuron_value(index, valnames["rrp"], rrp);
  newinsilico::neuron_value(index, valnames["sponrelrate"], sponrelrate);
  newinsilico::neuron_value(index, valnames["slowrelrate"], slowrelrate);
  newinsilico::neuron_value(index, valnames["sslowrelrate"], sslowrelrate);
  newinsilico::neuron_value(index, valnames["totalrelrate"], totalrelrate);
};

void transmitter_release_hybrid::update_release(state_type &variables, const double t, unsigned index,
							  ar::random_class &rnum1, ar::random_class &rnum2, ar::random_class &rnum3,
							  ar::random_class &rnum4,
							  stringmap varnames, 
							  stringmap parnames,
							  stringmap valnames) 
{   

  // Get parameter values
  const double sponrelrate = newinsilico::neuron_value(index, valnames["sponrelrate"]); // Forward rate for spontaneous release
  const double slowrelrate = newinsilico::neuron_value(index, valnames["slowrelrate"]); // Forward rate for synchronous release
  const double sslowrelrate = newinsilico::neuron_value(index, valnames["sslowrelrate"]); // Forward rate for asynchronous release

  const double probff = newinsilico::neuron_value(index, parnames["probff"]); // Percentage of full fusions
  
  int ffflag = 0;
  int krflag = 0;

  // ---------------------------------------------------------------------------
  double r1,r2,r3,r4,random = 0;
  
  int sponflag = 0;
  double spontime = -1.0;
    
  int slowflag = 0;
  double slowtime = -1.0;

  int sslowflag = 0;
  double sslowtime = -1.0;

  int relflag = 0;
  double reltime = -1.0;
  
  // Time until no release is allowed
  double reldelay =   newinsilico::neuron_value(index, parnames["reldelay"]);	

  r1 = rnum1.uni_double();
  r2 = rnum2.uni_double();
  r3 = rnum3.uni_double();
  r4 = rnum4.uni_double();

  if((sponrelrate * gvars::DELTA_T) > r1 && (t > reldelay) ){
    sponflag = 1;
    spontime = t;
    relflag = 1;
    reltime = t;
    random = r1;
  }
  if((slowrelrate * gvars::DELTA_T) > r2 && (t > reldelay)){
    slowflag = 1;
    slowtime = t;
    relflag = 1;
    reltime = t;
    random = r2;
  }
  if((sslowrelrate * gvars::DELTA_T) > r3 && (t > reldelay)){
    sslowflag = 1;
    sslowtime = t;
    relflag = 1;
    reltime = t;
    random = r3;
  }

  if (relflag){
    // ---------------------------------------------------------------------------
    // Throw dice here to decide whether it is full-fusion or kiss-and-run release
    // Check for the percentage of full-fusion by calling the random number
    // Update the released vesicles via full-fusions or kiss-and-run
    if (probff  >= r4){
      ffflag = 1;
      krflag = 0;
    }
    else{
      ffflag = 0;
      krflag = 1;
    }
    //  check which transmitter is released
    std::string str = varnames["h0l0"];
    std::string transmitter = "not found";
    if(str.find("gluves") < str.npos)
      transmitter = "glutamate";
    else if(str.find("atpves") < str.npos)
      transmitter = "atp";
    // check which type of release occured
    std::string reltype = "unknown transmitter";
    if(slowflag)
      reltype = "slow";
    else if(sslowflag)
      reltype = "super slow";
    else if(sponflag)
      reltype = "spontaneous";
    std::cout << "*** " << reltype << " release of " << transmitter << " from cell" <<  index << " at " << reltime << std::endl;
  }    
  // ----------------------------------
  newinsilico::neuron_value(index, valnames["ffflag"], ffflag);
  newinsilico::neuron_value(index, valnames["krflag"], krflag);
    
  newinsilico::neuron_value(index, valnames["sponflag"], sponflag);
  newinsilico::neuron_value(index, valnames["spontime"], spontime);
    
  newinsilico::neuron_value(index, valnames["slowflag"], slowflag);
  newinsilico::neuron_value(index, valnames["slowtime"], slowtime);

  newinsilico::neuron_value(index, valnames["sslowflag"], sslowflag);
  newinsilico::neuron_value(index, valnames["sslowtime"], sslowtime);

  newinsilico::neuron_value(index, valnames["relflag"], relflag);
  newinsilico::neuron_value(index, valnames["reltime"], reltime);

  newinsilico::neuron_value(index, valnames["random"], random); 

}
