#ifndef GILLESPIE_CLASS_HPP_INCLUDED
#define GILLESPIE_CLASS_HPP_INCLUDED

#include <iostream>
#include <cmath>
#include <vector>
#include <ctime>

#include "boost_random.hpp"
#include "stl_vector_operation_functions.hpp"

// Function to compute Tau from the first random number r1 and aTot (a = H_mew*C_mew)
double getTau(const double r1, const double Atotal);
// Function to find the next reaction using a random number r2 and vector A (the vector A = H*C; contains: 0 to M-1 reactions)
int getReaction(const double r2, const double Atotal, const std::vector<double> A);

//------------------------------------------------------------
// Gillespie simulator status display
template <typename gillespie_class>
void gillespie_display(const gillespie_class &G)
{
};
//-------------------------------------------------------------
// The Gillespie_MCMC simulator
template <class gillespie_class >
void gillespie(gillespie_class &G, double t1, double dt)
{
  double s;
  double r1,r2;
  uni_real_dist_type uni_real_dist(0,1); // created a uniform real distribution from [0,1) 
  uni_var_gen_real_type random_unif_real(gen,uni_real_dist); // binding the random generator with "uni_real_dist" distribution

  double t = 0;
  std::vector<double> A(G.H.size());
  double tau = 0.0;
  double Atotal = 1.0;//store Amew total;
  int reaction = -1;
  G.updateH(); // calculate Hmew based on the current state
  A = vectorProd(G.H,G.C);// calculate Amew = Hmew*Cmew
  //std::cout << "A = " << A << std::endl;
  Atotal = vectorSum(A);// store Amew total
  r1 = random_unif_real();
  tau = getTau(r1,Atotal); //calutate the next time step dttau
  G.first_object_calls();
  
  if( (tau != -1) && (t + tau <= dt) )
    {  
      while(  (Atotal != 0) && ( t + tau <= dt) ){
	t = t+tau;
	G.dt = tau;		// Sets local gillespie time step
	if(G.id == 1){
	  gillespie_class::time+=tau; // Sets global gillespie running time
	}
	r1 = random_unif_real();
	r2 = random_unif_real();
	reaction = getReaction(r2,Atotal,A); // determine the next reaction
	//std::cout << "t1 =  " << t1 << " dt = " << dt << " tau = " << tau << std::endl;
	//std::cout << "reaction = " << reaction << std::endl;
	G.updateX(reaction); // update the state to reflect the occurance of the reaction identified by mewIndex
	//std::cout << "X = " << G.X << std::endl;
	G.updateH(); // calculate Hmew based on the current state
	G.all_object_calls();
	G.update_variables();

	A = vectorProd(G.H,G.C);// calculate Amew = Hmew*Cmew
	Atotal = vectorSum(A);// store Amew total
	tau = getTau(r1,Atotal); //calutate the next time step dttau
      }
    }
  else
    {
      //std::cout << "t1 =  " << t1 << " dt = " << dt << " tau = " << tau << std::endl;
      //std::cout << "X = " << G.X << std::endl;
      //std::cout << "G.H = " << G.H << std::endl;
      //std::cout << "G.C = " << G.C << std::endl;
      //std::cout << "reaction = " << reaction << std::endl;
      G.updateH();
      G.all_object_calls();
      G.update_variables();
    }  
  if(G.id == 1)
    {
      gillespie_class::time = t1+dt; //Sets global gillespie running time
    }
}

//-------------------------------------------------------------

// Gillespie class function definitions

double getTau(const double r1, const double Atotal) // Function to compute Tau from the first random number r1 and aTot (a = H_mew*C_mew)
{
  double ret_value;
  if(Atotal > 1E-308)
    ret_value = (1/Atotal) * log(1/r1);
  else
    ret_value = -1;
  return (ret_value);
}

//------------------------------------------------------------

//Function to find the next reaction using a random number r2 and vector A (the vector A = H*C; contains: 0 to M-1 reactions)
int getReaction(const double r2, const double Atotal, const std::vector<double> A)
{
  std::vector<int> Ai; // Vector to hold the indices of A that has a non-zero entry
  for(size_t i=0; i<A.size();i++)
    {
      if (A[i] > 1E-308)
	{
	  Ai.push_back(i);
	}
    }
  int j=-1;
  if (!Ai.empty())
    {     // evaluate if Ai vector is non-zero
      j = Ai[0];  //
      double cum=0;
      for(size_t i=0; i < Ai.size()-1; i++)
	{
	  cum = cum + A[Ai[i]];
	  if (cum <= (Atotal * r2) )
	    {
	      j = Ai[i+1];
	    }
	}
    }
  return(j);
}

//----------------------------------------------------------------

#endif // GILLESPIE_CLASS_HPP_INCLUDED
