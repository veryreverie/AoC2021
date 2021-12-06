#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <exception>
#include <iomanip>
#include <numeric>

template <class T>
T munch(std::istringstream& iss, char delim) {
  std::string token;
  std::getline(iss, token, delim);
  T result;
  std::istringstream(token) >> result;
  return result;
}

template <class T>
std::vector<T> split(const std::string& s, char delim) {
  std::istringstream iss(s);
  std::vector<T> result;
  while (not iss.eof()){
    result.push_back(munch<T>(iss, delim));
  }
  return result;
}

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

void day06(std::vector<std::string> flines){
  Fish fish(split<int>(flines[0], ','));
  Lifetimes lifetimes(fish);
  
  for (int i=0; i<80; ++i){
    lifetimes.advance();
  }
  std::cout << lifetimes.count() << std::endl;
  
  for (int i=80; i<256; ++i){
    lifetimes.advance();
  }
  std::cout << lifetimes.count() << std::endl;
}

int main(void){
  std::ifstream infile("input");
  std::vector<std::string> lines;
  if (infile.is_open()){
    std::string line;
    while (getline(infile, line)){
      lines.push_back(line);
    }
  }
  infile.close();
  
  day06(lines);
}
