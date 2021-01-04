#include <iostream>

#include <cmath>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/operation.hpp>

#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/generator_iterator.hpp>
#include <boost/random/linear_congruential.hpp>

#include "stl_vector_operation_functions.hpp"
namespace bnu=boost::numeric::ublas;
//------------------------
//This is typedef for a random number generator
typedef boost::minstd_rand base_generator_type;

//===============FUNCTIONS==================
/* Function update H_mew vector with the current number of molecules in each state from the state vector X */
void updateH(std::vector<double>& H, const std::vector<int> X)
{
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
void updateX(std::vector<int>& X, const int rx_id)
{
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
//Function to compute Tau from the first random number r1 and aTot (a = ∑H_mew*C_mew)
double getTau(const double r1, const double Atotal)
{
   if (Atotal >1E-308){
      return( (1/Atotal) * log(1/r1) );
   }
   else{
      return(-1);
   }
}
//Function to find the next reaction using a random number r2 and vector A (the vector A = H*C; contains: 0 to M-1 reactions)
int getReaction(const double r2, const double Atotal, const std::vector<double> A)
{
   std::vector<int> Ai; // Vector to hold the indices of A that has a non-zero entry
   for(size_t i=0; i<A.size();i++){
      if(A[i] > 1E-308){
         Ai.push_back(i);
      }
   }
   int j=-1;
   if (!Ai.empty()){     // evaluate if Ai vector is non-zero
      j = Ai[0];  //
      double cum=0;
      for(size_t i=0; i < Ai.size()-1; i++){
         cum = cum + A[Ai[i]];
         if (cum <= (Atotal * r2) ){
            j = Ai[i+1];
         }
      }
   }
   return(j);
}
//-------------------------
//=================MAIN====================
int main(int argc, char** argv)
{
   //Define a random number generator and initialize it with a reproducible seed
   base_generator_type generator(45);
   //Define a uniform random number distribution which produces "double"
   //values b/w 0 and 1 (0 inclusive, 1 exlusive).
   boost::uniform_real<double>uni_dist(0,1);
   boost::variate_generator<base_generator_type&, boost::uniform_real<double> > uni(generator, uni_dist);

   const double avagadro = 6.022e+23;
   //--------------
   double kf1 = 4.59E06;//M^-1 S^-1
   double kb1 = 4.26E03;//S^-1
   double kf2 = 28.4E06;//M^-1 * S^-1
   double kb2 = 3.26E03;//S^-1
   double kf3 = 1.27E06;//M^-1 S^-1
   double kb3 = 45.7;//S^-1
   double a0 = 4.24E03;//S^-1
   double b0 = 900.0;//S^-1
   double a1 = 2.89E03;//S^-1
   double b1 = 39.2;//S^-1
   double a2 = 172.0;//S^-1
   double b2 = 0.727;//S^-1
   double a3 = 17.7;//S^-1
   double b3 = 4.0;//S^-1
   double a4 = 16.8;//S^-1
   double b4 = 190.4;//S^-1
   //-----------------------------
   std::vector<int> X(8);// A vector to hold the initial number of the receptors in each states [Glu,C0,C1,C2,C3,C4,C5,Open]
   std::vector<double> C(16); //A vector to hold the Cmew values
   std::vector<double> H(16); //A vector to hold the Hmew values
   std::vector<double> A(16); //A vector to hold the Amew values
   X = {1000,100,0,0,0,0,0,0};
   double V = 1.0;// Volume of the reaction space
   C = {kf1*V,kb1,kf2*V,kb2,a1,b1,kf3*V,kb3,a2,b2,a4,b4,a0,b0,b3,a3};
   H = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
   double tmax = 1.0;//10 secs
   double dt = 50E-06;// 1 msec
   double t2 = dt;
   double t = 0;
   double r1 = 0.0;
   double r2 = 0.0;
   int reaction = 0;
   double tau = 0.0;
   double Atotal = 1.0;// store Amew total;
   int reactionCount = 0;
   std::cout << t << " " << X;
   updateH(H,X); // calculate Hmew based on the current state
   A = vectorProd(H,C);// calculate Amew = Hmew*Cmew
   Atotal = vectorSum(A);// store Amew total
   while( (t <= tmax) && (Atotal != 0) ){
      //Genrate two random numbers from the distribution by means of STL generator interface.
      r1 = uni();
      r2 = uni();
      tau = getTau(r1,Atotal); //calutate the next time step dttau
      reaction = getReaction(r2,Atotal,A); // determine the next reaction
      if (tau > tmax){
         break;
      }
      else{
         updateH(H,X); // calculate Hmew based on the current state
         updateX(X,reaction); // update the state to reflect the occurance of the reaction identified by mewIndex
         A = vectorProd(H,C);// calculate Amew = Hmew*Cmew
         Atotal = vectorSum(A);// store Amew total
         //std::cout << "Current State " << X;
         //std::cout << "H " << H;
         //std::cout << "C " << C;
         //std::cout << "A " << A;
         //std::cout << "Atotal " << Atotal << std::endl;
         //std::cout << "Atotal * r2 " << Atotal*r2 << std::endl;
         //std::cout << "cumSum (A * r2) " << vectorCumSum(A);
         //std::cout << "Reaction " << reaction << std::endl;
         //std::cout << "Tau " << tau << std::endl;
         //std::cout << "Updated State " << X;
      }
      t = t+tau;
      if (t >= t2){
         std::cout << t << " " << X;
         t2+=dt;
      }
      reactionCount+=1;
      //std::cin.get();
   }
}
