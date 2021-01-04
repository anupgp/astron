#ifndef CA_SENSOR_GILLESPIE_CLASS_HPP_INCLUDED
#define CA_SENSOR_GILLESPIE_CLASS_HPP_INCLUDED

#include <iostream>
#include <cmath>
#include <vector>

#include <stl_vector_operation_functions.hpp>

namespace astron {
  namespace gillespie {

    class ca_sensor_gillespie_class
    {
    private:
				
      const double A = 1.91E08;      //M^-1 S^-1
      const double B = 2.32E03;	 //S^-1
      const double S = 3.68E06;	 //M^-1 * S^-1
      const double D = 13;		 //S^-1
      const double b = 0.25;	 //M^-1 S^-1
      const double G1 = 0.417E-03;	 // Spontaneous release rate 0.417E-03 S^-1
      const double G2 = 2E3;	 // Synchronous relase rate 2E3 S^-1
      const double G3 = 50;		 // Asynchronous release rate 50 S^-1
      const double LR = 1 / 10;	 // Sensor local reset rate S^-1
      
  
      const double relDelay = 6.34E-03;

    public:

      static int conCaIn; // Global variable to hold the concentration of calcium
      static double time; // Global time
      double dt;	  // Local gillespie_time step
      static int objTot;  // Global sensor count
      static double volume;	// Reaction volume

      static bool relFlag;		// Release flag
      static double lastRelTime;	// Time of last release

      static int sponRelcount;	// Global Spontaneous release rate
      static int asynRelcount;	// Global Asynchronous release rate
      static int synRelcount;	// Global synchronous release rate

      static int totalRelcount;

      static double lbin_time;	 // Global last bin time
  
      const double bin_rate = 1E-03; // Set bin rate

      unsigned int id = 0;		// Unique id of each sensor object

      const double avagadro = 6.022e+23;
      const unsigned int Nstates = 21; // 18 states of sensor + 3 released states (Spon, Syn, Asyn) = 21
      const unsigned int Nreactions = 67; // 68 possible reactions

      //Construct vectors
      std::vector<int> X;      // A vector to hold the initial number of the receptors in each states [XOYO, X1Y0, X2Y0 ... X5Y2]
      std::vector<double> H = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			       0,0,0,0,0,0,0};  //A vector to hold product of reactant molecules for each reaction
      std::vector<double> C = { 5 * A / volume, 4 * A / volume, 3 * A / volume, 2 * A / volume, A / volume,
				5 * A / volume, 4 * A / volume, 3 * A / volume, 2 * A / volume, A / volume,
				5 * A / volume, 4 * A / volume, 3 * A / volume, 2 * A / volume, A / volume,
				B, 2 * b * B, 3 * b * b * B, 4 * b * b * b * B, 5 * b * b * b * b * B,
				B, 2 * b * B, 3 * b * b * B, 4 * b * b * b * B, 5 * b * b * b * b * B,
				B, 2 * b * B, 3 * b * b * B, 4 * b * b * b * B, 5 * b * b * b * b * B,
				2 * S / volume, 2 * S / volume, 2 * S / volume, 2 * S / volume, 2 * S / volume, 2 * S / volume,
				S / volume, S / volume, S / volume, S / volume, S / volume, S / volume,
				D, D, D, D, D, D,
				2 * b * D, 2 * b * D, 2 * b * D, 2 * b * D, 2 * b * D, 2 * b * D,
				G1 , LR,
				G2 , G2 , G2 , LR,
				G3 , G3 , G3 , G3 , G3 , G3 , LR,
      };
      // C: Vector that hold the rate of each reaction adjusted according from the reaction rate constants 
      // -------------------------

      //Class constructors
      explicit ca_sensor_gillespie_class(std::vector<int> X_):X(X_) // Default constructor
      {
	if(X.size() != Nstates){
	  std::cout << "Length of the state vector X is not equal to number of states. Aborting ...!" << std::endl;
	}
	id = (++objTot);
      }
      // Copy constructor
      // explicit ca_sensor_gillespie_class(const ca_sensor_gillespie_class &ca_sensor_obj): X(ca_sensor_obj.X)  
      // {
      //   id += (++objTot);
      // }

      void updateX (const int rx_id);
      void updateH (void);
  
      void update_variables(void);
      void first_object_calls(void);
      void all_object_calls(void);

      void update_release_rate (void);
      void reset_relFlag(void);
    };
    //----------------------
    // SET ALL GLOBAL VARIABLES once in the header file

    // ----Default/mandatory gillespie class variables
    double ca_sensor_gillespie_class::time = 0.0; // Default gillespie class variable for running time
    double ca_sensor_gillespie_class::volume = 0;      // Default gillespie class variable for volume
    
    //-----Specific variables for Ca-Sensor-gillespie class
    int ca_sensor_gillespie_class::conCaIn = 0; // Calcium concentration is set to zero during sensor initializing
    double ca_sensor_gillespie_class::lbin_time = 0.0; // Sensor last bin time is set to zero at initialization

    int ca_sensor_gillespie_class::objTot = 0;

    int ca_sensor_gillespie_class::sponRelcount = 0;
    int ca_sensor_gillespie_class::synRelcount = 0;
    int ca_sensor_gillespie_class::asynRelcount = 0;

    int ca_sensor_gillespie_class::totalRelcount = 0;

    bool ca_sensor_gillespie_class::relFlag = 1;
    double ca_sensor_gillespie_class::lastRelTime = 0;

    //----------------------
    void ca_sensor_gillespie_class::update_release_rate(void)
    {
      //std::cout << "In UPDATE_RELEASE_FUNCTION " << std::endl;
      if ( (time - lbin_time) >= bin_rate ){
	//std::cout << "Updating rate " << std::endl;
	sponRelcount = 0;
	synRelcount = 0;
	asynRelcount = 0;

	lbin_time = time;
      }
    }
    // 
    void ca_sensor_gillespie_class::reset_relFlag(void)
    {
      if ( (!relFlag) && ( time > ( lastRelTime + relDelay) ) ){
	relFlag = 1;
      }
    }
    // Function def: void first_object_calls(void)
    void ca_sensor_gillespie_class::first_object_calls(void)
    {
      if(this->id == 1){
	std::cout << "The ID of this object == " << this->id << std::endl;
      }
    }
    // Function def: void all_object_calls(void)
    void ca_sensor_gillespie_class::all_object_calls(void)
    {
      reset_relFlag();
      update_release_rate();
    }
    // Function definition: void updateCa(void)
    void ca_sensor_gillespie_class::update_variables(void)
    {
     
    }
    //--------------------
    /* Function update H_mew vector with the current number of molecules in each state from the state vector X */
    void ca_sensor_gillespie_class::updateH()
    {
      H[0] = X[0] * conCaIn;
      H[1] = X[1] * conCaIn;
      H[2] = X[2] * conCaIn;
      H[3] = X[3] * conCaIn;
      H[4] = X[4] * conCaIn;

      H[5] = X[6] * conCaIn;
      H[6] = X[7] * conCaIn;
      H[7] = X[8] * conCaIn;
      H[8] = X[9] * conCaIn;
      H[9] = X[10] * conCaIn;

      H[10] = X[12] * conCaIn;
      H[11] = X[13] * conCaIn;
      H[12] = X[14] * conCaIn;
      H[13] = X[15] * conCaIn;
      H[14] = X[16] * conCaIn;

      H[15] = X[1];
      H[16] = X[2];
      H[17] = X[3];
      H[18] = X[4];
      H[19] = X[5];

      H[20] = X[7];
      H[21] = X[8];
      H[22] = X[9];
      H[23] = X[10];
      H[24] = X[11];

      H[25] = X[13];
      H[26] = X[14];
      H[27] = X[15];
      H[28] = X[16];
      H[29] = X[17];

      H[30] = X[0] * conCaIn;
      H[31] = X[1] * conCaIn;
      H[32] = X[2] * conCaIn;
      H[33] = X[3] * conCaIn;
      H[34] = X[4] * conCaIn;
      H[35] = X[5] * conCaIn;

      H[36] = X[6] * conCaIn;
      H[37] = X[7] * conCaIn;
      H[38] = X[8] * conCaIn;
      H[39] = X[9] * conCaIn;
      H[40] = X[10] * conCaIn;
      H[41] = X[11] * conCaIn;

      H[42] = X[6];
      H[43] = X[7];
      H[44] = X[8];
      H[45] = X[9];
      H[46] = X[10];
      H[47] = X[11];

      H[48] = X[12];
      H[49] = X[13];
      H[50] = X[14];
      H[51] = X[15];
      H[52] = X[16];
      H[53] = X[17];
      // Spontaneous release
      H[54] = X[0] * relFlag;
      H[55] = X[18];
      // Synchronous release
      H[56] = X[5] * relFlag;
      H[57] = X[11] * relFlag;
      H[58] = X[17] * relFlag;
      H[59] = X[19];
      // Asynchronous release
      H[60] = X[12] * relFlag;
      H[61] = X[13] * relFlag;
      H[62] = X[14] * relFlag;
      H[63] = X[15] * relFlag;
      H[64] = X[16] * relFlag;
      H[65] = X[17] * relFlag;
      H[66] = X[20];
      //-----------
      reset_relFlag();
      update_release_rate();
    }
    //Function update the state vector X for a given reaction rx_id
    void ca_sensor_gillespie_class::updateX(const int rx_id)
    {
      //std::cout << "Reaction " << rx_id << " X in " << X;
      switch(rx_id)
	{
	case 0:
	  {
	    X[0]--;  conCaIn--;  X[1]++;  break;
	  }
	case 1:
	  {
	    X[1]--;  conCaIn--;  X[2]++;   break;
	  }
	case 2:
	  {
	    X[2]--;  conCaIn--;  X[3]++;  break;
	  }
	case 3:
	  {
	    X[3]--; conCaIn--;   X[4]++;  break;
	  }
	case 4:
	  {
	    X[4]--;  conCaIn--;  X[5]++;  break;
	  }
	case 5:
	  {
	    X[6]--;  conCaIn--;  X[7]++;  break;
	  }
	case 6:
	  {
	    X[7]--;  conCaIn--;  X[8]++;  break;
	  }
	case 7:
	  {
	    X[8]--;  conCaIn--;  X[9]++;  break;
	  }
	case 8:
	  {
	    X[9]--;  conCaIn--;  X[10]++; break;
	  }
	case 9:
	  {
	    X[10]--; conCaIn--;  X[11]++; break;
	  }
	case 10:
	  {
	    X[12]--; conCaIn--;  X[13]++; break;
	  }
	case 11:
	  {
	    X[13]--; conCaIn--;  X[14]++; break;
	  }
	case 12:
	  {
	    X[14]--; conCaIn--;  X[15]++; break;
	  }
	case 13:
	  {
	    X[15]--; conCaIn--;  X[16]++; break;
	  }
	case 14:
	  {
	    X[16]--; conCaIn--;  X[17]++; break;
	  }
	  //-------------------------------------
	case 15:
	  {
	    X[1]--;  X[0]++;  conCaIn++;  break;
	  }
	case 16:
	  {
	    X[2]--;  X[1]++;  conCaIn++;  break;
	  }
	case 17:
	  {
	    X[3]--;  X[2]++;  conCaIn++;  break;
	  }
	case 18:
	  {
	    X[4]--;  X[3]++;  conCaIn++;  break;
	  }
	case 19:
	  {
	    X[5]--;  X[4]++;  conCaIn++;  break;
	  }
	case 20:
	  {
	    X[7]--;  X[6]++;  conCaIn++;  break;
	  }
	case 21:
	  {
	    X[8]--;  X[7]++;  conCaIn++; break;
	  }
	case 22:
	  {
	    X[9]--;  X[8]++;  conCaIn++;  break;
	  }
	case 23:
	  {
	    X[10]--; X[9]++;  conCaIn++;  break;
	  }
	case 24:
	  {
	    X[11]--; X[10]++; conCaIn++;  break;
	  }
	case 25:
	  {
	    X[13]--; X[12]++; conCaIn++;  break;
	  }
	case 26:
	  {
	    X[14]--; X[13]++; conCaIn++;  break;
	  }
	case 27:
	  {
	    X[15]--; X[14]++; conCaIn++;  break;
	  }
	case 28:
	  {
	    X[16]--; X[15]++; conCaIn++;  break;
	  }
	case 29:
	  {
	    X[17]--; X[16]++; conCaIn++;  break;
	  }
	  //------------------------------------
	case 30:
	  {
	    X[0]--; conCaIn--;   X[6]++;  break;
	  }
	case 31:
	  {
	    X[1]--;  conCaIn--;  X[7]++;  break;
	  }
	case 32:
	  {
	    X[2]--;  conCaIn--;  X[8]++;  break;
	  }
	case 33:
	  {
	    X[3]--;  conCaIn--;  X[9]++;  break;
	  }
	case 34:
	  {
	    X[4]--;  conCaIn--;  X[10]++; break;
	  }
	case 35:
	  {
	    X[5]--;  conCaIn--;  X[11]++; break;
	  }
	case 36:
	  {
	    X[6]--;  conCaIn--;  X[12]++; break;
	  }
	case 37:
	  {
	    X[7]--;  conCaIn--;  X[13]++; break;
	  }
	case 38:
	  {
	    X[8]--;  conCaIn--;  X[14]++; break;
	  }
	case 39:
	  {
	    X[9]--;  conCaIn--;  X[15]++; break;
	  }
	case 40:
	  {
	    X[10]--; conCaIn--;  X[16]++; break;
	  }
	case 41:
	  {
	    X[11]--; conCaIn--;  X[17]++; break;
	  }
	  //------------------------------------
	case 42:
	  {
	    X[6]--;  X[0]++;  conCaIn++;  break;
	  }
	case 43:
	  {
	    X[7]--;  X[1]++;  conCaIn++;  break;
	  }
	case 44:
	  {
	    X[8]--;  X[2]++;  conCaIn++;  break;
	  }
	case 45:
	  {
	    X[9]--;  X[3]++;  conCaIn++;  break;
	  }
	case 46:
	  {
	    X[10]--; X[4]++;  conCaIn++;  break;
	  }
	case 47:
	  {
	    X[11]--; X[5]++;  conCaIn++;  break;
	  }
	case 48:
	  {
	    X[12]--; X[6]++;  conCaIn++;  break;
	  }
	case 49:
	  {
	    X[13]--; X[7]++;  conCaIn++;  break;
	  }
	case 50:
	  {
	    X[14]--; X[8]++;  conCaIn++;  break;
	  }
	case 51:
	  {
	    X[15]--; X[9]++;  conCaIn++;  break;
	  }
	case 52:
	  {
	    X[16]--; X[10]++; conCaIn++;  break;
	  }
	case 53:
	  {
	    X[17]--; X[11]++; conCaIn++;  break;
	  }
	  //-----------------------------------
	  // Spontaneous release
	case 54:
	  {
	    X[0]--;  X[18]++; sponRelcount++;  totalRelcount++; relFlag = 0; lastRelTime = time; break;
	  }
	case 55:
	  {
	    X[18]--; X[0]++;  break;
	  }
	  //-----------------------------------
	  // Synchronous release
	case 56:
	  {
	    X[5]--;    X[19]++; synRelcount++; totalRelcount++; relFlag = 0; lastRelTime = time; break;
	  }
	case 57:
	  {
	    X[11]--;   X[19]++; synRelcount++; totalRelcount++; relFlag = 0; lastRelTime = time;  break;
	  }
	case 58:
	  {
	    X[17]--;   X[19]++; synRelcount++;  totalRelcount++; relFlag = 0; lastRelTime = time; break;
	  }
	case 59:
	  {
	    X[19]--; X[0]++;  break;
	  }
	  //-----------------------------------
	  // Asynchronous release
	case 60:
	  {
	    X[12]--; X[20]++; asynRelcount++; totalRelcount++; relFlag = 0; lastRelTime = time; break;
	  }
	case 61:
	  {
	    X[13]--;  X[20]++; asynRelcount++; totalRelcount++; relFlag = 0; lastRelTime = time; break;
	  }
	case 62:
	  {
	    X[14]--;   X[20]++; asynRelcount++; totalRelcount++; relFlag = 0; lastRelTime = time; break;
	  }
	case 63:
	  {
	    X[15]--;   X[20]++;  asynRelcount++; totalRelcount++; relFlag = 0;  lastRelTime = time; break;
	  }
	case 64:
	  {
	    X[16]--;   X[20]++;  asynRelcount++; totalRelcount++; relFlag = 0; lastRelTime = time; break;
	  }
	case 65:
	  {
	    X[17]--;   X[20]++;  asynRelcount++; totalRelcount++; relFlag = 0; lastRelTime = time; break;
	  }
	case 66:
	  {
	    X[20]--; X[0]++;  break;
	  }
	  //-----------------------------------
	}
      for(size_t i=0; i < X.size();++i){
	if(X[i] < 0){
	  X[i] = 0;
	}
      };
      if (conCaIn < 0){
	conCaIn = 0;
      };
  
      return;
    }

  } // namespace gillespie
} // namespace astron

#endif // CA_SENSOR_GILLESPIE_CLASS_HPP_INCLUDED
