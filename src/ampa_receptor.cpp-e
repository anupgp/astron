// Time-stamp: <2019-01-05 16:43:42 macbookair>
// Units: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads
// Description: Generates AMPA receptor currents for a given glutamate concentration
// Note: The binding and unbinding of glutamate at the receptor will change local glutamate concentration. Currently this is not taken into account.  
// Ref: Peter Jonas & Sakmann 1993

#include <vector>
#include <iostream>
#include <cmath>

#include "include/new_insilico.hpp"

#include "data_types.hpp"
#include "physical_constants.hpp"
#include "ampa_receptor.hpp"

namespace consts=astron::phy_const;

void ampa_receptor::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{
  // Get indices of all pre cells that form synapses with this cell and has glu_ext variable declared 
  auto glu_ext_indices = newinsilico::get_pre_neuron_indices(index, "glu_ext");

  // Sum up all glu_ext from all the pre_neuron synapses

  auto glu_ext = 0.0;
  for(unsigned iter = 0; iter < glu_ext_indices.size(); ++iter) {
    glu_ext = glu_ext + std::max(variables[glu_ext_indices[iter]],0.0);
  }

  // Get post_neuron variable index

  unsigned V_index = newinsilico::get_neuron_index(index, "V");

  unsigned C0_index = newinsilico::get_neuron_index(index, "ampar_C0");
  unsigned C1_index = newinsilico::get_neuron_index(index, "ampar_C1");
  unsigned C2_index = newinsilico::get_neuron_index(index, "ampar_C2");
  unsigned C3_index = newinsilico::get_neuron_index(index, "ampar_C3");
  unsigned C4_index = newinsilico::get_neuron_index(index, "ampar_C4");
  unsigned C5_index = newinsilico::get_neuron_index(index, "ampar_C5");
  unsigned O_index = newinsilico::get_neuron_index(index, "ampar_O");  
  
  // Set lower limits on variable values

  variables[C0_index] = std::max<double>(variables[C0_index],0.0);
  variables[C1_index] = std::max<double>(variables[C1_index],0.0);
  variables[C2_index] = std::max<double>(variables[C2_index],0.0);
  variables[C3_index] = std::max<double>(variables[C3_index],0.0);
  variables[C4_index] = std::max<double>(variables[C4_index],0.0);
  variables[C5_index] = std::max<double>(variables[C5_index],0.0);
  variables[O_index] = std::max<double>(variables[O_index],0.0);

  // Get parameter values

  double E_ampar = newinsilico::neuron_value(index, "E_ampar");
  double G_ampar = newinsilico::neuron_value(index, "G_ampar");
  double n_ampar = newinsilico::neuron_value(index, "n_ampar");

  double k1 = newinsilico::neuron_value(index, "ampar_k1");
  double k1b = newinsilico::neuron_value(index, "ampar_k1b");
  double k2 = newinsilico::neuron_value(index, "ampar_k2");
  double k2b = newinsilico::neuron_value(index, "ampar_k2b");
  double k3 = newinsilico::neuron_value(index, "ampar_k3");
  double k3b = newinsilico::neuron_value(index, "ampar_k3b");
  double a = newinsilico::neuron_value(index, "ampar_a");
  double b = newinsilico::neuron_value(index, "ampar_b");
  double a1 = newinsilico::neuron_value(index, "ampar_a1");
  double b1 = newinsilico::neuron_value(index, "ampar_b1");
  double a2 = newinsilico::neuron_value(index, "ampar_a2");
  double b2 = newinsilico::neuron_value(index, "ampar_b2");
  double a3 = newinsilico::neuron_value(index, "ampar_a3");
  double b3 = newinsilico::neuron_value(index, "ampar_b3");
  double a4 = newinsilico::neuron_value(index, "ampar_a4");
  double b4 = newinsilico::neuron_value(index, "ampar_b4");

  // Get variable values

  double V = variables[V_index];
  
  double C0 = variables[C0_index];
  double C1 = variables[C1_index];
  double C2 = variables[C2_index];
  double C3 = variables[C3_index];
  double C4 = variables[C4_index];
  double C5 = variables[C5_index];
  double O = variables[O_index];

  // dxdt values
  dxdt[C0_index] = (-C0 * glu_ext * k1) + (C1 * k1b); 
  dxdt[C1_index] = (-C1 * glu_ext * k2) + (C2 * k2b) + (-C1 * a1) + (C3 * b1) + (-C1 * k1b) + (C0 * glu_ext * k1);
  dxdt[C2_index] = (-C2 * a) + (O * b) + (-C2 * a2) + (C4 * b2) + (-C2 * k2b) + (C1 * glu_ext * k2);
  dxdt[C3_index] = (-C3 * b1) + (C1 * a1) + (-C3 * glu_ext * k3) + (C4 * k3b);
  dxdt[C4_index] = (-C4 * a4) + (C5 * b4) + (-C4 * k3b) + (C3 * glu_ext * k3) + (-C4 * b2) + (-C2 * a2);
  dxdt[C5_index] = (-C5 * b4) + (C4 * a4) + (-C5 * b3) + (O * a3);
  dxdt[O_index] = (-O * b) + (C2 * a) + (-O * a3) + (C5 * b3);
  
  // double ampar_glu_flux = (-C0 * glu_ext * k1) + (C1 * k1b) + (-C1 * glu_ext * k2) + (C2 * k2b) + (-C3 * glu_ext * k3) + (C4 * k3b);

  double fraction_of_open_channels = (O/(C0 + C1 + C2 + C3 + C4 + C5 + O)); 
  double I_ampar = G_ampar * fraction_of_open_channels  * (V - E_ampar) * n_ampar;

  newinsilico::neuron_value(index, "I_ampar", I_ampar);
  newinsilico::neuron_value(index, "ampar_open_fraction", fraction_of_open_channels);
  newinsilico::neuron_value(index, "ampar_glu_flux", 0); // Note: needs to be modified as explained at the top!

};
