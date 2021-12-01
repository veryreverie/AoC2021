#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(void){
  std::vector<int> vec;
  
  std::ifstream infile("input");
  if (infile.is_open()){
    std::string line;
    while (getline(infile, line)){
      vec.push_back(std::stoi(line));
    }
  }
  infile.close();
  
  int count = 0;
  for (int i=0; i+3<vec.size(); ++i){
    if (vec[i+3]>vec[i]){
      ++count;
    }
  }
  
  std::cout << count << std::endl;
}
