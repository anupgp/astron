// Time-stamp: <2016-04-21 17:21:46 anup>
// Description: This program will read a text file (csv) and reads specific columns to compute the min and max values between a certain time

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>

#include <sstream>
#include <string>
#include <cstring>

#include "string_functions.hpp"
#include "file_functions.hpp"
#include "matrix_functions.hpp"

void getcolumn(const std::string infile_fullname, std::string colname, char colsep, char rowsep)
{
  std::vector<double> data;
  std::vector<std::string> header;
  // Open source file
  std::ifstream fsource;
  fsource.open(infile_fullname,std::ios::in);
  if (!fsource.good()){
    std::cout << "File could not be opened!" << std::endl;
  }
  bool headerfound=false;
  int rowcount=0;
  double value;
  unsigned pos;
  std::vector<double> onerow;
  while(!fsource.eof()){
    std::string oneline;
    // get header line
    if(!getline(fsource,oneline,'\n')){
      break;
    }
    rowcount++;
    std::istringstream ss(oneline);

    while (ss){
      std::string cell;
      if (!getline(ss,cell,colsep)){
	break;
      }
      // get colnames from the header line
      if (headerfound == false && rowcount == 1)
	header.push_back(cell);
      if (rowcount > 1){
	try{
	  value = std::stod(cell.c_str());
	}
	catch (const std::invalid_argument&){
	std::cerr << "Invalid string to double conversion error!\n";
	throw;
	}
	catch (const std::out_of_range&){
	  std::cerr << "Out of range string to double conversion error!\n";
	  throw;
	}
	onerow.push_back(value);
      }
    }
    if(header[0].compare("time") != 0){
      std::cerr << "Wrong header found!" << std::endl;
      return;
      headerfound=true;
    }
    // Check if the colnames contain colname
    std::vector<std::string>::iterator it = std::find_if(header.begin(),header.end(),[colname](const std::string s){return(s.compare(colname)==0);});
    if (it != header.end()){
      pos = it - header.begin();
    }
    else{
      std::cerr << "Column name not found in the header!\n"; 
      return;
    }
    if (rowcount > 1){
      data.push_back(onerow[pos]);
    }
  }
  fsource.close();
  std::cout << "File finished at row " << rowcount << std::endl;
  for (auto el:header)
    std::cout << el << " ";
  std::cout << std::endl;
  return;
}; 

int main(int argc, char* argv[])
{
  astron::matrix::matrix<std::vector<double>> mat(9);
  std::vector<double> v = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
  mat.push_row(v);
  // mat.display();
  std::string sourcefname = "/mnt/storage/goofy/projects/data/astron/raw/test2.csv";
  // getcolumn(sourcefname,"n0ca_cyt",',','\n');
  // mat = file_readcolumn(sourcefname,2,100,',','\n');
  // auto result = std::minmax_element(mat.d[8].begin(),mat.d[8].end());
  // std::cout << *result.first << " " << *result.second << std::endl;
  return(0);
  
  // astron::vfunc::vector_swap(mat);
}
