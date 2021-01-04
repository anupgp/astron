// Time-stamp: <2016-04-28 16:32:50 anup>
// This program will remove all whitespaces present at the begining and end of the given file

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <locale>
#include <cctype>

int filetrim(const char in_file[], const char out_file[])
{
  std::cout << "\n----------------------------------------------------\n";
  std::cout << "**Running filetrim: trims whitespace from the file: " << in_file << std::endl;
  // std::cout << "\n----------------------------------------------------\n";
  std::string infile(in_file);
  std::string outfile(out_file);
  // Open file for reading
  std::ifstream rfile;
  rfile.open(infile);
  if (!rfile.good()){
    std::cout << "File could not be opened!" << std::endl;
    return(1);
  }
  std::vector<char> filebuf;
  while(!rfile.eof()){
    char c;
    rfile.get(c);
    filebuf.push_back(c);
  }
  filebuf.pop_back();
  // Close file after reading
  rfile.close();
  std::locale loc;
  // ------------------------------------------------------------------
  // Find the first non-whitespace character from the start of the file
  std::vector<char>::iterator it1 = 
    std::find_if(filebuf.begin(),filebuf.end(),[](char c){return(!isspace(c));});
  // std::cout << filebuf.size() << std::endl;
  if(it1 != filebuf.end() || it1 != filebuf.begin()){
    // std::cout << "it1 points to: "<< *it1 << std::endl; 
    // std::cout << "it1+1 points to: "<< *(it1+1) << std::endl; 
    filebuf.erase(filebuf.begin(),it1);
  }
  // std::cout << filebuf.size() << std::endl;
  // -----------------------------------------------------------------
  // Find the first non-whitespace character from the end of the file
  std::vector<char>::reverse_iterator it2 = 
    std::find_if(filebuf.rbegin(),filebuf.rend(),[](char c){return(!isspace(c));});
  if(it2 != filebuf.rend() || it2 != filebuf.rbegin()){
    // Trim whitespaces from the end till the first non-whitespace character
    // std::cout << "it2 points to: "<< *it2 << std::endl; 
    // std::cout << "it2+1 points to: "<< *(it2+1) << std::endl; 
    // std::cout << "it2+2 points to: "<< *(it2+2) << std::endl; 
    unsigned dis2 = abs(std::distance(filebuf.rend(),it2));
    filebuf.resize(dis2);
  }
  // -----------------------------------------------------------------
  // write to file if output filename is given
  if(!outfile.empty()){
    // Open file for writing
    std::ofstream wfile;
    wfile.open(outfile);
    if (!wfile.good()){
      std::cout << "File could not be opened!" << std::endl;
      return(1);
    }
    for(char el : filebuf){
      wfile.put(el);
    }
    // Close file after writing
    wfile.close();
    return(0);
  }
  // If no output file is given write to std::out
  else{
    for(char el : filebuf){
      std::cout << el;
    }
  }
  return(0);
}

int main(int argc, char* argv[])
{
  if(argc < 2){
    std::cerr << "Error! input filename required!" << std::endl;
    return(0);
  }
  if(argc > 1 && argc < 3){
    filetrim(argv[1],"");
  }
  if(argc > 2){
    filetrim(argv[1],argv[2]);
  }
  return(0);
}
