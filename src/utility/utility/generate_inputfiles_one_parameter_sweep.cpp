// Time-stamp: <2016-11-03 11:19:49 anup>
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
  std::string pname = "ip3_cyt_baseline";
  double startval = 0.0;
  double stepval = 0.01e-06;
  char lworddelim = ',';
  char rworddelim = ';';
  char pairdelim = ':';
  unsigned startline = 249;
  unsigned stopline = 249;
  double val = startval;
  std::string sourcefname = "input/astrocyte/atprelease/astrocyte_all.isf";
  std::vector<std::string> destfnames;
  destfnames = generate_filenames(sourcefname,1000,1);
  file_duplicate(sourcefname,destfnames);
  for(auto el:destfnames){
    // file_change_value(el,pname,val,pairdelim,lworddelim,rworddelim,startline,stopline);
    // val+=stepval;
  }
}
