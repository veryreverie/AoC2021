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
    if (std::find(unique_lengths.begin(), unique_lengths.end(), digit.size()) != unique_lengths.end()){
      result++;
    }
  }
  return result;
}

int Display::unscrambled_output() const {
  const std::string wires = "abcdefg";
  
  std::map<int,std::string> num_to_rep;
  std::map<std::string,int> rep_to_num;
  std::map<std::string,std::string> real_to_rep;
  
  std::vector<std::string> zero_six_nine;
  std::vector<std::string> two_three_five;
  for (const auto& digit : digits){
    int s = digit.size();
    if (s==2){
      num_to_rep[1] = digit;
      rep_to_num[digit] = 1;
    } else if (s==3){
      num_to_rep[7] = digit;
      rep_to_num[digit] = 7;
    } else if (s==4){
      num_to_rep[4] = digit;
      rep_to_num[digit] = 4;
    } else if (s==5){
      two_three_five.push_back(digit);
    } else if (s==6){
      zero_six_nine.push_back(digit);
    } else if (s==7){
      num_to_rep[8] = digit;
      rep_to_num[digit] = 8;
    } else {
      throw std::invalid_argument(digit);
    }
  }
  
  real_to_rep["cf"] = num_to_rep[1];
  real_to_rep["bcdf"] = num_to_rep[4];
  real_to_rep["bd"] = "";
  for (const char& c : real_to_rep["bcdf"]){
    if (real_to_rep["cf"].find(c)==std::string::npos){
      real_to_rep["bd"].push_back(c);
    }
  }
  
  for (const auto& rep : zero_six_nine){
    for (const char& c : wires){
      if (rep.find(c)==std::string::npos){
        if (real_to_rep["cf"].find(c)!=std::string::npos){
          num_to_rep[6] = rep;
          rep_to_num[rep] = 6;
          real_to_rep["c"] = c;
        } else if (real_to_rep["bd"].find(c)!=std::string::npos){
          num_to_rep[0] = rep;
          rep_to_num[rep] = 0;
          real_to_rep["d"] = c;
        } else {
          num_to_rep[9] = rep;
          rep_to_num[rep] = 9;
          real_to_rep["e"] = c;
        }
        break;
      }
    }
  }
  
  for (const auto& rep : two_three_five){
    if (rep.find(real_to_rep["e"])!=std::string::npos){
      num_to_rep[2] = rep;
      rep_to_num[rep] = 2;
    } else if (rep.find(real_to_rep["c"])==std::string::npos){
      num_to_rep[5] = rep;
      rep_to_num[rep] = 5;
    } else {
      num_to_rep[3] = rep;
      rep_to_num[rep] = 3;
    }
  }
  
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
