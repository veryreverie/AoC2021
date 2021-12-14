#include "14.hpp"

class Pair{
  public:
    char left;
    char right;
    
    Pair(){};
    
    friend std::ostream& operator<<(std::ostream& os, const Pair& pair);
    friend std::istream& operator>>(std::istream& is, Pair& pair);
    Pair(const char& _left, const char& _right);
    Pair(const std::string& string);
    
    bool operator==(const Pair& that) const{
      return left==that.left and right==that.right;
    }
    bool operator!=(const Pair& that) const{
      return not (*this==that);
    }
    bool operator<(const Pair& that) const{
      return left<that.left or (left==that.left and right<that.right);
    }
    bool operator<=(const Pair& that) const{
      return *this==that or *this<that;
    }
    bool operator>(const Pair& that) const{
      return not (*this<=that);
    }
    bool operator>=(const Pair& that) const{
      return not (*this<that);
    }
};

std::ostream& operator<<(std::ostream& os, const Pair& pair){
  return os << pair.left << pair.right;
}

std::istream& operator>>(std::istream& is, Pair& pair){
  std::string string;
  is >> string;
  pair = Pair(string);
  return is;
}

Pair::Pair(const char& _left, const char& _right){
  left = _left;
  right = _right;
}

Pair::Pair(const std::string& string) : Pair(string[0], string[1]){
}

class InsertionRule{
  public:
    Pair pair;
    char insert;
    std::vector<Pair> new_pairs;
    
    friend std::ostream& operator<<(std::ostream& os, const InsertionRule& insertion_rule);
    friend std::istream& operator>>(std::istream& is, InsertionRule& insertion_rule);
    InsertionRule(const std::string& string);
};

std::ostream& operator<<(std::ostream& os, const InsertionRule& insertion_rule){
  return os << insertion_rule.pair << " -> " << insertion_rule.insert;
}

std::istream& operator>>(std::istream& is, InsertionRule& insertion_rule){
  is >> insertion_rule.pair >> Ignore(4) >> insertion_rule.insert;
  insertion_rule.new_pairs = {
    Pair(insertion_rule.pair.left, insertion_rule.insert),
    Pair(insertion_rule.insert, insertion_rule.pair.right)
  };
  return is;
}

InsertionRule::InsertionRule(const std::string& string){
  std::istringstream(string) >> *this;
}

class Pairs{
  public:
    std::map<Pair,long long> pair_counts;
    char first_element;
    
    Pairs(){}
    Pairs(const std::string& string);
    
    friend std::ostream& operator<<(std::ostream& os, const Pairs& pairs);
    
    void add_pair(const Pair& pair, const long long& count=1);
    void insert(const std::vector<InsertionRule>& insertion_rules);
    
    std::map<char,long long> count_elements() const;
    long long element_count_range() const;
};

Pairs::Pairs(const std::string& string){
  for (int i=0; i<string.size()-1; ++i){
    add_pair(Pair(string.substr(i,2)));
  }
  first_element = string[0];
}

std::ostream& operator<<(std::ostream& os, const Pairs& pairs){
  for (const auto& [pair, count] : pairs.pair_counts){
    os << pair << " * " << count << std::endl;
  }
  return os;
}

void Pairs::add_pair(const Pair& pair, const long long& count){
  try {
    pair_counts.at(pair) += count;
  } catch(const std::out_of_range& e){
    pair_counts.insert({pair, count});
  }
}

void Pairs::insert(const std::vector<InsertionRule>& insertion_rules){
  Pairs new_pairs(std::string(1, first_element));
  for (const auto& insertion_rule : insertion_rules){
    try {
      const long long count = pair_counts.at(insertion_rule.pair);
      for (const auto& pair : insertion_rule.new_pairs){
        new_pairs.add_pair(pair, count);
      }
    } catch(const std::out_of_range& e){
    }
  }
  *this = new_pairs;
}

std::map<char,long long> Pairs::count_elements() const {
  std::map<char,long long> result;
  for (const auto& [pair, count] : pair_counts){
    try {
      result.at(pair.right) += count;
    } catch(const std::out_of_range& e) {
      result.insert({pair.right, count});
    }
  }
  
  try {
    result.at(first_element) += 1;
  } catch(const std::out_of_range& e) {
    result.insert({first_element, 1});
  }
  return result;
}

long long Pairs::element_count_range() const {
  auto element_counts = count_elements();
  
  [[maybe_unused]] auto [min_element, min_count] = *std::min_element(
    element_counts.begin(),
    element_counts.end(),
    [] (const auto& p1, const auto& p2){return p1.second < p2.second;}
  );
  [[maybe_unused]] auto [max_element, max_count] = *std::max_element(
    element_counts.begin(),
    element_counts.end(),
    [] (const auto& p1, const auto& p2){return p1.second < p2.second;}
  );
  return max_count-min_count;
}

std::tuple<long long,long long> day14(const std::vector<std::string>& flines){
  Pairs pairs(flines[0]);
  std::vector<InsertionRule> insertion_rules(flines.begin()+2, flines.end());
  
  for (int i=0; i<10; ++i){
    pairs.insert(insertion_rules);
  }
  long long first_range = pairs.element_count_range();
  
  for (int i=10; i<40; ++i){
    pairs.insert(insertion_rules);
  }
  long long second_range = pairs.element_count_range();
  
  return {first_range, second_range};
}
