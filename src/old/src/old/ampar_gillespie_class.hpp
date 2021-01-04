#ifndef AMPAR_GILLESPIE_CLASS_HPP_INCLUDED
#define AMPAR_GILLESPIE_CLASS_HPP_INCLUDED

#include <iostream>
#include <cmath>
#include <vector>
#include <ctime>

#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/generator_iterator.hpp>
#include <boost/random/linear_congruential.hpp>

#include "stl_vector_operation_functions.hpp"

class ampar_gillespie_class
{
   private:
      unsigned int seed;
      boost::minstd_rand rng;   //Boost random number generator
      boost::uniform_real<double> uni_dist;   //Uniform random number distribution which produces values b/w 0 and 1 (0 inclusive, 1 exlusive).
      boost::variate_generator<boost::minstd_rand&, boost::uniform_real< double> > uni_rand;// variate generator
      //--------------
      double kf1 = 4.59E06;    //M^-1 S^-1
      double kb1 = 4.26E03;    //S^-1
      double kf2 = 28.4E06;    //M^-1 * S^-1
      double kb2 = 3.26E03;    //S^-1
      double kf3 = 1.27E06;    //M^-1 S^-1
      double kb3 = 45.7;       //S^-1
      double a0 = 4.24E03;     //S^-1
      double b0 = 900.0;       //S^-1
      double a1 = 2.89E03;     //S^-1
      double b1 = 39.2;        //S^-1
      double a2 = 172.0;       //S^-1
      double b2 = 0.727;       //S^-1
      double a3 = 17.7;        //S^-1
      double b3 = 4.0;         //S^-1
      double a4 = 16.8;        //S^-1
      double b4 = 190.4;       //S^-1
      double Volume = 1.0;
   public:
      const double avagadro = 6.022e+23;
      const int Nstates = 8;
      const int Nreactions = 16;
      double r1,r2;
      //Construct vectors
      std::vector<int> X;      // A vector to hold the initial number of the receptors in each states [Glu,C0,C1,C2,C3,C4,C5,Open]
      std::vector<double> C;  //A vector to hold the Cmew values
      std::vector<double> H;  //A vector to hold the Hmew values
      //Class constructorsampar_gillespie_class(unsigned int seed_ = std::time(0), std::vector<int> X_):   seed(seed_),
       ampar_gillespie_class(std::vector<int> X_, unsigned int seed_=std::time(0)):   seed(seed_),
                                                                        uni_dist(boost::uniform_real<double>(0,1)),
                                                                        uni_rand(boost::variate_generator<boost::minstd_rand&, boost::uniform_real<double> >(rng, uni_dist)),
                                                                        X(std::move(X_))
      {
         rng.seed(seed);
         C = {kf1*Volume,kb1,kf2*Volume,kb2,a1,b1,kf3*Volume,kb3,a2,b2,a4,b4,a0,b0,b3,a3};
         H = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
      }
      void updateX (const int rx_id);
      void updateH (void);
};

/* Function update H_mew vector with the current number of molecules in each state from the state vector X */
void ampar_gillespie_class::updateH(void)
{
   //Genrate two random numbers from the distribution by means of STL generator interface.
   r1 = uni_rand();
   r2 = uni_rand();

   H[0] = X[0] * X[1];
   H[1] = X[2];
   H[2] = X[2] * X[0];
   H[3] = X[3];
   H[4] = X[2];
   H[5] = X[4];
   H[6] = X[4] * X[0];
   H[7] = X[5];
   H[8] = X[3];
   H[9] = X[5];
   H[10] = X[5];
   H[11] = X[6];
   H[12] = X[3];
   H[13] = X[7];
   H[14] = X[6];
   H[15] = X[7];
}
//Function update the state vector X for a given reaction rx_id
void ampar_gillespie_class::updateX(const int rx_id)
{
   //std::cout << "Reaction " << rx_id << " X in " << X;
   switch(rx_id)
   {
      case 0:
      {
         if((X[0] > 0) && (X[1] > 0)){
            --X[0]; --X[1];
            ++X[2];
         }
         break;
      }
      case 1:
      {
         if(X[2] > 0){
         --X[2];
         ++X[0]; ++X[1];
         }
         break;
      }
      case 2:
      {
         if((X[2] > 0) && (X[0] > 0)){
         --X[2]; --X[0];
         ++X[3];
         }
         break;
      }
      case 3:
      {
         if(X[3] > 0){
         --X[3];
         ++X[2]; ++X[0];
         }
         break;
      }
      case 4:
      {
         if(X[2] > 0){
         --X[2];
         ++X[4];
         }
         break;
      }
      case 5:
      {
         if(X[4] > 0){
         --X[4];
         ++X[2];
         }
         break;
      }
      case 6:
      {
         if((X[4] > 0) && (X[0] > 0)){
         --X[4];
         --X[0];
         ++X[5];
         }
         break;
      }
      case 7:
      {
         if(X[5] > 0){
         --X[5];
         ++X[4];
         ++X[0];
         }
         break;
      }
      case 8:
      {
         if(X[3] > 0){
         --X[3];
         ++X[5];
         }
         break;
      }
      case 9:
      {
         if(X[5] > 0){
         --X[5];
         ++X[3];
         }
         break;
      }
      case 10:
      {
         if(X[5] > 0){
         --X[5];
         ++X[6];
         }
         break;
      }
      case 11:
      {
         if(X[6] > 0){
         --X[6];
         ++X[5];
         }
         break;
      }
      case 12:
      {
         if(X[3] > 0){
         --X[3];
         ++X[7];
         }
         break;
      }
      case 13:
      {
         if(X[7] > 0){
         --X[7];
         ++X[3];
         }
         break;
      }
      case 14:
      {
         if(X[6] > 0){
         --X[6];
         ++X[7];
         }
         break;
      }
      case 15:
      {
         if(X[7] > 0){
         --X[7];
         ++X[6];
         }
         break;
      }
   }
   for(size_t i=0; i<X.size();++i){
      if(X[i] < 0){
         X[i] = 0;
      }
   }
}

#endif // AMPAR_GILLESPIE_CLASS_HPP_INCLUDED
