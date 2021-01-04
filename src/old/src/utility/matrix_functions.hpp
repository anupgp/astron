// Time-stamp: <2016-04-21 17:33:32 anup>

#ifndef MATRIX_FUNCTIONS_HPP_INCLUDED
#define MATRIX_FUNCTIONS_HPP_INCLUDED

#include<memory>
#include<vector>

namespace astron {
  namespace matrix {

    template<class T>
    class matrix {
    private:
    public:
      int ncolumns;
      int nrows;
      std::vector<*T> d;
      explicit matrix (int _ncolumns): ncolumns(_ncolumns), nrows(0) {
	d = new std::vector<T>(ncolumns,T();
      };
      void push_row(const T &arow);
      void display(void);
    };

    template<class T>
    void matrix<T>::push_row(const T &arow)
    {
      if(arow.size() < ncolumns){
	std::cerr << "Length of the rows less than columns\n";
	return;
      }
      for(unsigned i=0; i<=ncolumns; i++){
	d[i]->push_back(arow[i]);
	std::cout << d[i]->at(i) << " ";
	i++;
      }
      nrows++;
      // std::cout << "d[0].size() = " << d[0].size() << " d[ncolumns-1].size() = "<< d[ncolumns-1].size() << std::endl;
    };
    
    template<class T>
    void matrix<T>::display(void)
    {
      for(unsigned i=0; i< 1; i++){
	for(typename std::vector<T*>::iterator it=d.begin(); it<d.end(); ++it){
	  std::cout << (*it)->at(i) << " ";
	std::cout << std::endl;
	}
      }
    }

  } // namespace vfunc
}   // namespace astro
#endif
