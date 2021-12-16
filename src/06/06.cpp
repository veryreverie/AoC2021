#include "06.hpp"

namespace Day06{
  class Fish{
    public :
      std::vector<int> timers;
      
      friend std::ostream& operator<<(std::ostream& os, const Fish& fish);
      friend std::istream& operator>>(std::istream& is, Fish& fish);
      Fish(const std::string& line);
  };

  std::ostream& operator<<(std::ostream& os, const Fish& fish){
    for (const auto timer : fish.timers){
      os << timer << ',';
    }
    return os;
  }

  std::istream& operator>>(std::istream& is, Fish& fish){
    int timer;
    while (is >> timer){
      fish.timers.push_back(timer);
      is >> Common::Ignore(1,',');
    }
    return is;
  }

  Fish::Fish(const std::string& line){
    std::istringstream(line) >> *this;
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
    for (const auto& timer : fish.timers){
      lifetimes[timer]++;
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
    Fish fish(flines[0]);
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
}
