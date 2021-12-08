#include "03.hpp"

class Bits{
  public:
    std::vector<int> bits;
    Bits();
    
    friend std::ostream& operator<<(std::ostream& os, const Bits& bits);
    friend std::istream& operator>>(std::istream& is, Bits& bits);
    Bits(const std::string& s);
    
    int size() const;
    operator int() const;
};

Bits::Bits(){
}

std::ostream& operator<<(std::ostream& os, const Bits& bits){
  for (int bit : bits.bits){
    os << bit;
  }
  return os;
}

std::istream& operator>>(std::istream& is, Bits& bits){
  for (;;){
    char c = is.get();
    if (is.rdstate() == 0){
      bits.bits.push_back(c-'0');
    } else {
      return is;
    }
  }
}

Bits::Bits(const std::string& s){
  std::istringstream(s) >> *this;
}

int Bits::size() const{
  return bits.size();
}

Bits::operator int() const{
  int s = size();
  int result = 0;
  for (int i=0; i<s; ++i){
    if (bits[i]==1){
      result += 1 << (s-i-1);
    }
  }
  return result;
}

std::tuple<Bits, Bits> gamma_epsilon(std::vector<Bits> bits_list){
  int l = bits_list[0].size();
  
  std::vector<int> counts;
  for (int i=0; i<l; ++i){
    counts.push_back(0);
  }
  for (auto& bits : bits_list){
    for (int i=0; i<l; ++i){
      if (bits.bits[i]==0){
        counts[i]--;
      } else if (bits.bits[i]==1){
        counts[i]++;
      }
    }
  }
  
  Bits gamma;
  Bits epsilon;
  for (int i=0; i<l; ++i){
    if (counts[i]>=0){
      gamma.bits.push_back(1);
      epsilon.bits.push_back(0);
    } else {
      gamma.bits.push_back(0);
      epsilon.bits.push_back(1);
    }
  }
  
  return {gamma, epsilon};
}

std::vector<Bits> filter_bits(
  const std::vector<Bits>& bits_list,
  const Bits& match,
  const int& index
){
  std::vector<Bits> result;
  for (const auto& bits : bits_list){
    if (bits.bits[index]==match.bits[index]){
      result.push_back(bits);
    }
  }
  return result;
}

std::tuple<long long,long long> day03(const std::vector<std::string>& flines){
  int l = flines[0].size();
  
  std::vector<Bits> bits_list;
  for (auto fline : flines){
    bits_list.push_back(Bits(fline));
  }
  
  auto [gamma, epsilon] = gamma_epsilon(bits_list);
  
  std::vector<Bits> new_list = bits_list;
  Bits o2;
  for (int i=0; i<l; ++i){
    auto [g, _] = gamma_epsilon(new_list);
    new_list = filter_bits(new_list, g, i);
    if (new_list.size()==1){
      o2 = new_list[0];
      break;
    }
  }
  
  new_list = bits_list;
  Bits co2;
  for (int i=0; i<l; ++i){
    auto [_, e] = gamma_epsilon(new_list);
    new_list = filter_bits(new_list, e, i);
    if (new_list.size()==1){
      co2 = new_list[0];
      break;
    }
  }
  
  return {int(gamma)*int(epsilon), int(o2)*int(co2)};
}
