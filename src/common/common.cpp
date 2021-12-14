#include "common.hpp"

Ignore::Ignore(const std::streamsize& n, const char& delim){
  _n = n;
  _delim = delim;
}

std::istream& operator>>(std::istream& is, Ignore ignore){
  return is.ignore(ignore._n, ignore._delim);
}

std::vector<std::string> split(std::istream& input, const char& delim){
  std::string line;
  std::vector<std::string> result;
  while (std::getline(input, line, delim)){
    result.push_back(line);
  }
  return result;
}

std::vector<std::string> split(const char* input, const char& delim){
  std::istringstream iss(input);
  return split(iss, delim);
}

std::vector<std::string> read_file(const std::string& filename){
  std::ifstream infile(filename);
  return split(infile);
}
