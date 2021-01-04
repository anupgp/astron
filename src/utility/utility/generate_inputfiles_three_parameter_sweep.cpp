// Time-stamp: <2016-09-26 14:12:20 anup>
// Description: This program is for changing the values in the insilico *.isf file for a specific variable or parameter
// This program can either of the following: take one insilico file and generate several file where one variable/parameter is changed in a certain way. Or, take many insilico files and change one parameter in a certain way.

#include <iostream>
#include <fstream>
#include <vector>

#include <sstream>
#include <string>
#include <cstring>

#include "string_functions.hpp"
#include "file_functions.hpp"

int main(int argc, char* argv[])
{
  // First parameter
  std::string p1name = "ip3r_yk_flux_coef";
  unsigned np1 = 10;
  unsigned p1startline = 147;
  unsigned p1stopline = 147;
  double p1startval = 0.6;
  double p1stepval = 0.6;
  // Second parameter
  std::string p2name = "er_leak_flux_coef";
  unsigned np2 = 4;
  unsigned p2startline = 121;
  unsigned p2stopline = 121;
  double p2startval = 0.0004;
  double p2stepval = 100e-9;
  std::vector<double> p2vals = {0.0004,0.004,0.04,0.11};
  // Third parameter
  std::string p3name = "serca_hill_v_max";
  unsigned np3 = 4;
  unsigned p3startline = 96;
  unsigned p3stopline = 96;
  double p3startval = 100e-9;
  double p3stepval = 100e-9;
  std::vector<double> p3vals = {1e-6, 2e-6, 5e-6, 10e-6};
  // General stuff
  char worddelim = ',';
  char pairdelim = ':'; 
  std::string sourcefname = "input/astrocyte/ip3rlr/astrocyte_all.isf";
  std::vector<std::string> destfnames;
  destfnames = generate_filenames(sourcefname,np1*np2*np3,1);
  file_duplicate(sourcefname,destfnames);
  // Sweep the first parameter
  double p1val = p1startval;
  for(auto el:destfnames){
    if (p1val > (p1startval + (p1stepval * (np1-1)) )){
      p1val = p1startval;
      std::cout << std::endl;
    }
    file_change_value(el,p1name,p1val,pairdelim,worddelim,worddelim,p1startline,p1stopline);
    std::cout << p1val << " ";
    p1val+=p1stepval;
  }
  std::cout << std::endl;
  // Sweep the second parameter
  double p2val = p2startval;
  unsigned counter2 = 1;
  unsigned idx2 = 0;
  for(auto el:destfnames){
    if (counter2 > np1){
      counter2 = 1;
      // p2val+=p2stepval;
      idx2 = (idx2 >= (p2vals.size() - 1)) ? 0 : idx2+1;  
      std::cout << std::endl;
    }
    // if (p2val > (p2startval + (p2stepval * (np2-1)) )){
    //   p2val = p2startval;
    // }
    p2val = p2vals[idx2];
    file_change_value(el,p2name,p2val,pairdelim,worddelim,worddelim,p2startline,p2stopline);
    counter2++;
    std::cout << p2val << " ";
  }
  std::cout << std::endl;
  // Sweep for third parameter
  double p3val = p3startval;
  unsigned counter3 = 1;
  unsigned idx3 = 0;
  for(auto el:destfnames){
    if (counter3 > np1*np2){
      counter3 = 1;
      // p3val+=p3stepval;
      idx3 = (idx3 >= (p3vals.size() - 1)) ? 0 : idx3+1;  
      std::cout << std::endl;
    }
    // if (p3val > (p3startval + (p3stepval * (np3-1)) )){
    //   p3val = p3startval;
    // }
    p3val = p3vals[idx3];
    file_change_value(el,p3name,p3val,pairdelim,worddelim,worddelim,p3startline,p3stopline);
    counter3++;
    std::cout << p3val << " ";
  }
  std::cout << std::endl;
}
