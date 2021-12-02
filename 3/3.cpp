#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

class Instruction{
  public:
    std::string direction;
    int distance;
    friend std::ostream& operator<<(std::ostream& os, const Instruction& instruction);
    friend std::istream& operator>>(std::istream& is, Instruction& instruction);
};

std::ostream& operator<<(std::ostream& os, const Instruction& instruction){
  os << instruction.direction << ' ' << instruction.distance;
}

std::istream& operator>>(std::istream& is, Instruction& instruction){
  is >> instruction.direction >> instruction.distance;
}

int main(void){
  std::vector<Instruction> instructions;
  
  std::ifstream infile("input");
  if (infile.is_open()){
    std::string line;
    while (getline(infile, line)){
      std::istringstream linestream(line);
      Instruction instruction;
      linestream >> instruction;
      instructions.push_back(instruction);
    }
  }
  infile.close();
  
  int position(0);
  int depth(0);
  for (Instruction instruction : instructions){
    if (instruction.direction=="forward"){
      position += instruction.distance;
    } else if (instruction.direction=="up"){
      depth -= instruction.distance;
    } else if (instruction.direction=="down"){
      depth += instruction.distance;
    }
  }
  
  std::cout << position*depth << std::endl;
}
