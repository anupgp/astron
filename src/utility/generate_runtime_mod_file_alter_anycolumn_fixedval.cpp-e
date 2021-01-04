// Time-stamp: <2017-07-31 17:58:53 anup>
// This program will accept a csv file with header names and duplicate the file by changing the values in one entire column with another

#include <iostream>
#include <vector>
#include <string>
#include <omp.h>
#include <chrono>

#include "string_functions.hpp"
#include "file_functions.hpp"


int main(int argc, char* argv[]){
  // std::string fname = "/mnt/temp1/data/astron/raw/astrocyte/caresponse/dynparams_atpext_dr2sec.isfdp";
  std::string fname = "/mnt/mount1/data/astron/raw/astrocyte/caresponse/dynparams_drglu30s.isfdp";
  std::string pname = "glu_ext1";
  char sepchar = ',';
  // std::vector<double> newvalues = {
  //   0,10e-9,20e-9,30e-9,40e-9,50e-9,60e-9,70e-9,80e-9,90e-9,
  //   100e-9,200e-9,300e-9,400e-9,500e-9,600e-9,700e-9,800e-9,900e-9,
  //   1e-6,2e-6,3e-6,4e-6,5e-6,6e-6,7e-6,8e-6,9e-6,
  //   10e-6,20e-6,30e-6,40e-6,50e-6,60e-6,70e-6,80e-6,90e-6,
  //   100e-6
  // };
  // std::vector<double> newvalues = {
  //   0,10e-9,20e-9,30e-9,40e-9,50e-9,60e-9,70e-9,80e-9,90e-9,
  //   100e-9,200e-9,300e-9,400e-9,500e-9,600e-9,700e-9,800e-9,900e-9,
  //   1e-6,2e-6,3e-6,4e-6,5e-6,6e-6,7e-6,8e-6,9e-6,
  //   10e-6
  // };
  std::vector<double> newvalues = {
    0,1e-9,10e-9,20e-9,30e-9,40e-9,50e-9,60e-9,70e-9,80e-9,90e-9,
    100e-9,200e-9,300e-9,400e-9,500e-9,600e-9,700e-9,800e-9,900e-9,
    1e-6,2e-6,3e-6,4e-6,5e-6,6e-6,7e-6,8e-6,9e-6,
    10e-6,20e-6,30e-6,40e-6,50e-6,60e-6,70e-6,80e-6,90e-6,
    100e-6,200e-6,300e-6,400e-6,500e-6,600e-6,700e-6,800e-6,900e-6,1000e-6
  };
  std::chrono::high_resolution_clock::time_point t1,t2;
  std::chrono::milliseconds ms;
  
  std::vector<std::string> destfnames;  
  destfnames = generate_filenames(fname,newvalues.size(),1); // generate multiple filenames
  file_duplicate(fname,destfnames); // duplicates one file to multiple files with names in destfnames
  unsigned count = -1;
  
  for(auto el:destfnames){
    count++;
    t1 = std::chrono::high_resolution_clock::now();
    file_change_entire_column_value(el,pname,sepchar,newvalues[count]);
    t2 = std::chrono::high_resolution_clock::now();
    ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1);
    std::cout << ms.count() << " ms\n";
  }
}
