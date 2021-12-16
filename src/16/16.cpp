#include "16.hpp"

namespace Day16{
  int char_to_int(const char& c){
    if (c-'0'>=0 and c-'0'<=9){
      return c-'0';
    } else if (c-'A'>=0 and c-'A'<=5){
      return 10+c-'A';
    } else {
      std::ostringstream os;
      os << "Cannot convert char " << c << " to int.";
      throw std::invalid_argument(os.str());
    }
  }
  
  class Bits{
    public:
      std::vector<bool> bits;
      
      Bits(){}
      Bits(const std::vector<bool>& _bits);
      
      Bits(const int& input);
      Bits(const char& input);
      Bits(const std::string& input);
      
      friend std::ostream& operator<<(std::ostream& os, const Bits& bits);
      
      Bits slice(const int& begin, const int& end=-1) const;
      void append(const Bits& input);
      
      operator long long() const;
  };
  
  Bits::Bits(const std::vector<bool>& _bits){
    bits = _bits;
  }
  
  Bits::Bits(const int& input){
    int copy = input;
    for (int i=0; i<4; ++i){
      bits.push_back(copy%2==1);
      copy >>= 1;
    }
    std::reverse(bits.begin(), bits.end());
  }
  
  Bits::Bits(const char& input) : Bits(char_to_int(input)){
  }
  
  Bits::Bits(const std::string& input){
    for (const char& c : input){
      append(Bits(c));
    }
  }
  
  std::ostream& operator<<(std::ostream& os, const Bits& bits){
    for (const auto& bit : bits.bits){
      os << bit;
    }
    return os;
  }
  
  Bits Bits::slice(const int& begin, const int& end) const {
    if (begin>=bits.size()){
      std::ostringstream os;
      os << "Slice begins at position " << begin << '/' << bits.size()-1 << ".";
      throw std::invalid_argument(os.str());
    }
    if (end!=-1){
      if (end>=bits.size()+1){
        std::ostringstream os;
        os << "Slice ends at position " << end << '/' << bits.size() << ".";
        throw std::invalid_argument(os.str());
      }
      return Bits(std::vector<bool>{bits.begin()+begin, bits.begin()+end});
    } else {
      return Bits(std::vector<bool>{bits.begin()+begin, bits.end()});
    }
  }
  
  void Bits::append(const Bits& input){
    bits.insert(bits.end(), input.bits.begin(), input.bits.end());
  }
  
  Bits::operator long long() const{
    long long result = 0;
    for (int i=0; i<bits.size(); ++i){
      if (bits[i]){
        result += (long long)1 << (bits.size()-i-1);
      }
    }
    return result;
  }
  
  class Packet{
    public:
      int num_bits;
      int version;
      int typeID;
      long long value;
      std::vector<Packet> subpackets;
      
      Packet(const Bits& bits);
      
      friend std::ostream& operator<<(std::ostream& os, const Packet& packet);
      void prettyprint(
        const int& depth=-1,
        const int& indent=0,
        const bool& last=true
      ) const;
      
      int sum_version_numbers() const;
      long long evaluate() const;
  };
  
  Packet::Packet(const Bits& bits){
    num_bits = 6;
    version = bits.slice(0,3);
    typeID = bits.slice(3,6);
    if (typeID==4){
      Bits _value;
      for (int i=0; ; ++i){
        num_bits += 5;
        _value.append(bits.slice(7+5*i, 11+5*i));
        if (not bits.bits[6+5*i]){
          value = _value;
          break;
        }
      }
    } else {
      value = 0;
      num_bits += 1;
      bool length_typeID = bits.bits[6];
      if (length_typeID){
        num_bits += 11;
        int num_subpackets = bits.slice(7,18);
        int start_position = 18;
        for (int i=0; i<num_subpackets; ++i){
          subpackets.push_back(Packet(bits.slice(start_position)));
          num_bits += subpackets.back().num_bits;
          start_position += subpackets.back().num_bits;
        }
      } else {
        num_bits += 15;
        int total_length = bits.slice(7,22);
        num_bits += total_length;
        int start_position = 22;
        while (start_position<22+total_length){
          subpackets.push_back(Packet(bits.slice(start_position,22+total_length)));
          start_position += subpackets.back().num_bits;
        }
      }
    }
  }
  
  std::ostream& operator<<(std::ostream& os, const Packet& packet){
    os << "v=" << packet.version << ",t=" << packet.typeID;
    if (packet.typeID==4){
      return os << ",val=" << packet.value;
    } else {
      os << ",subs={";
      for (const auto& subpacket : packet.subpackets){
        os << subpacket << " ";
      }
      return os << "}";
    }
  }
  
  void Packet::prettyprint(const int& depth, const int& indent, const bool& last) const {
    const std::vector<std::string> operations{
      "sum",
      "prod",
      "min",
      "max",
      "val",
      ">",
      "<",
      "=="
    };
    
    if (depth==0){
      std::cout << evaluate();
      if (not last){
        std::cout << ", ";
      }
    } else if (typeID==4){
      std::cout << std::string(indent*2,' ') << std::setw(11) << evaluate();
      if (not last){
        std::cout << ",";
      }
      std::cout << std::endl;
    } else {
      int _depth = depth;
      if (_depth>1 and std::all_of(
        subpackets.begin(),
        subpackets.end(),
        [](const Packet& p){return p.typeID==4;}
      )) {
        _depth = 1;
      }
      
      std::cout << std::string(indent*2,' ') << std::setw(11) << evaluate()
                << " = " << operations[typeID] << " {";
      if (_depth!=1){
        std::cout << std::endl;
      }
      for (int i=0; i<subpackets.size(); ++i){
        if (i!=subpackets.size()-1){
          subpackets[i].prettyprint(_depth-1, indent+1, false);
        } else {
          subpackets[i].prettyprint(_depth-1, indent+1);
        }
      }
      
      if (_depth==1) {
        std::cout << '}';
      } else {
        std::cout << std::string(2*indent, ' ') << '}';
      }
      
      if (not last){
        std::cout << ',';
      }
      std::cout << std::endl;
    }
  }
  
  int Packet::sum_version_numbers() const {
    int result = version;
    for (const auto& packet : subpackets){
      result += packet.sum_version_numbers();
    }
    return result;
  }
  
  long long Packet::evaluate() const {
    if (typeID==0){
      return std::accumulate(
        subpackets.begin(),
        subpackets.end(),
        (long long)0,
        [](const long long& a, const Packet& b){return a+b.evaluate();}
      );
    } else if (typeID==1){
      return std::accumulate(
        subpackets.begin(),
        subpackets.end(),
        (long long)1,
        [](const long long& a, const Packet& b){return a*b.evaluate();}
      );
    } else if (typeID==2){
      return std::min_element(
        subpackets.begin(),
        subpackets.end(),
        [](const Packet& a, const Packet& b){return a.evaluate()<b.evaluate();}
      )->evaluate();
    } else if (typeID==3){
      return std::max_element(
        subpackets.begin(),
        subpackets.end(),
        [](const Packet& a, const Packet& b){return a.evaluate()<b.evaluate();}
      )->evaluate();
    } else if (typeID==4){
      return value;
    } else if (typeID==5){
      if (subpackets[0].evaluate()>subpackets[1].evaluate()){
        return 1;
      } else {
        return 0;
      }
    } else if (typeID==6){
      if (subpackets[0].evaluate()<subpackets[1].evaluate()){
        return 1;
      } else {
        return 0;
      }
    } else if (typeID==7){
      if (subpackets[0].evaluate()==subpackets[1].evaluate()){
        return 1;
      } else {
        return 0;
      }
    } else {
      std::ostringstream os;
      os << "Invalid typeID: " << typeID << ".";
      throw std::invalid_argument(os.str());
    }
  }
  
  std::tuple<long long,long long> day16(const std::vector<std::string>& flines){
    Bits bits(flines[0]);
    Packet packet(bits);
    return {packet.sum_version_numbers(), packet.evaluate()};
  }
}
