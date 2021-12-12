#include "common.hpp"

Ignore::Ignore(const std::streamsize& n, const char& delim){
  _n = n;
  _delim = delim;
}

std::istream& operator>>(std::istream& is, Ignore ignore){
  return is.ignore(ignore._n, ignore._delim);
}
