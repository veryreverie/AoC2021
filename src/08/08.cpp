#include "08.hpp"

class Display{
  public:
    std::vector<std::string> digits;
    std::vector<std::string> output;
    
    Display();
    
    friend std::ostream& operator<<(std::ostream& os, const Display& display);
    friend std::istream& operator>>(std::istream& is, Display& display);
    Display(const std::string& s);
    
    int unique_outputs() const;
    std::map<int,std::string> get_num_to_rep() const;
    int unscrambled_output() const;
};

Display::Display(){
}

std::ostream& operator<<(std::ostream& os, const Display& display){
  for (const auto& digit : display.digits){
    os << digit << " ";
  }
  os << "| ";
  for (const auto& digit : display.output){
    os << digit << " ";
  }
  return os;
}

std::istream& operator>>(std::istream& is, Display& display){
  std::string token;
  for (int i=0; i<10; ++i){
    is >> token;
    std::sort(token.begin(), token.end());
    display.digits.push_back(token);
  }
  is >> token;
  for (int i=0; i<4; ++i){
    is >> token;
    std::sort(token.begin(), token.end());
    display.output.push_back(token);
  }
  return is;
}

Display::Display(const std::string& s){
  std::istringstream(s) >> *this;
}

int Display::unique_outputs() const {
  const std::array<int,4> unique_lengths{2,3,4,7};
  int result = 0;
  for (const auto& digit : output){
    if (item_in_list(digit.size(), unique_lengths)){
      result++;
    }
  }
  return result;
}

std::map<int,std::string> Display::get_num_to_rep() const {
  const std::string wires = "abcdefg";
  
  // num_to_rep[i] is the representation of the number i.
  std::map<int,std::string> num_to_rep;
  
  // real_to_rep["x"] is the string containing the representation of "x".
  // real_to_rep["xz"] is a string containing the representations of "x" and "z",
  //    in an unknown order.
  std::map<std::string,std::string> real_to_rep;
  
  // The representations of 0, 6 and 9, in an unknown order.
  std::vector<std::string> zero_six_nine;
  
  // The representations of 2, 3 and 5, in an unknown order.
  std::vector<std::string> two_three_five;
  
  // Identify the representations of the four numbers (1, 4, 7 and 8)
  //    which can be identified by representation length.
  // Separate the remaining numbers by representation length,
  //    and store them in zero_six_nine and two_three_five.
  for (const auto& rep : digits){
    int s = rep.size();
    if (s==2){
      num_to_rep[1] = rep;
    } else if (s==3){
      num_to_rep[7] = rep;
    } else if (s==4){
      num_to_rep[4] = rep;
    } else if (s==5){
      two_three_five.push_back(rep);
    } else if (s==6){
      zero_six_nine.push_back(rep);
    } else if (s==7){
      num_to_rep[8] = rep;
    } else {
      throw std::invalid_argument(rep);
    }
  }
  
  // Identify the representations of "cf" and "bd".
  real_to_rep["cf"] = num_to_rep[1];
  real_to_rep["bcdf"] = num_to_rep[4];
  real_to_rep["bd"] = "";
  for (const char& c : real_to_rep["bcdf"]){
    if (not item_in_list(c, real_to_rep["cf"])){
      real_to_rep["bd"].push_back(c);
    }
  }
  
  // Identify 0, 6 and 9 by noting that the only wire each does not contain is
  //    "c", "d" and "e" respectively.
  // These can be distinguished by comparing with the representations of "cf" and "bd".
  // This also identifies the representations of "c", "d" and "e".
  //    (and hence also "b" and "f", although these are not needed).
  for (const auto& rep : zero_six_nine){
    for (const char& c : wires){
      if (not item_in_list(c, rep)){
        if (item_in_list(c, real_to_rep["cf"])){
          num_to_rep[6] = rep;
          real_to_rep["c"] = c;
        } else if (item_in_list(c, real_to_rep["bd"])){
          num_to_rep[0] = rep;
          real_to_rep["d"] = c;
        } else {
          num_to_rep[9] = rep;
          real_to_rep["e"] = c;
        }
        break;
      }
    }
  }
  
  // Identify 2, 3 and 5, by noting that:
  //    2 is the only one of the three whose representation contains "e".
  //    5 is the only one of the three whose representation does not contain "c".
  //    3 is not 2 or 5.
  for (const auto& rep : two_three_five){
    if (item_in_list(real_to_rep["e"][0], rep)){
      num_to_rep[2] = rep;
    } else if (not item_in_list(real_to_rep["c"][0], rep)){
      num_to_rep[5] = rep;
    } else {
      num_to_rep[3] = rep;
    }
  }
  
  return num_to_rep;
}

int Display::unscrambled_output() const {
  // Get the mapping from numbers to their scrambled representation.
  auto num_to_rep = get_num_to_rep();
  
  // Reverse the map, to give the mapping from scrambled representation to number.
  std::map<std::string,int> rep_to_num;
  for (const auto& [num,rep] : num_to_rep){
    rep_to_num[rep] = num;
  }
  
  // Decode the representations, and construct the output in decimal.
  std::array<int,4> tens{1000,100,10,1};
  int result = 0;
  for (int i=0; i<4; ++i){
    const auto ref = rep_to_num.find(output[i]);
    if (ref!=rep_to_num.end()){
      result += tens[i]*ref->second;
    } else {
      throw std::invalid_argument(output[i]);
    }
  }
  
  return result;
}

std::tuple<long long,long long> day08(const std::vector<std::string>& lines){
  std::vector<Display> displays;
  for (const auto& line : lines){
    displays.push_back(Display(line));
  }
  
  int unique_outputs = 0;
  for (const auto& display : displays){
    unique_outputs += display.unique_outputs();
  }
  
  int output_sum = 0;
  for (const auto& display : displays){
    output_sum += display.unscrambled_output();
  }
  
  return {unique_outputs, output_sum};
}
