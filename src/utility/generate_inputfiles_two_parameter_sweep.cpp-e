// Time-stamp: <2017-01-20 16:19:45 anup>
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
  std::string p1name = "ip3r_lr_flux_coef";
  unsigned np1 = 6;
  double p1startval = 1;
  double p1stepval = 1;
  unsigned p1startline = 211;
  unsigned p1stopline = 211;
  // --------------
  std::string p2name = "serca_hill_v_max";
  unsigned np2 = 10;
  double p2startval = 0.5e-6;
  double p2stepval = 0.5e-6;
  unsigned p2startline = 96;
  unsigned p2stopline = 96;
  // --------------
  char worddelim = ',';
  char pairdelim = ':'; 
  std::string sourcefname = "/mnt/temp1/data/astron/raw/astrocyte/parsweep/set2/astrocyte_all.isf";
  std::vector<std::string> destfnames;
  destfnames = generate_filenames(sourcefname,np1*np2,1);
  file_duplicate(sourcefname,destfnames);

  // sweep the first parameter
  double p1val = p1startval;
  for(auto el:destfnames){
    file_change_value(el,p1name,p1val,pairdelim,worddelim,worddelim,p1startline,p1stopline);
    p1val+=p1stepval;
    if (p1val > (p1startval + (p1stepval * (np1-1)) )){
      p1val = p1startval;
    }
  }
  // sweep the second parameter
  double p2val = p2startval;
  unsigned counter = 0;
  for(auto el:destfnames){
    file_change_value(el,p2name,p2val,pairdelim,worddelim,worddelim,p2startline,p2stopline);
    counter++;
    if (counter >= np1){
      counter = 0;
      p2val+=p2stepval;
    }
    if (p2val > (p2startval + (p2stepval * (np2-1)) )){
      p2val = p2startval;
    }
  }
}
