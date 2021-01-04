// Time-stamp: <2017-02-16 09:42:56 anup>
// This function will read a csv file and make a new file from a slice of the original file
// The program will accept a column name as index column, a range from the index column to slice

#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>

typedef std::unordered_map<std::string, std::vector<double>> umap_string2vec;
// --------------------------------------
void print_usage(void){
  // Function prints usage information
  std::cout << "USAGE: slicecsv filename columnname startrow endrow" << std::endl;
}
// ---------------------------------------
void get_arguments(int argc, char *argv[], std::string &fname, std::string &colname, double &rowbegin, double &rowend){
  // Function get arguments passed during runtime
  std::string rowb,rowe;
  switch (argc)
    {
    case (1): {
      break;
    }
    case (2): {
      fname = argv[1];
      break;
    }
    case (3): {
      fname = argv[1];
      colname = argv[2];
      break;
    }
    case (4): {
      fname = argv[1];
      colname = argv[2];
      rowb = (argv[3]);
      break;
    }
    case (5): {
      fname = argv[1];
      colname = argv[2];
      rowb = argv[3];
      rowe = argv[4];
      break;
    }
    default: {
      break;
    }
    }
  if(argc < 5){
    print_usage();
    return;
  }
  try {
    rowbegin = std::stod(rowb);
    rowend = std::stod(rowe);
  }
  catch(...) {std::cerr << "string to double conversion failed!" << "\n"; return;}
  std::cout << fname << "\n" << colname << "\n" << rowbegin << "\n" << rowend << "\n";
}
// --------------------------------------
void umapcol(std::string fname, umap_string2vec  &csvdat){
  // strore a csv file into columnwise unoredered_map of vectors
  // Open source file for reading
  std::ifstream fhand;
  try{
    fhand.open(fname,std::ios::in);
  }
  catch(...){
    std::cerr << "Could not find the file!" << "\n";
    return;
  }
  if (!fhand.good()){
    std::cout << "File could not be opened!" << std::endl;
    return;
  }
  // The first two lines are always read, assuming the first is the header line
  bool readheader = false;
  unsigned counter = 0;
  std::string aline;
  std::string item;
  std::istringstream ss;
  std::vector<std::string> arow,colnames;
  while(getline(fhand,aline,'\n')){
    counter++;
    arow.clear();
    ss.str(std::string());
    ss.clear();			// !!!Very important!!!
    ss.str(aline);
    // split stringstream with the delimiter character
    while(std::getline(ss,item,',')){
	arow.push_back(item);
    }
    // if (!ss && item.empty())
    //   {
    // 	// If there was a trailing comma then add an empty element.
    // 	arow.push_back("");
    //   }
    if(!readheader){
      // Read the header line to get column names
      colnames = arow;
      readheader=true;
      // Create keys/elments to the csvmap
      for(auto el:colnames){
      	csvdat.emplace(el,std::vector<double>());
      }
    }
    if(readheader){
      // Push contents of the row to the map
      std::vector<std::string>::iterator itc = colnames.begin();
      std::vector<std::string>::iterator itr = arow.begin();;
      double val;
      while(itc < colnames.end()){
	try {
	  std::istringstream ss2(*itr);
	  ss2 >> val; 
	}
	catch(...) {
	  std::cout << *itr << " " << val << "\n";
	}
        csvdat[*itc].push_back(val);
        itc++;
        itr++;
      }
    }
  }
  // Close the file
  fhand.close();   
}
// ------------------------------------
void umaprow(std::string fname, umap_string2vec &csvdat){
  // strore a csv file into rowwise unoredered_map of vectors
  // Open source file for reading
}
// ------------------------------------
void print_csv(umap_string2vec csvdat){
    for(auto el:csvdat){
    std::cout << el.first << ":";
    for(auto it = el.second.begin(); it < el.second.begin() + 10; it++){
      std::cout << *it << " ";
    }
    std::cout << "\n";
  }
}
// ----------------------------------
void write_csv(umap_string2vec csvdat, std::string fname){
  // This function will write an unordered_map object to csv file
  // Open the file for writing
    std::ifstream fhand;
  try{
    fhand.open(fname,std::ios::out);
  }
  catch(...){
    std::cerr << "Could not find the file!" << "\n";
    return;
  }
  if (!fhand.good()){
    std::cout << "File could not be opened!" << std::endl;
    return;
  }

  // 
    for(auto el:csvdat){
    for(auto it = el.second.begin(); it < el.second.begin() + 10; it++){
      std::cout << *it << " ";
    }
    std::cout << "\n";
  }
  // Close the file
  fhand.close();   
}
// ----------------------------------
main(int argc, char *argv[]){
  umap_string2vec cwdat; 
  std::string fname,colname;
  double startrow,endrow = 0.0;
  get_arguments(argc,argv,fname,colname,startrow,endrow);
  umapcol(fname,cwdat);
  std::string fname2 = "/home/anup/goofy/projects/data/astron/raw/astrocyte/test.csv";
  return(0);
}
