#include "06.hpp"

class Fish{
  public :
    std::vector<int> fish;
    
    Fish(const std::vector<int>& fish);
};

Fish::Fish(const std::vector<int>& input){
  fish = input;
}

class Lifetimes{
  public :
    std::vector<long long> lifetimes;
    
    Lifetimes();
    
    friend std::ostream& operator<<(std::ostream& os, const Lifetimes& lifetime);
    friend std::istream& operator>>(std::istream& is, Lifetimes& lifetime);
    Lifetimes(const std::string& s);
    
    Lifetimes(const Fish& fish);
    void advance();
    long long count() const;
};

Lifetimes::Lifetimes(){
  for (int i=0; i<9; ++i){
    lifetimes.push_back(0);
  }
}

std::ostream& operator<<(std::ostream& os, const Lifetimes& lifetimes){
  for (const auto& l : lifetimes.lifetimes){
    os << l << ' ';
  }
  return os;
}

std::istream& operator>>(std::istream& is, Lifetimes& lifetimes){
  int lifetime;
  while (not is.eof()){
    is >> lifetime;
    lifetimes.lifetimes.push_back(lifetime);
  }
  return is;
}

Lifetimes::Lifetimes(const std::string& s){
  std::istringstream(s) >> *this;
}

Lifetimes::Lifetimes(const Fish& fish) : Lifetimes(){
  for (const auto& f : fish.fish){
    lifetimes[f]++;
  }
}

void Lifetimes::advance(){
  Lifetimes next;
  for (int i=0; i<8; ++i){
    next.lifetimes[i] = lifetimes[i+1];
  }
  next.lifetimes[6] += lifetimes[0];
  next.lifetimes[8] += lifetimes[0];
  lifetimes = next.lifetimes;
}

long long Lifetimes::count() const {
  return std::accumulate(lifetimes.begin(), lifetimes.end(), (long long)0);
}

std::tuple<long long,long long> day06(const std::vector<std::string>& flines){
  Fish fish(split<int>(flines[0], ','));
  Lifetimes lifetimes(fish);
  
  for (int i=0; i<80; ++i){
    lifetimes.advance();
  }
  long long count1 = lifetimes.count();
  
  for (int i=80; i<256; ++i){
    lifetimes.advance();
  }
  long long count2 = lifetimes.count();
  
  return {count1, count2};
}
