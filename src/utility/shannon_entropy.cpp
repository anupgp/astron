// Time-stamp: <2018-04-17 11:40:52 anup>
// This function takes a csv file containing spike arrival times to compute Shannon entropy
// Ref: reinagel2000,strong1998,shannon1949(book:The mathematical theory of communication)
// ---------------------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <limits>
#include <sstream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <numeric>

typedef std::vector<double> row_mat_double;
typedef std::vector<row_mat_double> mat_double;
typedef std::vector<int> row_mat_int;
typedef std::vector<row_mat_int> mat_int;
typedef std::unordered_map<std::string, std::string> umap_str2str;
typedef std::unordered_map<unsigned long long, int> umap_usllint2int;
typedef std::unordered_map<int, int> umap_int2int;
typedef std::unordered_map<int, double> umap_int2double;

// -----------------------------------------------------
// Read file containing spike event times into a matrix
int load_event_times(std::string fname, mat_double &etm)
{
  std::ifstream fhand;
  // Open file
  std::cout << "Preparing to read the file: " << fname << "\n";
  fhand.open(fname);
  if(fhand.is_open() == true) {
    std:: cout << "File is opened\n";
  }
  else{
    std::cout << "File could not be opened!/n";
    return(-1);
  }
  // Read data line by line to the matrix
  // Assuming no header line
  unsigned counter = 0;
  std::string aline;
  std::string item;
  std::istringstream ss;
  std::vector<double> arow;
  std::string::size_type str_sz;     // alias of size_t
  while(std::getline(fhand,aline)){
    std::cout << aline << "\n";
    counter++;
    arow.clear();
    ss.str(std::string());
    ss.clear();			// !!!Very important!!!
    ss.str(aline);
    // split stringstream with the delimiter character
    while(std::getline(ss,item,' ')){
      // std::cout << item <<  " " << std::setprecision(10) << std::stod(item) << "\n";
      arow.push_back(std::stod(item,&str_sz));
    }
    etm.push_back(arow);
  }
  // Close file
  std::cout << "Preparing to close the file...";
  fhand.close();
  std::cout << "File closed.\n";
  return(0);
}
// ----------------------------------------------------
// function to check if element is within the bound of a vector
void update_hbins(std::vector<double> vec, double val, std::vector<int> &hrow)
{
  int count=-1;
  bool found=false;
  for(std::vector<double>::iterator it=vec.begin();it <(vec.end()-1);it++){
    count++;
    if((val>=*it) && (val <*(it+1))){
      found=true;
      break;
    }
  }
  if(found)
    hrow[count]=hrow[count]+1;
}
// -----------------------------------------------------
// count all the types of bitcominations of bit patterns of a given wordlength from the discretized event matrix
void count_word_combinations(int wordlen, mat_int etmh, umap_usllint2int &wordch)
{  
  for(std::vector<std::vector<int>>::iterator r = etmh.begin(); r != etmh.end(); r++){
    // for(auto el : (*r)){
      // std::cout << el << " ";
    // }
    // std::cout << std::endl;
    // read the row in chunks of wordlength
    std::vector<int>::iterator c = (*r).begin();
    while(c != (*r).end()){
      std::vector<int>::iterator itbegin=c;
      std::vector<int>::iterator itend=c+wordlen;
      row_mat_int awordvec(itbegin,itend);
      // ---------------------
      // convert wordvec to an integer
      unsigned long long wordint = 0;
      int count=-1;
      for (auto el:awordvec){
	count++;
	wordint = wordint + ((el>0)*std::pow(2,count));
	// std::cout << el << " ";
      }
      // std::cout << "\t" << wordint << std::endl;
      // populate and increment the map with the wordint as the key
      std::pair<umap_usllint2int::iterator, bool> awordinsert;
      awordinsert = wordch.emplace(wordint,1);
      if(awordinsert.second == false){
	wordch.at(awordinsert.first->first)++;
      }
      // ----------------------
      c = c + wordlen;
      // break if a full word can not be obtained from the remaining elements of the row
      if((c+wordlen-1)>= (*r).end())
	break;
    }
  }
}
// ---------------------------------------------------
// a general function to display unordered_map
template<class Key, class Val>
void display_umap(const std::unordered_map<Key, Val> inumap)
{
  for (auto el : inumap){
    std::cout << el.first << ":\t" << el.second << std::endl;
  }
}
// ---------------------------------------------------
// a general function to display a matrix (vector of vector)
template<class T>
void display_matrix(const std::vector<T> mat)
{
  for (auto el1 : mat){
    for(auto el2 : el1){
      std::cout << el2 << " ";
    }
    std::cout << std::endl;
  }
}
// -------------------------------------------------- 
// a general function to sum the values unordered_map
template<typename Key, typename Val>
double sumvals_umap(const std::unordered_map<Key, Val> inumap)
{
  // get count total word count
  double totalcount=0.0;
  for(auto el:inumap){
    totalcount = totalcount + el.second;
  }
  // std::cout << "Total count = " << totalcount << std::endl;
  return(totalcount);
}
// -----------------------------------------------------
// discretize events in the event time matrix to a matrix of time bins
mat_int discretize_events(double tstart,double tstop, double binwidth, mat_double etm)
{
  // generate the hist matrix
  double tdur = tstop-tstart;
  int histlen = std::floor(tdur/binwidth);
  std::cout << histlen << "\n";
  mat_int etmh;
  row_mat_int hrow(histlen,0);
  // generate bins
  row_mat_double hbins; 	// has a length = histlen+1;
  for(int i=0;i<=histlen;i++){
    hbins.push_back(tstart+(i*binwidth));
  }
  // populate the hist matrix from event times
  for(std::vector<std::vector<double>>::iterator r = etm.begin(); r != etm.end(); r++){
    // change hrow values to zero
    for(std::vector<int>::iterator ith=hrow.begin();ith<hrow.end();ith++)
      *ith=0;
    for(std::vector<double>::iterator c = (*r).begin(); c != (*r).end(); c++){
      update_hbins(hbins,*c,hrow);
    }
    etmh.push_back(hrow);
  }
  return(etmh);
}
// ----------------------------------------------------
// convert the counts in word histogram counts (wordhistmap) to probability
void wordcounts2prob(const umap_usllint2int wordch, umap_int2double &wordph)
{
  double totalcount=sumvals_umap(wordch);
  std::cout << "Total count = " << totalcount << std::endl;
  // convert word counts to probability
  for(auto el:wordch){
    wordph.emplace(el.first,double(el.second/totalcount));
  }
}
// ----------------------------------------------------
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
      std::cout << *itn << " " << *itv << "\n";
      *itn++;
      *itv++;
    }
  }
  return;
}
// ------------------------------------------
bool check_parameters(umap_str2str args, std::vector<std::string> pnames)
// Checks for paramater names in arguments
{
  bool found_all_params = false;
  if(std::all_of(pnames.begin(),pnames.end(),[args](std::string pname){
	bool keysfound = false; 
	for(auto el:args){
	  if (el.first.find(pname) != std::string::npos){
	    keysfound = true;
	    std::cout << "Found option >> " << pname << ":" << "\t" << el.first << "\t" << el.second << "\n";
	  }
	}
	return(keysfound);})){
    found_all_params = true;
  }
  return(found_all_params);
}
// -----------------------------------
// function to calculate shannon entropy (bits/sec) from the values of the event time matrix (etm), binwidth in seconds and wordlength
double shannon_entropy(double tstart, double tstop, double binwidth, int wordlength, const mat_double etm)
{
  // discretize events to a matrix of time bins (dem:discretized event time matrix)
  mat_int detm;
  detm = discretize_events(tstart,tstop,binwidth,etm);
  // get histogram of word counts from discretized event matrix (dem)
  umap_usllint2int wordhistcountmap;
  count_word_combinations(wordlength,detm, wordhistcountmap);
  // convert word counts to probability
  umap_int2double wordhistprobmap;
  wordcounts2prob(wordhistcountmap,wordhistprobmap);
  // compute entropy
  double entropy=0;
  for(auto el:wordhistprobmap){
    entropy = entropy + (el.second*log2(el.second));
  }
  entropy = -entropy/(binwidth*wordlength);
  std::cout << "Entropy = " << entropy << " bits/sec" << std::endl;
  return(entropy);
}
// ---------------------------------------------
// compute shannon entropy for different set of discretization binsize and word length into a matrix
void shannon_entropy_multiparam(double tstart, double tstop,std::vector<double> disbins,mat_double etm, mat_double &entropymat)
{
  int maxwordlength;
  std::vector<double> arow;
    for(std::vector<double>::iterator itdb=disbins.begin();itdb<disbins.end();itdb++){
      maxwordlength = (tstop-tstart)/(*itdb);
      for(int wl = 1; wl <=maxwordlength; wl++){
	// compute Shannon entropy for the combination of histbin and wordlength
	double entropy = shannon_entropy(tstart,tstop,*itdb,wl,etm);
	// copy the entropy parameters and entropy to each row of the semat matrix
	arow.clear();
	arow.push_back(*itdb);
	arow.push_back(wl);
	arow.push_back(entropy);
	entropymat.push_back(arow);
      }
    }
}
// -----------------------------------
// given a matrix, column names and file name, write it into a file
void write_mat2file(mat_double inmat, std::string ofname, const char word_delim)
{
  std::ofstream fhand;
  // Open file
  std::cout << "Preparing to write matrix to file: " << ofname << "\n";
  fhand.open(ofname);
  if(fhand.is_open() == true) {
    std:: cout << "File is opened for writing\n";
  }
  else{
    std::cout << "File could not be opened!/n";
  }
  for (auto el1 : inmat){
    unsigned counter=0;
    for(auto el2 : el1){
      counter++;
      if(counter<el1.size())
	fhand << std::setprecision(10) << el2 << word_delim;
      else
	fhand << std::setprecision(10) << el2;
    }
    fhand << std::endl;
  }
  if(fhand.is_open()){
    fhand.close();      
  }  
}

  
  // std::stringstream write_buffer_double;
  // if( (outfile.is_open()) == true && (outfile.is_open() == true) ) {
  //   for(std::vector<double>::iterator i = in_vals.begin(); i != in_vals.end(); i++){
  //     // outfile << std::setprecision(std::numeric_limits<double>::digits10 + 1) << *i << word_delim;
  //     outfile << std::setprecision(10) << *i << word_delim;
  //     // outfile << write_buffer_double; 
  //   }
  //   outfile << std::endl;
  // }
  // else {
  //   std::cout << "File could not opened!" << std::endl;
  // }
// -----------------------------------
int main(int argc, char* argv[])
{
  // assign parameter names
  std::vector<std::string> pnames{"ifname","tstart","tstop","ofname"};
  // initialize an unordered_map to store key value pairs
  umap_str2str args;
  // copy arguments (parameter name and value pairs) to the map
  get_arguments(argc,argv,args);
  if(!check_parameters(args,pnames)){
    std::cerr << "Some parameters not supplied" << "\n";
    return(-1);
  }
  // read the file
  mat_double etm;
  load_event_times(args.at("ifname"),etm);
  // get histogram matrix
  double tstart=stod(args.at("tstart"));
  double tstop=std::stod(args.at("tstop"));
  std::vector<double> disbins = {500e-3,600e-3,700e-3,800e-3,900e-3,1.0,2.0,4.0,6.0,8.0,10.0};
  // populate the wordlengths vector from 1 to the maximum wordlength possible at maximum discretization time bin
  // for(int i=1; i<=num
  // double entropy = shannon_entropy(tstart,tstop,binwidth,wordlength,etm);
  mat_double entropymat;
  shannon_entropy_multiparam(tstart, tstop,disbins,etm, entropymat);
  display_matrix(entropymat);
  // write entropy matrix to file
  write_mat2file(entropymat,args.at("ofname"),',');
}
