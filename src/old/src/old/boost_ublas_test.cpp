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

namespace bnu=boost::numeric::ublas;
//===============FUNCTIONS==================
template<typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& v)
{
   //out << "[";
   size_t last = v.size() - 1;
   for(size_t i = 0; i < v.size(); ++i) {
      out << v[i];
      if (i != last)
         out << " ";
   }
   //out << "]";
   out << std::endl;
   return out;
}
/* Function update H_mew vector with the current number of molecules in each state from the state vector X */
void updateHmew(std::vector<double>& Hmew, const std::vector<int> X)
{
   Hmew[0] = X[0] * X[1];
   Hmew[1] = X[2];
   Hmew[2] = X[2] * X[0];
   Hmew[3] = X[3];
   Hmew[4] = X[2];
   Hmew[5] = X[4];
   Hmew[6] = X[4] * X[0];
   Hmew[7] = X[5];
   Hmew[8] = X[3];
   Hmew[9] = X[5];
   Hmew[10] = X[5];
   Hmew[11] = X[6];
   Hmew[12] = X[3];
   Hmew[13] = X[7];
   Hmew[14] = X[6];
   Hmew[15] = X[7];
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
template <typename vec_type, typename mat_type>
void MatrixCopy(const std::vector<vec_type> v, bnu::matrix<mat_type> &m, const bool byrow)
/*Copy a vector v to the matrix m in either row or columnwise*/
{
   if(v.size() != m.size1()*m.size2()){
      std::cout << "rows of the matrix = " << m.size1() << std::endl << "columns of matrix = " << m.size2() << std::endl;
      std::cout << "size of vector = " << v.size() << std::endl;
      std::cout << "size of vector not equal to sum of row and columns of the given matrix" << std::endl;
      return;
   }
      if(byrow){
         for(size_t row=0; row<m.size1(); row++){
            for(size_t col=0; col<m.size2(); col++){
               m(row,col) = v[(row*(m.size2()))+(col)];
            }
         }
      }
      else{
         for(size_t col=0; col<m.size2(); col++){
            for(size_t row=0; row<m.size1(); row++){
               m(row,col) = v[(col*(m.size1()))+(row)];
            }
         }
      }

}
//----------
template< typename T >
T vectorSum(const std::vector<T> v)
{
   T sum=0;
   for(size_t i=0; i < v.size();i++){
      sum = sum + v[i];
   }
   return sum;
}
//----------
std::vector<double> vectorProd(const std::vector<double> a, const std::vector<double> b)
{
   std::vector<double> c( a.size() );
   if(a.size() == b.size()){
      for(size_t i=0; i < a.size();i++){
         c[i] = (a[i] * b[i]);
      }
   }
   return(c);
}
//----------
template< typename T >
std::vector<T> vectorCumSum(const std::vector<T> v)
{
   std::vector<T> cumsum;
   T sum = 0;
   for(size_t i=0; i < v.size();i++){
      sum = sum + v[i];
      cumsum.push_back(sum);
   }
   return(cumsum);
}
std::vector<double> colSum(const bnu::matrix<double> &m)
{
   std::vector<double> colsum;
   for(size_t col=0; col < m.size2(); col++){
      double sum=0.0;
      for(size_t row=0; row < m.size1(); row++){
         sum = sum + m(row,col);
      }
      colsum.push_back(sum);
   }
   return colsum;
}
//------------------
std::vector<double> rowSum(const bnu::matrix<double> &m)
{
   std::vector<double> rowsum;
   for(size_t row=0; row < m.size1(); row++){
      double sum=0.0;
      for(size_t col=0; col < m.size2(); col++){
         sum = sum + m(row,col);
      }
      rowsum.push_back(sum);
   }
   return rowsum;
}
//Function to compute Tau from the first random number r1 and aTot (a = ∑H_mew*C_mew)
double getTau(double r1, double aTot)
{
   if (aTot >1E-308){
      return( (1/aTot) * log(1/r1) );
   }
   else
      return(-1);
}
//Function to compute mew_index from the second random number r1 and a_mew (the vector h_new*c_new; new: 0 to M reactions)
int getMewIndex(double r2, double aTot, std::vector<double> amew0)
{
   std::vector<int> amew;
   for(size_t i=0; i<amew0.size();i++){
      if(amew0[i] > 1E-308){
         amew.push_back(i);
      }
   }
   int j=-1;
   if (!amew.empty()){
      j = amew[0];
      double cum=0;
      for(size_t i=0; i<amew.size()-1;i++){
         cum = cum + amew0[amew[i]];
         if (cum <= (aTot * r2) ){
            j = amew[i+1];
         }
      }
   }
   //std::cout << amew << std::endl;
   return(j);
}
//------------------------
//This is typedef for a random number generator
typedef boost::minstd_rand base_generator_type;
//-------------------------
//=================MAIN====================
int main(int argc, char** argv)
{
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
   //Define a random number generator and initialize it with a reproducible seed
   base_generator_type generator(45);
   //Define a uniform random number distribution which produces "double"
   //values b/w 0 and 1 (0 inclusive, 1 exlusive).
   boost::uniform_real<>uni_dist(0,1);
   boost::variate_generator<base_generator_type&, boost::uniform_real<> > uni(generator, uni_dist);
   std::vector<int> X(8);// A vector to hold the initial number of the receptors in each states [Glu,C0,C1,C2,C3,C4,C5,Open]
   X = {500000,100,0,0,0,0,0,0};
   std::vector<double> Cmew(16); //A vector to hold the Cmew values
   double V = 1.0;// Volume of the reaction space
   Cmew = {kf1*V,kb1,kf2*V,kb2,a1,b1,kf3*V,kb3,a2,b2,a4,b4,a0,b0,b3,a3};
   std::vector<double> Hmew(16); //A vector to hold the Hmew values
   std::vector<double> Amew(16); //A vector to hold the Amew values
   std::transform(Cmew.begin(),Cmew.end(),Cmew.begin(),std::bind1st(std::multiplies<double>(),(1) ));
   Hmew = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
   double tmax = 10.0;//10 secs
   double dt = 50E-06;// 1 msec
   double t2 = dt;
   double t = 0;
   double r1 = 0.0;
   double r2 = 0.0;
   int mewIndex = 0;
   double tau = 0.0;
   double AmewTot = 0.0;
   int RxIndex = 0;
   std::cout << t << " " << X;
   while(t <= 1){
      updateHmew(Hmew,X); // calculate Hmew based on the current state
      Amew = vectorProd(Hmew,Cmew);// calculate Amew = Hmew*Cmew
      AmewTot = vectorSum(Amew);// store Amew total
      //Genrate two random numbers from the distribution by means of STL generator interface.
      r1 = uni();
      r2 = uni();
      tau = getTau(r1,AmewTot); //calutate the next time step dttau
      if ( (mewIndex != -1) ){
         mewIndex = getMewIndex(r2,AmewTot,Amew); // determine the next reaction
         updateX(X,mewIndex); // update the state to reflect the occurance of the reaction identified by mewIndex
      }
      t = t+tau;
      if (t >= t2){
         std::cout << t << " " << X;
         t2+=dt;
      }
      RxIndex+=1;
      //std::cout << "Step = " << RxIndex << "   Time = " << t <<  "  Rx time step = " << tau << "   Rx index  = " << mewIndex << std::endl;
      //std::cout << "Cmew = " << Cmew;
      //std::cout << "Hmew = " << Hmew;
      //std::cout << "Amew Tot = " << AmewTot << "   r2 = " << r2  << "   Amew * r2 = " << AmewTot*r2  << " " << "   Amew = "  << Amew;
      //std::cout << vectorCumSum(Amew);
      //std::cin.get();
   }
}
