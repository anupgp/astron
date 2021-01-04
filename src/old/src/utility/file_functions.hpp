// Time-stamp: <2017-04-06 16:01:42 anup>
// Description: cpp functions for string manipulation 

#ifndef FILE_FUNCTIONS_HPP_INCLUDED
#define FILE_FUNCTIONS_HPP_INCLUDED

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <stdexcept> 
#include <limits>
#include <algorithm>

#include <sstream>
#include <string>
#include <cstring>

#include "string_functions.hpp"
// #include "matrix_functions.hpp"

// auto file_readcolumn(const std::string infile_fullname, int ncolumns, int nrows, char colsep, char rowsep) -> astron::vfunc::matrix<std::vector<double>>
// {
//   astron::vfunc::matrix<std::vector<double>> mymat(9);
//   // Open source file
//   std::ifstream fsource;
//   fsource.open(infile_fullname,std::ios::in);
//   if (!fsource.good()){
//     std::cout << "File could not be opened!" << std::endl;
//     return(mymat);
//   }
//   // get length of file:
//   fsource.seekg (0, fsource.end);
//   int length = fsource.tellg();
//   std::cout << "File size = " << length << std::endl;
//   fsource.seekg (0, std::ios_base::beg);
//   std::string lineseg;
//   std::vector<std::string> pnames;
//   std::vector<double> values;


//   getline(fsource,lineseg);
//   pnames = get_paramnames(lineseg,',');
//   int i = 0;

//   while(!fsource.eof()){
//     getline(fsource,lineseg);
//     values = get_paramvalues(lineseg,',');
//     if(!values.empty()){
//       if (i >= 5999999-10){
//     	for(auto el:values){
//     	  std::cout << std::scientific;
//     	  std::cout  << el << " ";
//     	}
//     	std::cout << std::endl;
//       }
//     mymat.push_row(values);
//       i = i + 1;
//     }  
// }
//   fsource.close();
//   return(mymat);
// } 

// auto file_readcolumn(const std::string infile_fullname, int ncolumns, int nrows, char colsep, char rowsep) -> std::vector<std::vector<double>>
// {
//   std::vector<std::vector<double>> matrix;
//   // Open source file
//   std::ifstream fsource;
//   fsource.open(infile_fullname,std::ios::in);
//   if (!fsource.good()){
//     std::cout << "File could not be opened!" << std::endl;
//     return(matrix);
//   }
//   // get length of file:
//   fsource.seekg (0, fsource.end);
//   int length = fsource.tellg();
//   std::cout << "File size = " << length << std::endl;
//   fsource.seekg (0, std::ios_base::beg);
//   std::string lineseg;
//   std::vector<std::string> pnames;
//   std::vector<double> values;

//   getline(fsource,lineseg);
//   pnames = get_paramnames(lineseg,',');
//   int i = 0;
//   while(!fsource.eof()){
//     getline(fsource,lineseg);
//     values = get_paramvalues(lineseg,',');
//     matrix.push_back(values);
//     i++;
//   }    
//   fsource.close();
//   return(matrix);
// } 


void file_duplicate(const std::string infile_fullname, const std::vector<std::string> &destfnames)
// Function to make n copies of a given file path
{
  // // Get file path
  // std::string filepath = "";
  // filepath = get_string_pre(infile_fullname,'/');
  // // Get file basename
  // std::string filename = ""; 
  // filename = get_string_post(infile_fullname,'/');
  // std::string filenamebare =  get_string_pre(filename,'.');
  // // Get file extension name
  // std::string extname = "";
  // extname = get_string_post(infile_fullname,'.');
  // std::cout << infile_fullname << " " << filepath << " " << filenamebare << " " << extname << std::endl;
  // // Generate a vector of new filename with absolute paths
  // std::vector<std::string> outfile_fullnames;
  // Open source file
  std::ifstream fsource;
  fsource.open(infile_fullname,std::ios::in);
  // Copy source file content to file buffer
  std::string s((std::istreambuf_iterator<char>(fsource)), std::istreambuf_iterator<char>());
  fsource.close();
  std::ofstream fdest;
  for(unsigned i = 1; i <= destfnames.size(); i++){
    // outfile_fullnames.push_back(filepath + "/" + filenamebare + std::to_string(i) + "." + extname);
    // Open target file
    std::cout << destfnames[i-1] << std::endl;
    fdest.open(destfnames[i-1],std::ios::out);
    if(fdest.is_open()){
      fdest << s;
      fdest.close();      
    }
    else
      std::cout << "File could not be opened!" << std::endl;      
  }
  // delete fbuffer;
  // return();
}

// void file_change_value(std::string fname, std::string pname, double value, char pairdelim, char segdelim, unsigned firstline = 1, unsigned lastline = std::numeric_limits<int>::max())
// // Change the value of a parameter in the given file
// {
//   // Open source file for reading
//   std::ifstream fsource;
//   fsource.open(fname,std::ios::in);
//   // Copy whole source file content to file buffer
//   std::string oldfile((std::istreambuf_iterator<char>(fsource)), std::istreambuf_iterator<char>()),newfile,aline;
//   // Close the file
//   fsource.close();    
//   // -------- Copy only specific lines to the string if either firstline or lastline is not Default
//   std::stringstream ssold,ssnew;
//   // Copy string to string stream
//   ssold << oldfile;
//   unsigned counter=0;
//   while(getline(ssold,aline,'\n')){
//     counter++;
//     if(counter >= firstline && counter <= lastline && !aline.empty()){
//       // Get string segment containing the parameter
//       std::string oldseg = get_string_segment(aline, pname, segdelim);
//       if(oldseg.length()>1){
// 	std::cout << "oldline: " << aline;
// 	// std::cin.get();
// 	// Change value in the buffer if string found
// 	std::string newseg = change_param_value(oldseg, pname, value, pairdelim, segdelim);
// 	// Replace the changed string
// 	aline = replace_string_segment(aline, segdelim, oldseg, newseg);
// 	std::cout << "newline: " << aline;
//       }
//     }
//     ssnew << aline << '\n';
//   }
//   // copy sspart to spart
//   newfile = ssnew.str();
//   // std::cout << "extracted portion of file:" << newfile;
//   // Open the file for writing
//   std::ofstream fdest;
//   fdest.open(fname,std::ios::out); 
//   fdest << newfile;
//   // Close the file
//   fdest.close();
// }

void file_change_value(std::string fname, std::string pname, double value, char pairdelim, char segdelim1, char segdelim2, unsigned firstline = 1, unsigned lastline = std::numeric_limits<int>::max())
// Change the value of a parameter in the given file
{
  // Open source file for reading
  std::ifstream fsource;
  fsource.open(fname,std::ios::in);
  // Copy whole source file content to file buffer
  std::string oldfile((std::istreambuf_iterator<char>(fsource)), std::istreambuf_iterator<char>()),newfile,aline;
  // Close the file
  fsource.close();    
  // -------- Copy only specific lines to the string if either firstline or lastline is not Default
  std::stringstream ssold,ssnew;
  // Copy string to string stream
  ssold << oldfile;
  unsigned counter=0;
  while(getline(ssold,aline,'\n')){
    counter++;
    if(counter >= firstline && counter <= lastline && !aline.empty()){
      // Get position of segment containing the parameter
      unsigned segstartpos=0,segfinishpos=0;
      // Check if the line contains the parameter
      get_segment_pos(aline, pname, segdelim1,segdelim2,segstartpos,segfinishpos);
      if(segfinishpos-segstartpos > 1){
	std::cout << "line: "<<counter << " " << aline;
	// Change value in the buffer if string found
	change_seg_param_value(aline, pname, value, pairdelim,segdelim1,segdelim2);
	// // Replace the changed string
	// aline = replace_string_segment(aline, segdelim1,segdelim2, oldseg, newseg);
	// std::cout << "newline: " << aline;
      }
    }
    ssnew << aline << '\n';
  }
  // copy sspart to spart
  newfile = ssnew.str();
  // std::cout << "extracted portion of file:" << newfile;
  // Open the file for writing
  std::ofstream fdest;
  fdest.open(fname,std::ios::out); 
  fdest << newfile;
  // Close the file
  fdest.close();
}

// -------------------------------------------------------------------------------------------
void file_change_entire_column_value(std::string fname, std::string pname, char sepchar, double newval)
// Change all the values in an entire column with a new value
{
  // Open source file for reading
  std::ifstream fsource;
  fsource.open(fname,std::ios::in);
  // Copy whole source file content to file buffer
  std::string oldfile((std::istreambuf_iterator<char>(fsource)), std::istreambuf_iterator<char>()),newfile,aline;
  // Close the file
  fsource.close();
  std::stringstream sslold,sslnew,ssfold,ssfnew;
  // Copy string to string stream
  ssfold << oldfile;
  // vector for keeping the column names
  std::vector<std::string> colnames, srow;
  std::vector<double> drow;
  unsigned colindex;
  unsigned counter=0;
  while(getline(ssfold,aline,'\n')){
    counter++;
    if (counter == 1){
      std::cout << counter;
      // get headers from the first line/row
      colnames = get_paramnames(aline,sepchar);      
      // exit if column names is empty
      if (colnames.size() == 0){
	std::cout << "No header row with column names!" << std::endl;
	return;
      }
      // Find if the given parameter name is present in colnames
      std::vector<std::string>::iterator it = find(colnames.begin(),colnames.end(),pname);
      // exit if column name could not be found
      if(*it != pname){
	std::cout << "Column name " << pname << " could not be found!" << std::endl;
	return;
      }
      colindex = colnames.end()-it;
      std::cout << *it << colindex << "\n";
      // write header/column names into the output stream stream
      for (auto el:colnames){
	ssfnew << el << ',';
      }
      ssfnew << "\n";
      continue;
    }
    // Read the row into a vector of double
    drow = get_paramvalues(aline,sepchar);
    // change the value in colindex with the new value
    drow[colindex] = newval;
    // write the vector into a stringsteam
    sslnew.clear();
    sslnew.str(std::string());
    for(auto el:drow){
      sslnew << std::setprecision(10) << el << sepchar;
      // std::cout << sslnew.str() << std::endl;
    }
    // write the line stringstream to file stringstream
    ssfnew << sslnew.str() << "\n";
  }
    // copy sspart to spart
    newfile = ssfnew.str();
  // std::cout << "extracted portion of file:" << newfile;
  // Open the file for writing
  std::ofstream fdest;
  fdest.open(fname,std::ios::out); 
  fdest << newfile;
  fdest.flush();
  // Close the file
  fdest.close();
}
#endif	// FILE_FUNCTIONS_HPP_INCLUDED
