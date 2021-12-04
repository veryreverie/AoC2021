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
    Instruction(const std::string& s);
};

std::ostream& operator<<(std::ostream& os, const Instruction& instruction){
  return os << instruction.direction << ' ' << instruction.distance;
}

std::istream& operator>>(std::istream& is, Instruction& instruction){
  return is >> instruction.direction >> instruction.distance;
}

Instruction::Instruction(const std::string& s){
  std::istringstream(s) >> *this;
}

int main(void){
  std::vector<Instruction> instructions;
  
  std::ifstream infile("input");
  if (infile.is_open()){
    std::string line;
    while (getline(infile, line)){
      instructions.push_back(Instruction(line));
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
  
  int aim(0);
  position = 0;
  depth = 0;
  for (Instruction instruction : instructions){
    if (instruction.direction=="forward"){
      position += instruction.distance;
      depth += instruction.distance*aim;
    } else if (instruction.direction=="up"){
      aim -= instruction.distance;
    } else if (instruction.direction=="down"){
      aim += instruction.distance;
    }
  }
  std::cout << position*depth << std::endl;
}
