#ifndef PMCA_GILLESPIE_CLASS_HPP_INCLUDED
#define PMCA_GILLESPIE_CLASS_HPP_INCLUDED

#include <iostream>
#include <cmath>
#include <vector>

#include "physical_constants.hpp"
#include "stl_vector_operation_functions.hpp"

namespace consts=astron::phy_const;

namespace astron {
  namespace gillespie {
    namespace pmca {

      class pmca_gillespie_class
      {
      private:
	const unsigned int Nstates = 5; // [4 states ]
	const unsigned int Nreactions = 5; // Total of 5 reactions
	

	double k1 = 1.5E7;   // M^-1S^-1
	double k2 = 20.0;    // S^-1
	double k3 = 20.0;    // S^-1
	double k4 = 100.0;   // S^-1
	double kleak = 12.5; // S^-1

      public:
	static int objTot;		// Global object count
	static double time;		// Global running time
	//static int numCaIn;		// Global number of Calcium ions
	double volume = 0;

	double dt;			// Local gillespie time step
	unsigned int id = 0;		// Unique id for each object

	// Construct vectors
	std::vector<int> X; // Vector hold the states
	std::vector<double> H = {0,0,0,0,0}; //  Vector hold the product of reactants for each reaction
	std::vector<double> C = {kleak,k1/volume,k2,k3,k4}; // Vector hold the rate of each reaction adj. according from the reaction rate constant
  
	explicit pmca_gillespie_class(double volume_, std::vector<int> X_):volume(volume_), X(X_) // Default Class constructor 
	{
	  if(X.size() != Nstates){
	    std::cout << "Length of the state vector X is not equal to number of states. Aborting ...!" << std::endl;
	    return;
	  }
	  id = (++objTot);
	}
	void updateX (const int rx_id);
	void updateH (void);

	void update_variables(void);
	void first_object_calls(void);
	void all_object_calls(void);
	void display_variables(void);
      };
      // END PMCA_GILLESPIE_CLASS DECLARATION
      // SET ALL GLOBAL VARIABLES once in the header file

      // ----Default/mandatory gillespie class variables
      double pmca_gillespie_class::time = 0.0; // Default gillespie class variable for running time

      int pmca_gillespie_class::objTot = 0;
      //int pmca_gillespie_class::numCaIn = 0;

      // Define all functions here
      void pmca_gillespie_class::display_variables(void)
      {
	std::cout << "Obj_ID = " << id << " Time = " << time << std::endl;
	std::cout << "H = " << H << std::endl;
	std::cout << "C = " << C << std::endl;
      }
      // Function def: void first_object_calls(void)
      void pmca_gillespie_class::first_object_calls(void)
      {
	if(this->id == 1){
	  //std::cout << "The ID of this object == " << this->id << std::endl;
	  //X[0] = numCaIn;
	}
      }
      // Function def: void all_object_calls(void)
      void pmca_gillespie_class::all_object_calls(void)
      {
	//X[0] = numCaIn;
      }
      // update_variables()
      void pmca_gillespie_class::update_variables()
      {
      }
      // Function definition: void vgcc_gillespie_class:updateH()
      void pmca_gillespie_class::updateH()
      {
	//X[0] = numCaIn;
	
	H[0] = X[1];
	H[1] = X[0]*X[2];
	H[2] = X[3];
	H[3] = X[3];
	H[4] = X[4];
      };
      // Function definition: void vgcc_gillespie_class:updateX()
      void pmca_gillespie_class::updateX(const int rx_id)
      {
	//std::cout << "Reaction selected = " << rx_id << std::endl;
	//X[0] = numCaIn;
	switch(rx_id)
	  {
	  case 0:
	    {
	      X[0]++;  break;
	    }
	  case 1:
	    {
	      X[0]--; X[2]--; X[3]++;   break;
	    }
	  case 2:
	    {
	      X[3]--; X[2]++;  break;
	    }
	  case 3:
	    {
	      X[3]--; X[4]++;  break;
	    }
	  case 4:
	    {
	      X[4]--; X[2]++;  break;
	    }
	  }
	//numCaIn = X[0];
	for(size_t i=0; i < X.size();++i){
	  if(X[i] < 0){
	    X[i] = 0;
	  }
	}
      };  
    } // namespace pmca
  } // namespace gillespie
}   // namespace astron

#endif 				// PMCA_GILLESPIE_CLASS_HPP_INCLUDED
