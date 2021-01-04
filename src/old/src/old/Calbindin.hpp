/* Last Revised Date: 08_APRIL_2015 */
/* Lastest status: not checked   */
#ifndef CALBINDIN_HPP_INCLUDED
#define CALBINDIN_HPP_INCLUDED

#include <vector>
#include <iostream>
#include <cmath>

#include "data_types.hpp"
#include "insilico-0.25/include/insilico/core.hpp"

//UNITS: all SI units - seconds, Volts, Ampere, Meters, Simenes, Farads

class Calbindin
{
public:
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index);
};

void Calbindin::current(state_type &variables, state_type &dxdt, const double t, unsigned index) 
{

  // Get all variable indices
  unsigned Ca_Cyt_index = insilico::engine::neuron_index(index, "Ca_Cyt");
  unsigned CbH0L0_index = insilico::engine::neuron_index(index, "CbH0L0");
  unsigned CbH1L0_index = insilico::engine::neuron_index(index, "CbH1L0");
  unsigned CbH2L0_index = insilico::engine::neuron_index(index, "CbH2L0");
  unsigned CbH3L0_index = insilico::engine::neuron_index(index, "CbH3L0");

  unsigned CbH0L1_index = insilico::engine::neuron_index(index, "CbH0L1");
  unsigned CbH1L1_index = insilico::engine::neuron_index(index, "CbH1L1");
  unsigned CbH2L1_index = insilico::engine::neuron_index(index, "CbH2L1");
  unsigned CbH3L1_index = insilico::engine::neuron_index(index, "CbH3L1");

  // Get parameter values  
  const double kon_f = insilico::engine::neuron_value(index, "kon_f");
  const double koff_f = insilico::engine::neuron_value(index, "koff_f");
  const double kon_s = insilico::engine::neuron_value(index, "kon_s");
  const double koff_s = insilico::engine::neuron_value(index, "koff_s");

  variables[CbH0L0_index] = std::max<double>(variables[CbH0L0_index],0.0);
  variables[CbH1L0_index] = std::max<double>(variables[CbH1L0_index],0.0);
  variables[CbH2L0_index] = std::max<double>(variables[CbH2L0_index],0.0);
  variables[CbH3L0_index] = std::max<double>(variables[CbH3L0_index],0.0);

  variables[CbH0L1_index] = std::max<double>(variables[CbH0L1_index],0.0);
  variables[CbH1L1_index] = std::max<double>(variables[CbH1L1_index],0.0);
  variables[CbH2L1_index] = std::max<double>(variables[CbH2L1_index],0.0);
  variables[CbH3L1_index] = std::max<double>(variables[CbH3L1_index],0.0);
  
  // Get variable values
  double Ca_Cyt = variables[Ca_Cyt_index];
  double CbH0L0 = variables[CbH0L0_index];
  double CbH1L0 = variables[CbH1L0_index];
  double CbH2L0 = variables[CbH2L0_index];
  double CbH3L0 = variables[CbH3L0_index];

  double CbH0L1 = variables[CbH0L1_index];
  double CbH1L1 = variables[CbH1L1_index];
  double CbH2L1 = variables[CbH2L1_index];
  double CbH3L1 = variables[CbH3L1_index];

  // Compute dxdt values
  dxdt[CbH0L0_index] = (-CbH0L0 * Ca_Cyt * 3 * kon_f) + (CbH1L0 * koff_f) + (-CbH0L0 * Ca_Cyt * kon_s) + (CbH0L1 * koff_s);
  dxdt[CbH1L0_index] = (-CbH1L0 * Ca_Cyt * 2 * kon_f) + (CbH2L0 * 2 * koff_f) + (-CbH1L0 * Ca_Cyt * kon_s) + (CbH1L1 * koff_s) + (-CbH1L0 * koff_f) + (CbH0L0 * Ca_Cyt * 3 * kon_f);
  dxdt[CbH2L0_index] = (-CbH2L0 * Ca_Cyt * kon_f) + (CbH3L0 * 3 * koff_f) + (-CbH2L0 * Ca_Cyt * kon_s) + (CbH2L1 * koff_s) + (-CbH2L0 * 2 * koff_f) + (CbH1L0 * Ca_Cyt * 2 * kon_f);
  dxdt[CbH3L0_index] = (-CbH3L0 * Ca_Cyt * kon_s) + (CbH3L1 * koff_s) + (-CbH3L0 * 3 * koff_f) + (CbH2L0 * Ca_Cyt * kon_f);
  
  dxdt[CbH0L1_index] = (-CbH0L1 * Ca_Cyt * 3 * kon_f) + (CbH1L1 * koff_f) + (-CbH0L1 * koff_s) + (CbH0L0 * Ca_Cyt * kon_s);
  dxdt[CbH1L1_index] = (-CbH1L1 * Ca_Cyt * 2 * kon_f) + (CbH2L1 * 2 * koff_f) + (-CbH1L1 * koff_s) + (CbH1L0 * Ca_Cyt * kon_s) + (-CbH1L1 * koff_f) + (CbH0L1 * Ca_Cyt * 3 * kon_f);
  dxdt[CbH2L1_index] = (-CbH2L1 * Ca_Cyt * kon_f) + (CbH3L1 * 3 * koff_f) + (-CbH2L1 * koff_s) + (CbH2L0 * Ca_Cyt * kon_s) + (-CbH2L1 * 2 * koff_f) + (CbH1L1 * Ca_Cyt * 2 * kon_f);
  dxdt[CbH3L1_index] = (-CbH3L1 * koff_s) + (CbH3L0 * Ca_Cyt * kon_s) + (-CbH3L1 * 3 * koff_f) + (CbH2L1 * Ca_Cyt * kon_f);

  double Calbindin_Ca_Cyt_dxdt = (-CbH0L0 * Ca_Cyt * 3 * kon_f) + (CbH1L0 * koff_f) + (-CbH1L0 * Ca_Cyt * 2 * kon_f) + (CbH2L0 * 2 * koff_f) + (-CbH2L0 * Ca_Cyt * kon_f) + (CbH3L0 * 3 * koff_f) +
    (-CbH0L0 * Ca_Cyt * kon_s) + (CbH0L1 * koff_s) + (-CbH1L0 * Ca_Cyt * kon_s) + (CbH1L1 * koff_s) + (-CbH2L0 * Ca_Cyt * kon_s) + (CbH2L1 * koff_s) + (-CbH3L0 * Ca_Cyt * kon_s) + (CbH3L1 * koff_s) +
    (-CbH0L1 * Ca_Cyt * 3 * kon_f) + (CbH1L1 * koff_f) + (-CbH1L1 * Ca_Cyt * 2 * kon_f) + (CbH2L1 * 2 * koff_f) + (-CbH2L1 * Ca_Cyt * kon_f) + (CbH3L1 * 3 * koff_f);

  // Update values

  double Cb_Total = CbH0L0 + CbH1L0 + CbH2L0 + CbH3L0 + CbH0L1 + CbH1L1 + CbH2L1 + CbH3L1;

  insilico::engine::neuron_value(index, "Calbindin_Ca_Cyt_dxdt", Calbindin_Ca_Cyt_dxdt);
  insilico::engine::neuron_value(index, "Cb_Total", Cb_Total);
};

#endif // CALBINDIN_HPP_INCLUDED`
