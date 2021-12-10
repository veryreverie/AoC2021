#ifndef COMMON_HPP
#define COMMON_HPP

#include <algorithm>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iterator>
#include <iostream>
#include <map>
#include <numeric>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

template <class T>
T munch(std::istringstream& iss, char delim) {
  std::string token;
  std::getline(iss, token, delim);
  T result;
  std::istringstream(token) >> result;
  return result;
}

template <class T>
std::vector<T> split(const std::string& s, char delim) {
  std::istringstream iss(s);
  std::vector<T> result;
  while (not iss.eof()){
    result.push_back(munch<T>(iss, delim));
  }
  return result;
}

template <class T1, class T2>
bool element_in_list(const T1& element, const T2& list){
  return std::find(list.begin(), list.end(), element) != list.end();
}

#endif
