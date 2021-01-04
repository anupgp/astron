// Time-stamp: <2016-06-01 14:48:50 anup>
// Description: cpp functions for string manipulation 

#ifndef STRING_FUNCTIONS_HPP_INCLUDED
#define STRING_FUNCTIONS_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

#include <sstream>
#include <string>
#include <cstring>
#include <cctype>

std::string get_string_pre(const std::string& instring, const char sep)
// Get the string segment before the sep
{
  size_t lastpos = instring.rfind(sep,instring.length());
  if(lastpos != instring.length()){
    return(instring.substr(0,lastpos));
  }
  else
    std::cout << "string pre not found!" <<  std::endl;
  return("");
}

std::string string_trim(const std::string& instring)
// Trims away the newlines, tabs and whitespaces from the left and right part of the given string
{
  std::vector<char> badchars = {'\n','\t',' '};
  std::string outstring = instring;
  bool ltrim = false;
  do{
    ltrim = true;
    for(auto el: badchars){
      if( el == outstring.front()){
	outstring.erase(0,1);
	ltrim = false;
      }
    }
  } while (!ltrim);
  bool rtrim = false;
  do{
    rtrim = true;
    for(auto el: badchars){
      if( el == outstring.back()){
	outstring.erase(outstring.length()-1,1);
	rtrim = false;
      }
    }
  } while (!rtrim);
  return(outstring);
}	

std::vector<std::string> get_paramnames(const std::string strin, const char sep)
// Reads a string segment and returns a vector of strings from splitting the given string 
{
  std::vector<std::string> strout;
  std::size_t lpos = 0;
  std::size_t rpos = 0;
  while (lpos < strin.length()){
    rpos = strin.find(sep,lpos);
    if (rpos > strin.length()-1){
      rpos = strin.length();
    }
    strout.push_back(strin.substr(lpos,rpos-lpos));
    // std::cout << lpos << " " << rpos << " " << strin.length() << " " << strin.substr(lpos,rpos-lpos) << std::endl;
    // std::cin.get();
    lpos = rpos + 1;
  }
  return(strout);
}

std::vector<double> get_paramvalues(const std::string strin, const char sep)
// Reads a string segment and returns a vector of strings from splitting the given string 
{
  double value;
  std::string str;
  std::vector<double> values;
  std::size_t lpos = 0;
  std::size_t rpos = 0;
  while (lpos < strin.length()){
    rpos = strin.find(sep,lpos);
    if (rpos > strin.length()-1){
      rpos = strin.length();
    }
    try {
      // value = ::atof(strnum.c_str());
      str = string_trim(strin.substr(lpos,rpos-lpos));
      value = std::atof(str.c_str());
    }
    catch(const std::exception& e) {
      std::cerr << "[insilico::] Simulation Exception: "
		<< "supplied with file that contains improper value: "<< strin.substr(lpos,rpos-lpos) <<'\n';
      exit(1);
    }
    values.push_back(value);
    // std::cout << lpos << " " << rpos << " " << strin.length() << " " << strin.substr(lpos,rpos-lpos) << std::endl;
    // std::cin.get();
    lpos = rpos + 1;
  }
  return(values);
}

// std::string get_string_segment(const std::string instring, const std::string param_str, const char sep)
// // Reads a string and returns a line/segment that contains a given string and flanked by the sep chars 
// {
//   // Find the first position that matches the target string (param_str)
//   std::size_t strpos = instring.find(param_str);
//   std::string strseg;
//   if (strpos < instring.length()){
//     // Find start and end pos of the segment that contains the string
//     std::size_t startpos = instring.rfind(sep,strpos);
//     std::size_t finishpos = instring.find(sep,strpos);
//     if (startpos > strpos && finishpos > strpos && finishpos < instring.length()){
//       strseg = instring.substr(startpos+1, finishpos-startpos-1);
//       // std::cout << "Found string at " << strpos << std::endl;
//       // std::cout << "seg start = " << startpos << " " << " seg finish = " << finishpos << std::endl;
//       // std::cout << "The segment = " << strseg << std::endl;
//       std::cout << " The param string found: " << strseg <<  std::endl;
//     }
//   }
//   return(strseg);
// };

std::string get_string_segment(const std::string instring, const std::string param_str, const char sep1, const char sep2)
// Reads a string and returns a line/segment that contains a given string and flanked by the sep chars 
{
  // Find the first position that matches the target string (param_str)
  std::size_t strpos = instring.find(param_str);
  std::string strseg;
  if (strpos < instring.length()){
    // Find start and end pos of the segment that contains the string
    std::size_t startpos = instring.find(sep1,strpos);
    std::size_t finishpos = instring.find(sep2,startpos);
    if (startpos > strpos && finishpos > strpos && finishpos < instring.length()){
      strseg = instring.substr(startpos, finishpos-startpos);
      std::cout << "instring: " << instring << " param_string: "  << param_str << " pos = " << strpos << std::endl;
      std::cout << "sep1 = " << sep1 << " sep2 = " << sep2 << std::endl;
      std::cout << "segment: " << strseg << "start = " << startpos << " finish = " << finishpos << std::endl;

    }
  }
  else{
    std::cout << " fun: get_string_segment - param string not found: " << strseg <<  std::endl;
  }
  return(strseg);
};

void get_segment_pos(const std::string instring, const std::string param_str, const char sep1, const char sep2,unsigned &startpos, unsigned &finishpos)
// Reads a string and returns a line/segment that contains a given string and flanked by the sep chars 
{
  startpos = 0;
  finishpos = 0;
  // Find the first position that matches the target string (param_str)
  startpos = instring.find(param_str);
  if (startpos < instring.length()){
    // Find start and end pos of the segment that contains the string
    finishpos = instring.find(sep2,startpos)-1;
    if (startpos < instring.length() && finishpos > startpos && finishpos < instring.length()){
      std::cout << "instring: " << instring << " param_string: "  << param_str << " pos = " << startpos << std::endl;
      std::cout << "sep1 = " << sep1 << " sep2 = " << sep2 << std::endl;
      std::cout << "segment: " << instring.substr(startpos,finishpos-startpos+1) << " start = " << startpos << " finish = " << finishpos << std::endl;
    }
  }
  else{
    std::cout << " Error in FUN:get_segment_pos. segment not found" << std::endl;
  }
};

std::string get_string_post(const std::string& instring, const char sep)
// Get the string segment after the sep
{
  size_t lastpos = instring.rfind(sep,instring.length());
  if(lastpos != instring.length()){
    return(instring.substr(lastpos+1, instring.length()-lastpos-1));
  }
  else
    return("");
}

std::vector<std::string> generate_filenames(std::string fsourcename, int ncopies, int postfixbeg)
// generate a string vector of filenames from the source filename 
{
  // Get file path
  std::string filepath = "";
  filepath = get_string_pre(fsourcename,'/');
  // Get file basename
  std::string filename = ""; 
  filename = get_string_post(fsourcename,'/');
  std::string filenamebare =  get_string_pre(filename,'.');
  // Get file extension name
  std::string extname = "";
  extname = get_string_post(fsourcename,'.');
  std::cout << fsourcename << " " << filepath << " " << filenamebare << " " << extname << std::endl;
  // Generate a vector of new filename with absolute paths
  std::vector<std::string> fdestnames;
  for(int i = postfixbeg; i < (postfixbeg + ncopies); i++){
    fdestnames.push_back(filepath + "/" + filenamebare + std::to_string(i) + "." + extname);
  }
  return(fdestnames);
}

// std::string change_param_value(std::string inseg, const std::string parname, double newval, char pairdelim, char segdelim)
// {
//   // Function will replace the  old value in the given line based on the variable id and given new value
//   std::ostringstream os;
//   os << std::setprecision(12) << newval;
//   std::string newval_string = os.str();
//   std::string outseg = inseg;
//   //std::cout << aline << std::endl;
//   size_t param_pos = inseg.find(parname);
//   size_t startpos = inseg.find(pairdelim, param_pos);
//   size_t finishpos = inseg.find(segdelim, param_pos);
//   if (startpos != inseg.length() && finishpos != inseg.length()){
//     std::string replaced_value = inseg.substr(startpos+1, finishpos - startpos - 1);
//     outseg.replace(startpos+1, finishpos - startpos - 1, "");
//     outseg.insert(startpos+1, " " + newval_string);
//     // std::cout << "inseg before = " << inseg << std::endl;
//     // std::cout << "inseg after = " << outseg << std::endl;
//     return(outseg);
//   }
//   else{
//     std::cout << " The param string could not be found" <<  std::endl;
//     return("");
//   } 
// }

void change_seg_param_value(std::string &seg, const std::string parname, double newval, char pairdelim, char segdelim1, char segdelim2)
{
  // Function will replace the  old value in the given line based on the variable id and given new value
  std::ostringstream ssnewseg;
  size_t parampos = seg.find(parname);
  size_t valstartpos = seg.find(pairdelim, parampos) + 1;
  size_t valfinishpos = seg.find(segdelim2, parampos) - 1;
  if (valstartpos != seg.length()){
    std::string replaced_value = seg.substr(valstartpos, valfinishpos - valstartpos + 1);
    // copy part of the inseg until (including) pairdelim
    ssnewseg << seg.substr(parampos,valstartpos-parampos);
    // add a space
    ssnewseg << " ";
    // add the new value 
    ssnewseg << std::setprecision(12) << newval << " ";
    // add the remaining portion of the string
    ssnewseg << seg.substr(valfinishpos + 1, (seg.length()-valfinishpos+1));
    // swap the seg with the new string stream
    std::string newseg = ssnewseg.str();
    seg.swap(newseg);
  }
  else{
    std::cout << " Change_param_value: param string could not be found" <<  std::endl;
  } 
}

std::string replace_string_segment(const std::string instring, char sep1,char sep2, const std::string &oldseg, const std::string &newseg)
// Replace a segment in a given string with a new segment 
{
  std::size_t strpos = instring.find(oldseg);
  std::string newstr;
  if (strpos != instring.length()){
    // Find start and end pos of the segment that contains the string
    std::size_t startpos = instring.rfind(sep1,strpos);
    std::size_t finishpos = instring.find(sep2,strpos);
    if (startpos != instring.length() && finishpos <= instring.length()){
      std::string strseg = instring.substr(startpos+1, finishpos-startpos-1);
      newstr = instring;
      newstr.replace(startpos+1, finishpos-startpos-1, newseg);
      std::cout << "Found string at " << strpos << std::endl;
      // std::cout << "seg start =" << startpos << " " << "seg finish = " << finishpos << std::endl;
      // std::cout << "old segment = " << strseg << std::endl;
      // std::cout << "new segment = " << newstr << std::endl;
    }
  }
  else{
    std::cout << " The param string could not be found" <<  std::endl;
  }
  return(newstr);
}


#endif	// STRING_FUNCTIONS_HPP_INCLUDED
