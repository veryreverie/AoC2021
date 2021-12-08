#include "07.hpp"

class Crabs{
  public:
    std::vector<int> positions;
    
    Crabs(const std::vector<int>& positions);
};

Crabs::Crabs(const std::vector<int>& _positions){
  positions = _positions;
}

std::tuple<long long,long long> day07(const std::vector<std::string>& flines){
  Crabs crabs(split<int>(flines[0], ','));
  
  int max_position = *std::max_element(crabs.positions.begin(), crabs.positions.end());
  
  std::vector<int> linear_distances;
  for (int i=0; i<=max_position; ++i){
    int linear_distance = 0;
    for (const auto& position : crabs.positions){
      linear_distance += std::abs(position-i);
    }
    linear_distances.push_back(linear_distance);
  }
  int min_linear_distance = *std::min_element(
    linear_distances.begin(),
    linear_distances.end()
  );
  
  std::vector<int> triangular_distances;
  for (int i=0; i<=max_position; ++i){
    int triangular_distance = 0;
    for (const auto& position : crabs.positions){
      int linear_distance = std::abs(position-i);
      triangular_distance += (linear_distance*(linear_distance+1))/2;
    }
    triangular_distances.push_back(triangular_distance);
  }
  int min_triangular_distance = *std::min_element(
    triangular_distances.begin(),
    triangular_distances.end()
  );
  
  return {min_linear_distance, min_triangular_distance};
}
