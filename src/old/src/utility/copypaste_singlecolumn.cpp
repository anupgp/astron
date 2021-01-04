// Time-stamp: <2017-07-06 09:07:41 anup>
// Copies a specific single column from one csv file and paste it into another csv file

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <limits>
#include <sstream>
#include <string>
#include <unordered_map>
#include <algorithm>

typedef std::vector<double> column_type;
typedef std::vector<column_type> matrix_type;
typedef std::unordered_map<std::string, std::string> umapstr2str_type;

// -----------------------------------------------------------
void file2matrix_rowwise(std::string fname,int colid, bool header, std::string &colname, matrix_type &rwisemat){
  std::ifstream ifh;
  // Open the file
  ifh.open(fname,std::ios::in);
  // Check the file exists
  if(ifh.is_open() == false){
    std::cerr << "The file does not exist!" << "\n";
    return;
  }
  // declare matrix_type
  matrix_type _rwisemat;
  // Read file line by line
  std::string aline;
  while(std::getline(ifh,aline,'\n')){
    
  }  
}
// ------------------------------------------------------------
void file2matrix_colwise(std::string fname,int colid, bool header, std::string &colname, column_type &outcol){
  std::ifstream ifh;
  // Open the file
  ifh.open(fname,std::ios::in);
  // Check the file exists
  if(ifh.is_open() == false){
    std::cerr << "The file does not exist!" << "\n";
    return;
  }
  // Read file line by line
  std::string aline;
  while(std::getline(ifh,aline,'\n')){
    std::cout<<aline << "\n";
  }  
}
// ----------------------------------------------------------
void pastecolumn(std::string fname, std::string colname, column_type &incol){


}
// ---------------------------------------------------------
int main(int argc, char* argv[])
{
  column_type outcol;
  int colid;
  std::string colname;
  std::string ifname;
  ifname = "/mnt/mount1/data/astron/raw/astrocyte/caresponse/dynparams_test.isfdp";
  copycolumn(ifname,1,true,colname,outcol);
}
