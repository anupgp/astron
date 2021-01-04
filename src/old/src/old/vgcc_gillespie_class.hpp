#ifndef VGCC_GILLESPIE_CLASS_HPP_INCLUDED
#define VGCC_GILLESPIE_CLASS_HPP_INCLUDED

#include <iostream>
#include <cmath>
#include <vector>

#include "physical_constants.hpp"
#include "stl_vector_operation_functions.hpp"

namespace consts=astron::phy_const;

namespace astron {
  namespace gillespie {
    namespace vgcc {

      class vgcc_gillespie_class
      {
      private:
	const double GCa = 0.2E-12; // Calcium channel single channel conductance
	const unsigned int Nstates = 5; // [5 VGCC states ]
	const unsigned int Nreactions = 8; // Total of 8 reactions

	double ECa = 0.0;		// Reversal potential of VGCC
	
	// Private Functions
	double alpha(const int rx_id);
	double beta(const int rx_id);
        void updateC (void);
	void update_ECa(void);    
      public:
	static int objTot;		// Global VGCC object count
	static double time;		// Global running time
	double dt;			// Local gillespie time step
	unsigned int id = 0;		// Unique id for each VGCC object
      
	static double V; 		// Global Voltage in volts;
	static int numCaFlux;	// Global Calcium influx
	static double I_Ca;		// Global Calcium current
	double volume = 0;

	static double conCaOut;	// Outside Calcium concentration is fixed (2 mM)
	static double conCaIn;	// Global outside Calcium concentration

	// Construct vectors
	std::vector<int> X; // Vector hold the initial number of channels in each state [C0 C1 C2 C3 O] + number of Calcium ions inside + number of Calcium ions outside
	std::vector<double> H = {0,0,0,0,0,0,0,0}; //  Vector hold the product of reactants for each reaction
	std::vector<double> C = {alpha(1),beta(1),alpha(2),beta(2),alpha(3),beta(3),alpha(4),beta(4)}; // Vector hold the rate of each reaction adj. according from the reaction rate constant
  
	explicit vgcc_gillespie_class(double volume_, std::vector<int> X_):volume(volume_), X(X_) // Default Class constructor 
	{
	  if(X.size() != Nstates){
	    std::cout << "Length of the state vector X is not equal to number of states. Aborting ...!" << std::endl;
	  }
	  id = (++objTot);
	}
	void updateX (const int rx_id);
	void updateH (void);
	
	void first_object_calls(void);
	void all_object_calls(void);
	void update_variables(void);
	void display_variables(void);
      };
      // END VGCC_GILLESPIE_CLASS DECLARATION
      // Set all global variables here


      double vgcc_gillespie_class::time = 0;

      int vgcc_gillespie_class::objTot = 0;

      int vgcc_gillespie_class::numCaFlux = 0.0;
      double vgcc_gillespie_class::I_Ca = 0.0;
      double vgcc_gillespie_class::conCaOut = 2E-03;	// Outside Calcium concentration is fixed (2 mM)
      double vgcc_gillespie_class::conCaIn = 0;
      double vgcc_gillespie_class::V = 0.0;
      
      void vgcc_gillespie_class::updateC()
      {
	C[0] = alpha(1);
	C[1] = beta(1);
	C[2] = alpha(2);
	C[3] = beta(2);
	C[4] = alpha(3);
	C[5] = beta(3);
	C[6] = alpha(4);
	C[7] = beta(4);
      }
	  
      void vgcc_gillespie_class::display_variables(void)
      {
	std::cout << "Obj_ID = " << id << " Time = " << time << " Voltage = " << V << std::endl;
	std::cout << "H = " << H << std::endl;
	std::cout << "C = " << C << std::endl;
      }

      // Function def: void first_object_calls(void)
      void vgcc_gillespie_class::first_object_calls(void)
      {
	if(this->id == 1){
	  //std::cout << "The ID of this object == " << this->id << std::endl;
	  numCaFlux = 0;	// numCaFlux is reset to zero for each dt run
	  I_Ca = 0.0;
	}
      }
      // Function def: void all_object_calls(void)
      void vgcc_gillespie_class::all_object_calls(void)
      {

      }
      // Function definition: void updateCa(void)
      void vgcc_gillespie_class::update_variables(void)
      {
	update_ECa();
	I_Ca = I_Ca + ( X[4] * GCa * (V - ECa) );
	numCaFlux = numCaFlux + abs(round( ( I_Ca * dt ) / (consts::Z_Ca * consts::F/consts::Av) ));
	//std::cout << "dt = " << dt << " numCaFlux = " << numCaFlux << " I_Ca = " << I_Ca << std::endl;
      }
      // Function definition: void update_ECa(void);  
      void vgcc_gillespie_class::update_ECa(void)
      {
	ECa = ( (consts::R * consts::T) / (consts::Z_Ca * consts::F) ) * log(conCaOut/conCaIn);
	//std::cout << "ECa = " << ECa << std::endl; 
      };
      // Function definition: double alpha(double V, int rx_id);
      double vgcc_gillespie_class::alpha(const int rx_id)
      {
	double value, a, v = 0.0;
	switch (rx_id){
	case 1:{
	  a = 4.04E03;     // sec^-1
	  v = 49.14E-03;     // V
	  break;
	}
	case 2:{
	  a = 6.70E03;     // sec^-1
	  v = 42.08E-03;     // V
	  break;
	}
	case 3:{
	  a = 4.39E03;     // sec^-1
	  v = 55.31E-03;     // V
	  break;
	}
	case 4:{
	  a = 17.33E03;     // sec^-1
	  v = 26.55E-03;     // V
	  break;
	}
	}
	value = a * exp( V/v);
	//std::cout << "value = " << value << std::endl;
	return (value);
	
      };
      // Function definition: double beta(double V, int rx_id); 
      double vgcc_gillespie_class::beta(const int rx_id)
      {
	double value, b, v = 0.0;
	switch (rx_id){
	case 1:{
	  b = 2.88E03;     // sec^-1
	  v = 49.14E-03;     // V
	  break;
	}
	case 2:{
	  b = 6.30E03;     // sec^-1
	  v = 42.08E-03;     // V
	  break;
	}
	case 3:{
	  b = 8.16E03;     // sec^-1
	  v = 55.31E-03;     // V
	  break;
	}
	case 4:{
	  b = 1.84E03;     // sec^-1
	  v = 26.55E-03;     // V
	  break;
	}
	}
	value = b * exp( -V/v);
	return value;
      };
    
      // Function definition: void vgcc_gillespie_class:updateH()
      void vgcc_gillespie_class::updateH()
      {
	H[0] = X[0];
	H[1] = X[1];
	H[2] = X[1];
	H[3] = X[2];
	H[4] = X[2];
	H[5] = X[3];
	H[6] = X[3];
	H[7] = X[4];
	updateC();
      };
      // Function definition: void vgcc_gillespie_class:updateX()
      void vgcc_gillespie_class::updateX(const int rx_id)
      {
	//std::cout << "Reaction selected = " << rx_id << std::endl;
	switch(rx_id)
	  {
	  case 0:
	    {
	      X[0]--; X[1]++;  break;
	    }
	  case 1:
	    {
	      X[1]--; X[0]++;   break;
	    }
	  case 2:
	    {
	      X[1]--; X[2]++;  break;
	    }
	  case 3:
	    {
	      X[2]--; X[1]++;  break;
	    }
	  case 4:
	    {
	      X[2]--; X[3]++;  break;
	    }
	  case 5:
	    {
	      X[3]--; X[2]++;  break;
	    }
	  case 6:
	    {
	      X[3]--; X[4]++;  break;
	    }
	  case 7:
	    {
	      X[4]--; X[3]++;  break;
	    }
	  }
	for(size_t i=0; i < X.size();++i){
	  if(X[i] < 0){
	    X[i] = 0;
	  }
	}
      };  
    } // namespace vgcc
  } // namespace gillespie
}   // namespace astron

#endif	// VGCC_GILLESPIE_CLASS_HPP_INCLUDED
