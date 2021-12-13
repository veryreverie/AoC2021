#ifndef COMMON_HPP
#define COMMON_HPP

#include <algorithm>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iterator>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

class Ignore{
  private:
    std::streamsize _n;
    char _delim;
  public:
    Ignore(const std::streamsize& n=1, const char& delim = EOF);
    friend std::istream& operator>>(std::istream& is, Ignore ignore);
};

template <class T1, class T2>
bool item_in_list(const T1& element, const T2& list){
  return std::find(list.begin(), list.end(), element) != list.end();
}

#endif
