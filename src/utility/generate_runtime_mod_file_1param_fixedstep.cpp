// Time-stamp: <2020-08-26 14:52:51 macbookair>
// Generates a CVS file with a header with column names and rows with time and value steps

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <limits>
#include <sstream>
#include <string>
#include <unordered_map>
#include <algorithm>

typedef std::vector<double> row_matrix;
typedef std::vector<row_matrix> matrix;
typedef std::unordered_map<std::string, std::string> umap_str2str;

// ---------------------------------------------
void generate_values(double tstart, double tstop, double tstep, double curval, double curdur, double puldur, int ncols, matrix& out_matrix)
// Generate a matrix of values with time as the first column and values in subsequent columns (ncols)
{
  row_matrix onerow;
  double curvalnow = 0.0;
  long double tnow = 0.0;
  long double pulstart = 0.0;
  long double pulstop = 0.0;
  long double curstart = 0.0;
  long double curstop = 0.0;
  unsigned counter=-1;
  while(tnow < tstop)
    {
      counter++;
      tnow=tstart + (counter*tstep);
      if ((tnow >= (pulstop+1e-12)) | (tnow >= (pulstop-1e-12))){ 
	pulstart = tnow;
	pulstop = pulstart + puldur;
	curstart = pulstart;
	curstop = curstart + curdur;
      }
      if ((tnow > (curstop+1e-12)) | (tnow > (curstop-1e-12))){ 
	curvalnow = 0.0;
      }
      else{ 
	curvalnow = curval;
      }
      onerow.push_back(tnow);
      for(int i = 0; i < (ncols-1); i++){
	  onerow.push_back(curvalnow);
      }
      out_matrix.push_back(onerow);
      onerow.clear();
      // std::cout << tnow << "\t" << pulstart << "\t" << pulstop << "\t" << curstart << "\t" << curstop << "\t" << curvalnow << std::endl;
    }
}
// -------------------------------------------
void write_values_2file(std::vector<double> in_vals, std::ofstream &outfile, const char word_delim)
{
  std::stringstream write_buffer_double;
  if( (outfile.is_open()) == true && (outfile.is_open() == true) ) {
    for(std::vector<double>::iterator i = in_vals.begin(); i != in_vals.end(); i++){
      // outfile << std::setprecision(std::numeric_limits<double>::digits10 + 1) << *i << word_delim;
      outfile << std::setprecision(10) << *i << word_delim;
      // outfile << write_buffer_double; 
    }
    outfile << std::endl;
  }
  else {
    std::cout << "File could not opened!" << std::endl;
  }  
}
// ------------------------------------------
void get_arguments(const int argc, char* argv[], umap_str2str &args)
// Maps the arguments entered to an unordered map
// Usage: exec_name --argument_name argument_value
{
  // Seperate the argument names (prefixed by --) and argument values into two string vectors
  std::vector<std::string> argnames;
  std::vector<std::string> argvals;
  std::stringstream argss;

  // Seperate the argument names and values into seperate vector of strings
  for(int i=1;i<argc;i=i+2){
    argss.clear();
    argss.str("");
    argss.str(std::string());
    argss << argv[i];
    argnames.push_back(argss.str());
    argss.clear();
    argss.str("");
    argss.str(std::string());
    if( (i+1) < argc){
      argss << argv[i+1];
      argvals.push_back(argss.str());
    }
  }
  // Check for equal sizes
  if(argnames.size() != argvals.size()){
    std::cerr << "Error! : no.of argument names and values are not equal" << std::endl;
    return;
  }
  // Check for --prefix in argument names
  if(!std::all_of(argnames.begin(),argnames.end(),[](std::string str){return(str.find("--") == 0);})){
      std::cerr << "Error! : argument names should begin with --" << std::endl;
    }
  // copy argnames and agvalues to umap
  {
    std::vector<std::string>::iterator itn,itv; // iterators for argnames and argvals
    itn = argnames.begin();
    itv = argvals.begin();
    std::string argnstriped;
    for(size_t i=0; i< argnames.size(); i++){
      args.emplace((*itn).substr((*itn).find("--")+2),*itv);
      // std::cout << *itn << " " << *itv << "\n";
      *itn++;
      *itv++;
    }
  }
  return;
}
// -----------------------------------------------
bool check_parameters(umap_str2str args, std::vector<std::string> pnames)
// Checks for paramater names in arguments
{
  bool found_all_params = false;
  if(std::all_of(pnames.begin(),pnames.end(),[args](std::string pname){
	bool keysfound = false; 
	for(auto el:args){
	  if (el.first.find(pname) != std::string::npos){
	    keysfound = true;
	    // std::cout << el.first << " " << pname << "\n";
	    // std::cout <<"key found" << "\n";
	  }
	}
	return(keysfound);})){
    found_all_params = true;
  }
  return(found_all_params);
}
// ----------------------------------------------
std::vector<std::string> get_paramvalues_by_keymatch(const umap_str2str args,std::string pname)
// Get all the paramter values that match a given key
{
  std::vector<std::string> pvalues;
  for(auto el:args){
    if (el.first.find(pname) != std::string::npos){
      pvalues.push_back(el.second);
    }
  }
  // if the vector contains time then bring it to the first position
  std::vector<std::string>::iterator it = std::find(pvalues.begin(),pvalues.end(),"time");
  if(it != pvalues.end()){
    std::string tempstr=pvalues[0];
    pvalues[0] = *it;
    *it = tempstr;
  }
      
  return(pvalues);
}
// ----------------------------------------------
int main(int argc, char* argv[])
{
  // assign parameter names
  std::vector<std::string> pnames{"fname","colname","ncols","tstart","tstop","tstep","pulse-amp","pulse-on-dur","pulse-period","sepchar"};
  // initialize an unordered_map to store key value pairs
  umap_str2str args;
  // copy arguments (parameter name and value pairs) to the map
  get_arguments(argc,argv,args);
  // check wether all the parameters are present
  if(!check_parameters(args,pnames)){
    std::cerr << "Some parameters not supplied" << "\n";
    std::cerr << "USAGE: generate_runtime_mod_file_1param_fixedstep --fname fname --colname1 time --colname2 atp_ext0 --ncols 2 --tstart 10 --tstop 12 --tstep 5e-6 --pulse-amp 10e-6 --pulse-on-dur 2 --pulse-period 2 --sepchar ','" << "\n";   
    return(-1);
  }
  std::vector<std::string> colnames;
  // Multiple column names could be provide so get all of them
  colnames = get_paramvalues_by_keymatch(args,"colname");
  for (auto el:colnames){
    std::cout << el << " ";
  }
  std::cout << std::endl;
  // intialize a matrix to store values (each row and column)
  matrix values;
  unsigned int ncol = colnames.size();  
  // copy values from the map to variables

  std::string fname = args.at("fname"); // filename
  char sepchar = args.at("sepchar").c_str()[0]; // separater character

  double tstart = std::stod(args.at("tstart"));
  double tstop = std::stod(args.at("tstop"));
  long double tstep = std::stod(args.at("tstep"));

  long double pulse_amp = std::stod(args.at("pulse-amp"));
  long double pulse_on_dur = std::stod(args.at("pulse-on-dur"));
  long double pulse_period = std::stod(args.at("pulse-period"));

  std::string aline;
  std::ofstream outfile;
  
  // Open file
  outfile.open(fname);    

  // Write header line
  if( (outfile.is_open()) == true && (outfile.is_open() == true) ) {
    for(std::vector<std::string>::iterator i = colnames.begin(); i != colnames.end(); i++){
      outfile << *i << sepchar; 
    }
    outfile << std::endl;
    // Update values & write values
    generate_values(tstart,tstop,tstep,pulse_amp,pulse_on_dur,pulse_period,ncol,values);
    for(size_t i = 0; i < values.size(); i++){
      // std::cout << values[i] << std::endl;
      write_values_2file(values[i],outfile,sepchar);
    }
  }
  else {
    std::cout << "File could not opened!" << std::endl;
  }

  // Close file
  outfile.close();

}

