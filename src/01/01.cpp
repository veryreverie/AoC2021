#include "01.hpp"

namespace Day01{
  std::tuple<long long,long long> day01(const std::vector<std::string>& flines){
    std::vector<int> vec;
    for (const auto& fline : flines){
      vec.push_back(std::stoi(fline));
    }
    
    int count1 = 0;
    for (int i=0; i+1<vec.size(); ++i){
      if (vec[i+1]>vec[i]){
        ++count1;
      }
    }
    
    int count2 = 0;
    for (int i=0; i+3<vec.size(); ++i){
      if (vec[i+3]>vec[i]){
        ++count2;
      }
    }
    
    return {count1, count2};
  }
}
