#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <exception>
#include <iomanip>
#include <numeric>
#include <algorithm>

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

class Crabs{
  public:
    std::vector<int> positions;
    
    Crabs(const std::vector<int>& positions);
};

Crabs::Crabs(const std::vector<int>& _positions){
  positions = _positions;
}

void day07(std::vector<std::string> flines){
  Crabs crabs(split<int>(flines[0], ','));
  for (const auto& c : crabs.positions){
    std::cout << c << std::endl;
  }
  
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
  std::cout << min_linear_distance << std::endl;
  
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
  std::cout << min_triangular_distance << std::endl;
}

int main(void){
  std::ifstream infile("input");
  std::vector<std::string> lines;
  if (infile.is_open()){
    std::string line;
    while (getline(infile, line)){
      lines.push_back(line);
    }
  }
  infile.close();
  
  day07(lines);
}
