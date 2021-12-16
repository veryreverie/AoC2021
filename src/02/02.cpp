#include "02.hpp"

namespace Day02{
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

  std::tuple<long long,long long> day02(const std::vector<std::string>& flines){
    std::vector<Instruction> instructions;
    for (const auto& fline : flines){
      instructions.push_back(Instruction(fline));
    }
    
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
    int result1 = position*depth;
    
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
    int result2 = position*depth;
    
    return {result1, result2};
  }
}
