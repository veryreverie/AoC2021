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

namespace Common{
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

  std::vector<std::string> split(std::istream& input, const char& delim='\n');
  std::vector<std::string> split(const char* input, const char& delim='\n');
  std::vector<std::string> read_file(const std::string& filename);
  
  template <class T1, class T2>
  auto min_map_value(const std::map<T1,T2>& map){
    return std::min_element(
      map.begin(),
      map.end(),
      [] (const auto& p1, const auto& p2){return p1.second < p2.second;}
    );
  }
  
  template <class T1, class T2>
  auto max_map_value(const std::map<T1,T2>& map){
    return std::max_element(
      map.begin(),
      map.end(),
      [] (const auto& p1, const auto& p2){return p1.second < p2.second;}
    );
  }
  
  template <class T1, class T2, class T3>
  auto min_map_value(const std::map<T1,T2,T3>& map){
    return std::min_element(
      map.begin(),
      map.end(),
      [] (const auto& p1, const auto& p2){return p1.second < p2.second;}
    );
  }
  
  template <class T1, class T2, class T3>
  auto max_map_value(const std::map<T1,T2,T3>& map){
    return std::max_element(
      map.begin(),
      map.end(),
      [] (const auto& p1, const auto& p2){return p1.second < p2.second;}
    );
  }
}

#endif
