// Time-stamp: <2016-05-06 15:38:48 anup>
// This program will generate a new file that contains only every 'n'th line of the given file
 
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <locale>
#include <cctype>

int lineskip(const char in_file[], const unsigned nline, const char out_file[])
{
  std::cout << "----------------------------------------------------\n";
  std::cout << "**Running lineskip: extracts every "<< nline << "th line from file: " << in_file << std::endl;
  std::cout << "----------------------------------------------------\n";
  std::string infile(in_file);
  std::string outfile(out_file);
  // Open file for reading
  std::ifstream rfile;
  rfile.open(infile);
  if (!rfile.good()){
    std::cout << "File could not be opened!" << std::endl;
    return(1);
  }
  std::vector<std::string> filebuf;
  std::string aline;
  // The first two lines are always read, assuming the first is the header line
  unsigned surereadlines=2;
  bool readline = true;
  unsigned nextline2read = nline;
  unsigned counter = 0;
  while(getline(rfile,aline,'\n')){
    counter++;
    if(counter<=surereadlines){
      readline=true;
    }
    if(counter==nextline2read){
      readline=true;
    }
    if(readline){
      filebuf.push_back(aline);
      // std::cout << "read line " << counter << std::endl;
      readline=false;
      nextline2read=counter+nline;
    }
  }
  // always write the last line
  if(nextline2read-nline != counter){
      filebuf.push_back(aline);
  }
  // For some reasons I need to spiff out the last read to avoid some characters repeating.
  // filebuf.pop_back();
  // Close file after reading
  rfile.close();
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
    for(std::string el : filebuf){
      wfile << el << std::endl;
    }
    // Close file after writing
    wfile.close();
    return(0);
  }
  // If no output file is given write to std::out
  else{
    for(auto el:filebuf){
      std::cout << el << std::endl;
    }
  }
  return(0);
}

int main(int argc, char* argv[])
{
  if(argc < 2){
    std::cerr << "Error! input filename required!" << std::endl;
    std::cerr << "Usage: lineskip input_file lines_to_skip_after_line_read output_file\n";
    return(0);
  }
  if(argc == 2){
    std::cout << "Running lineskip with only the input file. No lines skipped\n";
    lineskip(argv[1],1,"");
  }
  if(argc ==3){
    std::cout << "Running lineskip with only the input file and lines to skip\n";
    // Check if the arg 3 is numeric
    if(std::stoi(argv[2])<0){
	std::cerr << "Error! digit check failed. Please enter a valid digit!\n";
	return(0);
      }
    lineskip(argv[1],std::stoi(argv[2]),"");
  }else{
    std::cout << "Running lineskip with all arguments\n";
    // Check if the arg 3 is numeric
    if(std::stoi(argv[2])<0){
	std::cerr << "Error! digit check failed. Please enter a valid digit!\n";
	return(0);
      }
    lineskip(argv[1],std::stoi(argv[2]),argv[3]);
  }
  return(0);
}
